#pragma once

//Included dependencies
#include "MassBody.h"
#include "Vector2Buffer.h"
#include "PositionTracker.h"
#include "GravityController.h"
#include <SFML\System.hpp> /* sf::Vector2, sf::Time */

//Forward declared dependencies
	//none

//The class

class GravitationalBody : public MassBody {
public:
	GravitationalBody(std::vector<MassBody*>* allBodies,
		double mass = 1,
		double destroyRange = 0.0000001,
		bool isStatic = false,
		sf::Vector2<double> startPos = sf::Vector2<double>(0, 0), 
		PositionTracker<double>* posTracker = new PositionTracker<double>(),
		Vector2Buffer<double>* accelBuffer = new Vector2Buffer<double>(),
		Vector2Buffer<double>* velocBuffer = new Vector2Buffer<double>());
	virtual ~GravitationalBody();

	virtual	void update(sf::Time dt); //Uses the definition of second derivate to cause movement, inherited from superclass.
									//Starting with this class, also applies gravitational acceleration.

private:
	GravityController* gravCtrl_;
};