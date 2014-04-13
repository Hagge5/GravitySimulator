#pragma once

//Included dependencies
#include "Vector2Buffer.h"
#include "PositionTracker.h"
#include <SFML\System.hpp> /* sf::Vector2, sf::Time */

//Forward declared dependencies
	//None

//The class

class Body {
public:
	Body(bool isStatic = false,
		sf::Vector2<double> startPos = sf::Vector2<double>(0, 0), 
		PositionTracker<double>* posTracker = new PositionTracker<double>(),
		Vector2Buffer<double>* accelBuffer = new Vector2Buffer<double>(),
		Vector2Buffer<double>* velocBuffer = new Vector2Buffer<double>());
	virtual ~Body();

	virtual void update(sf::Time dt); //Uses the definition of second derivate to cause movement

	sf::Vector2<double>* addImpulse(sf::Vector2<double> impulse); //Returns pointer to value in buffer
	sf::Vector2<double>* addAcceleration(sf::Vector2<double> acceleration);

	inline	bool isStatic()									const { return this->static_;				}

	inline	Vector2Buffer<double>* getAccelerationBuffer()	const {	return this->accelBuffer_;			}
	inline	PositionTracker<double>* getPositionTracker()	const {	return this->pos_;					}
	inline	sf::Vector2<double> getPosition()				const {	return this->pos_->getCurrentPos();	}
	inline	sf::Vector2<double> getPreviousPosition()		const {	return this->pos_->getLastPos();	}

	inline	bool wantDestroy()								const { return this->wantDestroy_;			}
	inline	void destroy()										  { this->wantDestroy_ = true;			}

private:
	bool static_;
	bool wantDestroy_;
	Vector2Buffer<double>* accelBuffer_;
	Vector2Buffer<double>* velocBuffer_;
	PositionTracker<double>* pos_;
};