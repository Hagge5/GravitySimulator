#include "BodySystem.h"

const double		BodySystem::DESTROY_RECT_ADDITIONAL_SIZE_PERCENT = 3.0;


BodySystem::BodySystem(double collisionRange, sf::Color trailColor, float trailRadius, float spriteScale, float sfxScale, int trailLength, EffectManager* explosionManager) {
	this->collisionRange_ = collisionRange;
	this->spriteScale_ = spriteScale;
	this->sfxScale_ = sfxScale;
	this->trailRadius_ = trailRadius;
	this->trailLength_ = trailLength;

	this->explosions_ = explosionManager;
}

BodySystem::~BodySystem() {
	this->clear();

	if(this->explosions_ != nullptr) {
		this->explosions_->clear();
	}
}

GravitationalBodyDrawable* BodySystem::add(sf::Texture& texture, double mass, bool isStatic, sf::Vector2<double> pos, sf::Vector2<double> initVeloc) {

	sf::Sprite* s = new sf::Sprite(texture);
	s->setOrigin(s->getLocalBounds().width * 0.5, s->getLocalBounds().width * 0.5);
	s->setScale(this->spriteScale_, this->spriteScale_);

	PositionTrackerDrawable<double>* ptd = new PositionTrackerDrawable<double>(this->trailColor_, this->trailRadius_, pos, true, this->trailLength_);

	GravitationalBodyDrawable* b = new GravitationalBodyDrawable(&this->massBodies_, mass, this->collisionRange_, isStatic, pos, s, ptd);

	b->addImpulse(initVeloc);

	this->bodies_.push_back(b);
	this->massBodies_.push_back(b);
	this->trackers_.push_back(ptd);

	return b;
}

void BodySystem::update(sf::Time dt) {
	this->checkForDestroy();
	
	for(auto it = this->bodies_.begin(); it !=  this->bodies_.end(); it++)
		(**it).update(dt);
}

void BodySystem::draw(sf::RenderWindow& wdw, sf::Time future) {
	for(auto it = this->trackers_.begin(); it !=  this->trackers_.end(); it++)
		(**it).draw(wdw);
	for(auto it = this->bodies_.begin(); it !=  this->bodies_.end(); it++)
		wdw.draw(**it);
}

void BodySystem::clear() {
	while(this->bodies_.size() > 0)
		this->eraese(0);
}

void BodySystem::eraese(int index) {
	//fancy shit
	if(this->explosions_ != nullptr)
		this->explosions_->add(V2dToV2f(bodies_[index]->getPosition()), *LoadTexture("gfx\\explosion.png"), 192, 192, sf::seconds(0.05), this->sfxScale_, true);

	//Actual deletion
	delete bodies_[index];

	auto itb = this->bodies_.begin();
	auto itmb = this->massBodies_.begin();
	auto itt = this->trackers_.begin();

	itb += index;
	itmb += index;
	itt += index;

	this->bodies_.erase(itb);
	this->massBodies_.erase(itmb);
	this->trackers_.erase(itt);
}

void BodySystem::eraese(Body* o) {
	//find the body
	for(int i = 0; i < this->bodies_.size(); i++)
		if(this->bodies_[i] == o) {
			this->eraese(i);
			return;
		}
}

void BodySystem::changeBounds(sf::View& view) {
	sf::Vector2f size(view.getSize().x * DESTROY_RECT_ADDITIONAL_SIZE_PERCENT, view.getSize().y * DESTROY_RECT_ADDITIONAL_SIZE_PERCENT);
	this->destroyBounds_ = sf::Rect<double>(
		view.getCenter().x - size.x * 0.5, 
		view.getCenter().y + size.y * 0.5,
		size.x, size.y);
	this->boundsEnabled_ = true;
}

void BodySystem::changeBounds(sf::Rect<double> r) {
	this->destroyBounds_ = r;
	this->boundsEnabled_ = true;
}

void BodySystem::disableBounds() {
	this->boundsEnabled_ = false;
}



//===========================================================
//PRIVATE METHODS
//===========================================================

void BodySystem::checkForDestroy() {
	if(!this->boundsEnabled_) return;

	for(auto it = this->bodies_.begin(); it !=  this->bodies_.end(); it++) {
		if(this->destroyBounds_.contains((*it)->getPosition()) || ((*it)->wantDestroy())) {

			//Remove the body.
			this->eraese((*it));

			//This invalidates the vector, we have to do it from the top.
			this->checkForDestroy();
			return;
		}
	}
}