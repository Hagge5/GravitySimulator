#include "Scene.h"

//IN-CLASS INITS
const float			Scene::TRAIL_RADIUS					= 0.02;
const sf::Color		Scene::TRAIL_COLOR					= sf::Color::White;
const int			Scene::UPDATE_FRAMETIME_MAX			= 250000;
const float			Scene::BODY_CONSTANT_SCALE			= 0.004;
const double		Scene::DESTROY_RECT_ADDITIONAL_SIZE = 0.30;
const double		Scene::DESTROY_BODY_COLLISION_RANGE = 0.05;
const float			Scene::VIEWCORDS_PER_PIXEL			= 0.016;

const double		Scene::BODY_PLANET_BREAKOFF_PERCENT = 0.05;
const double		Scene::BODY_SUN_BREAKOFF_PERCENT	= 0.50;

//METHODS

Scene::Scene(sf::RenderWindow* window, sf::Time dt, int ups, float objectScale, float sfxScale, double massMax, bool showTrails, int trailLimit)  {

	this->wdw_ = window;
	this->view_ = sf::View(sf::FloatRect(0, 0, window->getSize().x * VIEWCORDS_PER_PIXEL, window->getSize().y * VIEWCORDS_PER_PIXEL));
	this->dt_ = dt;
	this->frametimePerUpdate_ = sf::seconds((float) 1 / ups);
	this->objectScale_ = objectScale;
	this->showTrails_ = showTrails;

	this->hud_ = new HeadsUpDisplay("BRLNSR.TTF", this, this->wdw_, massMax, massMax * 0.05, massMax);
	this->bodSys_ = new BodySystem(DESTROY_BODY_COLLISION_RANGE, TRAIL_COLOR, TRAIL_RADIUS, objectScale * BODY_CONSTANT_SCALE, sfxScale * BODY_CONSTANT_SCALE, trailLimit, &this->explosions_);

	this->loadTextures();
	this->initDefaults();
}

Scene::~Scene() {
	delete this->hud_;
	delete this->bodSys_;
 int sadad;
}

void Scene::draw(sf::Time future) {
	this->bodSys_->draw(*this->wdw_, future);
	this->wdw_->draw(this->explosions_);
	this->hud_->draw(*this->wdw_);
}

void Scene::update() {
	//Checking for events
	this->eventPoll();

	//updating HUD
	this->hud_->update(this->clock_.getElapsedTime());
	this->explosions_.update(this->clock_.getElapsedTime());

	//Getting elapsed time and resetting the clock
	this->bufferTime_ += this->clock_.getElapsedTime();
	this->clock_.restart();

	//Updating objects
	while(this->bufferTime_.asMicroseconds() > this->frametimePerUpdate_.asMicroseconds()) {

		if(!this->paused_) this->bodSys_->update(this->dt_);
		this->bufferTime_ -= this->frametimePerUpdate_;
	}

	//Drawing
	this->wdw_->clear();
	this->wdw_->draw(this->backGround_);
	this->draw(this->bufferTime_);
	this->wdw_->display();
}

void Scene::continousUpdate() {
	while(!this->wantExit_)
		this->update();
}

