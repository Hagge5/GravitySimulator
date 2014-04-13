#include "Body.h"

Body::Body(bool isStatic, sf::Vector2<double> startPos, PositionTracker<double>* posTracker, Vector2Buffer<double>* accelBuffer, Vector2Buffer<double>* velocBuffer) {
	this->static_ = isStatic;
	this->pos_ = posTracker;
	this->accelBuffer_ = accelBuffer;
	this->velocBuffer_ = velocBuffer;
	this->wantDestroy_ = false;

	//Has to be done twice, the movement uses the definition of second derivate
	//which requires the current position and the last position. At construction, both
	//of these are the same since it hasn't moved.
	this->pos_->clearAll();
	this->pos_->addPos(startPos);
	this->pos_->addPos(startPos);
}

Body::~Body() {
	delete this->pos_;
	delete this->accelBuffer_;
	delete this->velocBuffer_;
}

void Body::update(sf::Time dt) {

	//Static bodies does not update
	if(this->static_) 
		return;


	//We are here going to utilize the definition of the second derivate for movement.
	//See the limit of second derivate @ http://en.wikipedia.org/wiki/Second_derivative for more information.

	//We'll use a ton of variables here to make things clearer.

	//We'll need delta-time squared, as seconds
	double dtsqr = dt.asSeconds() * dt.asSeconds();

	//We calculate a constant we'll use later for x and y-axis respectively
	double cnstax = dtsqr * this->accelBuffer_->getSum().x;
	double cnstay = dtsqr * this->accelBuffer_->getSum().y;

	//Same thing for velocity. Here we use dt and not dtsqr, but it is otherwise very similar
	double cnstvx = dt.asSeconds() * this->velocBuffer_->getSum().x;
	double cnstvy = dt.asSeconds() * this->velocBuffer_->getSum().y;

	//Then we calculate the position according to the definition of the second derivate.
	//Here, velocity is "saved" as the distance between the two last positions
	double newPosX = cnstax + cnstvx + 2 * this->pos_->getCurrentPos().x - this->pos_->getLastPos().x;
	double newPosY = cnstay + cnstvy + 2 * this->pos_->getCurrentPos().y - this->pos_->getLastPos().y;

	//We then push the new position into our positionTracker, thus saving it
	this->pos_->addPos(newPosX, newPosY);


	//The acceleration should be applied over several updates, but the velocity is added as an impulse.
	//We therefore need to clear the velocitybuffer so that it isn't reapplied.
	this->velocBuffer_->clear();
}

sf::Vector2<double>* Body::addImpulse(sf::Vector2<double> impulse) {
	return this->velocBuffer_->add(impulse);
}

sf::Vector2<double>* Body::addAcceleration(sf::Vector2<double> acceleration) {
	return this->accelBuffer_->add(acceleration);
}