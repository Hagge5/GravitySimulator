#pragma once

//Included dependencies
#include "Body.h"
#include "Vector2Buffer.h"
#include "PositionTracker.h"
#include <SFML\System.hpp> /* sf::Vector2, sf::Time */

//Forward declared dependencies
	//None

//The class

class MassBody : public Body {
public:
	MassBody(double mass = 1,
		bool isStatic = false,
		sf::Vector2<double> startPos = sf::Vector2<double>(0, 0), 
		PositionTracker<double>* posTracker = new PositionTracker<double>(),
		Vector2Buffer<double>* accelBuffer = new Vector2Buffer<double>(),
		Vector2Buffer<double>* velocBuffer = new Vector2Buffer<double>());
	virtual ~MassBody();

	virtual void update(sf::Time dt); //Uses the definition of second derivate to cause movement, inherited from superclass.
	sf::Vector2<double>* addForce(sf::Vector2<double> force); //Returns pointer to inserted value in acceleration vector

	inline double getMass()			const {	return this->mass_;	}

private:
	double mass_;
};