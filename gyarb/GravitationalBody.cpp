#include "GravitationalBody.h"

GravitationalBody::GravitationalBody(std::vector<MassBody*>* allBodies, double mass, double destroyRange, bool isStatic, sf::Vector2<double> startPos,  PositionTracker<double>* posTracker, Vector2Buffer<double>* accelBuffer, Vector2Buffer<double>* velocBuffer) 
	: MassBody(mass, isStatic, startPos, posTracker, accelBuffer, velocBuffer) {

		this->gravCtrl_ = new GravityController(this, allBodies, destroyRange);
}

GravitationalBody::~GravitationalBody() {
	delete this->gravCtrl_;
}

void GravitationalBody::update(sf::Time dt) {
	this->gravCtrl_->update();
	this->MassBody::update(dt);
}