void Scene::userCreateBody(double mass, bool isStatic) {
	
	const double IMPULSE_PER_UNIT = 0.00005;

	//Preparing Phase one
	this->wdw_->setView(this->view_); //In case the view has been altered from outside

	sf::Sprite s(*LoadTexture(determineTexture(mass)));
	sf::Event event;

	s.setScale(this->objectScale_ * BODY_CONSTANT_SCALE, this->objectScale_ * BODY_CONSTANT_SCALE);
	s.setOrigin(s.getLocalBounds().width * 0.5, s.getLocalBounds().width * 0.5);

	while(true) {

		//Updating
		s.setPosition(GetMouseCoords(*this->wdw_));

		//Drawing
		this->wdw_->clear();
		this->wdw_->draw(this->backGround_);
		this->bodSys_->draw(*this->wdw_, sf::microseconds(0));
		this->wdw_->draw(s);
		this->wdw_->display();

		//Checking for close and press
		this->wdw_->pollEvent(event);
		
		if(event.type == sf::Event::MouseButtonPressed)
			break;
		else if(event.type == sf::Event::Closed) {
			this->wdw_->close();
			this->wantExit_ = true;
			return;
		}
	}
	
	//Preparing phase two
	sf::Vector2<float> pos = s.getPosition();
	Arrow a(0.10 * this->objectScale_, pos, pos, sf::Color(180, 180, 180));
	
	while (!isStatic && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		//Updating
		a.setLength(GetDistanceBetweenPoints(pos, GetMouseCoords(*this->wdw_)));
		a.setRotation(GetAngleBetweenPointsDeg(pos, GetMouseCoords(*this->wdw_)));

		//Drawing
		this->wdw_->clear();
		this->wdw_->draw(this->backGround_);
		this->bodSys_->draw(*this->wdw_, sf::microseconds(0));
		this->wdw_->draw(a);
		this->wdw_->draw(s);
		this->wdw_->display();

		//Checking for close
		this->wdw_->pollEvent(event);

		if(event.type == sf::Event::Closed) {
			this->wdw_->close();
			this->wantExit_ = true;
			return;
		}
	}

	this->bodSys_->add(*LoadTexture(this->determineTexture(mass)), mass, isStatic, 
		sf::Vector2<double>(s.getPosition().x, s.getPosition().y),
		sf::Vector2<double>(
			(double)(GetMouseCoords(*this->wdw_).x - pos.x) * IMPULSE_PER_UNIT, 
				(double)(GetMouseCoords(*this->wdw_).y - pos.y) * IMPULSE_PER_UNIT));

	//The clock shouldn't tick while this is paused. We reset it.
	this->clock_.restart();
}

void Scene::clear() {
	this->bodSys_->clear();
	this->explosions_.clear();
}

void Scene::loadTextures() {
	LoadTexture("explosion.png");
	LoadTexture("asteroid.png");
	LoadTexture("earth.png");
	LoadTexture("sun.png");
}

void Scene::initDefaults() {
	this->paused_ = false;
	this->wantExit_ = false;
	this->clock_ = sf::Clock();
	this->wdw_->setView(this->view_);

	this->backGround_ = sf::Sprite(*LoadTexture("space.jpg"));
	this->backGround_.setColor(sf::Color(100, 100, 100));
	this->resizeBackground();
}

void Scene::eventPoll() {
	sf::Event event;
	while (this->wdw_->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			this->wdw_->close();
			this->wantExit_ = true;
		} else if (event.type == sf::Event::MouseButtonPressed) {
			this->hud_->checkClick(sf::Mouse::getPosition(*this->wdw_));
		} else if (event.type == sf::Event::MouseWheelMoved) {
			//TODO: Stuff for zooming out/in
		} else if (event.type == sf::Event::Resized) {
			this->view_ = sf::View(sf::FloatRect(0, 0, this->wdw_->getSize().x * VIEWCORDS_PER_PIXEL, this->wdw_->getSize().y * VIEWCORDS_PER_PIXEL));
			this->wdw_->setView(this->view_);
			this->bodSys_->changeBounds(this->view_);
			this->hud_->onWindowResize(this->wdw_->getSize());
			this->resizeBackground();
		}
	}
}

void Scene::resizeBackground() {
	sf::Vector2f s = this->view_.getSize();
	sf::Vector2f bs = sf::Vector2f(backGround_.getLocalBounds().width, backGround_.getLocalBounds().height);
	sf::Vector2f rel = sf::Vector2f(bs.x / s.x, bs.y / s.y);

	if(rel.x > rel.y)
		this->backGround_.setScale(1 / rel.y, 1 / rel.y);
	else
		this->backGround_.setScale(1 / rel.x, 1 / rel.x);

	this->backGround_.setPosition(0, 0);
}

std::string Scene::determineTexture(double mass) {
	if(mass < BODY_PLANET_BREAKOFF_PERCENT * this->hud_->getMaxMass())
		return "asteroid.png";
	else if(mass < BODY_SUN_BREAKOFF_PERCENT * this->hud_->getMaxMass())
		return "earth.png";
	else
		return "sun.png";
}