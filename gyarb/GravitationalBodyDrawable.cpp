#include "GravitationalBodyDrawable.h"

GravitationalBodyDrawable::GravitationalBodyDrawable(std::vector<MassBody*>* allBodies, double mass, double destroyRange, bool isStatic, sf::Vector2<double> startPos, sf::Sprite* shape, PositionTracker<double>* posTracker, Vector2Buffer<double>* accelBuffer, Vector2Buffer<double>* velocBuffer)
	: GravitationalBody(allBodies, mass, destroyRange, isStatic, startPos, posTracker, accelBuffer, velocBuffer), sf::Drawable() {

		this->shape_ = shape;

		if(isStatic) {
			this->staticSign_ = new sf::Sprite(*LoadTexture("gfx\\Static.png"));
			this->staticSign_->setScale(this->getSprite()->getScale());
			this->staticSign_->setOrigin(this->staticSign_->getLocalBounds().width * 0.5, this->staticSign_->getLocalBounds().height * 0.5);
		} else
			this->staticSign_ = nullptr;

		this->updatePos();
}

GravitationalBodyDrawable::~GravitationalBodyDrawable() {
	delete this->shape_;
	if(this->staticSign_ != nullptr)
		delete this->staticSign_;
}

sf::Sprite* GravitationalBodyDrawable::getSprite() {
	return this->shape_;
}

void GravitationalBodyDrawable::update(sf::Time dt) {
	this->GravitationalBody::update(dt);
	this->updatePos();
}

void GravitationalBodyDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*(this->shape_), states);

	if(this->staticSign_ != nullptr)
		target.draw(*(this->staticSign_), states);
}

void GravitationalBodyDrawable::updatePos() {
	this->getSprite()->setPosition((float)this->getPosition().x, (float)this->getPosition().y);

	if(this->staticSign_ != nullptr)
		this->staticSign_->setPosition((float)this->getPosition().x, (float)this->getPosition().y);
}