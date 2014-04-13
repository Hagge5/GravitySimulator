#pragma once

//Included dependencies
#include "MassBody.h"
#include "Vector2Buffer.h"
#include "PositionTracker.h"
#include "UtilFuncs.h"
#include <math.h>
#include <vector>
#include <SFML\System.hpp>

//Forward declared dependencies
	//None

//The class

class GravityController {
public:
	GravityController(MassBody* whichBody, std::vector<MassBody*>* allBodies, double destroyRange = 0.0000000000001);
	virtual ~GravityController();

	void update();

private:
	static inline sf::Vector2<double> getGravitationalAcceleration(double otherMass, double distanceBetweenBodies, double radBetweenBodies);

	double destroyRange_;
	std::vector<MassBody*>* allBodies_;
	MassBody* bdy_;
	sf::Vector2<double>* controlledAccel_;

	static const double G; //defined in cpp file
};          