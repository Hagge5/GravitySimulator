#include "GravityController.h"

//Has to be defined outside of class definition due to the c++ 2010 standard. Not needed in c++ 2011 or later.
const double GravityController::G = 0.0000000000667128190396304;

GravityController::GravityController(MassBody* whichBody, std::vector<MassBody*>* allBodies, double destroyRange) {
	this->destroyRange_ = destroyRange;
	this->allBodies_ = allBodies;
	this->bdy_ = whichBody;
	this->controlledAccel_ = this->bdy_->addAcceleration(sf::Vector2<double>(0, 0));
}

GravityController::~GravityController() {

	//We are going to remove the value we inserted into our bodies acceleration-buffer at construction.

	//Let's be safe, set the controlledAccel to 0...
	this->controlledAccel_->x = 0;
	this->controlledAccel_->y = 0;

	//We need to find the added acceleration in the vector and dispose of it, to avoid memory leaks.
	//For each element in the vector...
	for(int i = 0; i < this->bdy_->getAccelerationBuffer()->getSize(); i++) {

		//If the adress of a element is what controlledAccel is pointing to...
		if(this->bdy_->getAccelerationBuffer()->at(i) == this->controlledAccel_) {

			//Erease the value at index i
			this->bdy_->getAccelerationBuffer()->asVector()->erase(this->bdy_->getAccelerationBuffer()->asVector()->begin() + i);

			//Then break, that value is unique. We don't need to check the rest of them.
			break;

		}
	}

	//NOTE: Due to how this destructor works, the gravityControllers needs to be destroyed BEFORE the body.
}

void GravityController::update() {
	Vector2Buffer<double> temp;
	sf::Vector2<double> r;
	double rSize;

	//A static body is not affected by gravity
	if(this->bdy_->isStatic())
		return;

	for(int i = 0; i < this->allBodies_->size(); i++) {

		//We dont need to compare the object to itself. Since r = 0, the acceleration always becomes 0
		if (this->allBodies_->at(i) == this->bdy_) 
			continue;

		//Calculating distance between bodies
		r.x = this->allBodies_->at(i)->getPosition().x - this->bdy_->getPosition().x;
		r.y = this->allBodies_->at(i)->getPosition().y - this->bdy_->getPosition().y;
		rSize = GetVectorSum(r);

		//Are they too close to each other?
		if(rSize < this->destroyRange_) {
			this->bdy_->destroy();

			if(!this->allBodies_->at(i)->isStatic())
				this->allBodies_->at(i)->destroy();
			return;
		}

		//Getting the acceleration resulting from the gravity of each other body and inserting it into temp.
		temp.add(GravityController::getGravitationalAcceleration(this->allBodies_->at(i)->getMass(), rSize, atan2(r.y, r.x)));
	}

	this->controlledAccel_->x = temp.getSum().x;
	this->controlledAccel_->y = temp.getSum().y;
}

sf::Vector2<double> GravityController::getGravitationalAcceleration(double otherMass, double distanceBetweenBodies, double radBetweenBodies) {
	/*****************************************************************
		Algebra...

		F = G * (m[1] * m[2]) / r^2				(newtons law of gravitational force)
		a[1]*m[1] = G * (m[1] * m[2]) / r^2		(Rewriting F = ma)
		a[1] = G * m[2] / r^2

		Note that this is only the size, and has no indicator of direction.
	******************************************************************/

	//We need to avoid division by zero, thus only perform calculations if the distance isn't 0.
	if(distanceBetweenBodies == 0) return sf::Vector2<double>(0, 0);

	//Calculating size of acceleration using the algebra above
	double a = (GravityController::G * otherMass) / (distanceBetweenBodies * distanceBetweenBodies);

	//Return the values as a vector2, with x and y values calculated using the angle between the bodies
	return sf::Vector2<double>(a * cos(radBetweenBodies), a * sin(radBetweenBodies));
}