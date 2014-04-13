#include "MassBody.h"

MassBody::MassBody(double mass, bool isStatic, sf::Vector2<double> startPos, PositionTracker<double>* posTracker, Vector2Buffer<double>* accelBuffer, Vector2Buffer<double>* velocBuffer)
	: Body(isStatic, startPos, posTracker, accelBuffer, velocBuffer) {

		this->mass_ = mass;
}

MassBody::~MassBody() {}

sf::Vector2<double>* MassBody::addForce(sf::Vector2<double> force) {
	//Definition of force...
		//f = m * a
		//a = f / m

	return this->Body::addAcceleration(sf::Vector2<double>(force.x / this->getMass(), force.y / this->getMass()));
}

void MassBody::update(sf::Time dt) {
	this->Body::update(dt);
}