#pragma once

//Included dependencies
#include "TextureLoader.h"
#include "GravitationalBody.h"
#include "PositionTracker.h"
#include <SFML\System.hpp> /* sf::Vector2, sf::Time */
#include <SFML\Graphics.hpp> /* sf::Drawable */

//Forward declared dependencies
	//none

//The class

class GravitationalBodyDrawable : public GravitationalBody, public sf::Drawable {
public:
	GravitationalBodyDrawable(std::vector<MassBody*>* allBodies,
		double mass = 1,
		double destroyRange = 0.0000001,
		bool isStatic = false,
		sf::Vector2<double> startPos = sf::Vector2<double>(0, 0), 
		sf::Sprite* shape = new sf::Sprite(*LoadTexture("gfx\\unknown.png")),
		PositionTracker<double>* posTracker = new PositionTracker<double>(),
		Vector2Buffer<double>* accelBuffer = new Vector2Buffer<double>(),
		Vector2Buffer<double>* velocBuffer = new Vector2Buffer<double>());
	virtual ~GravitationalBodyDrawable();

	sf::Sprite* getSprite();
	
	virtual void update(sf::Time dt); //Overrided from GravitationalBody. From here on places the objects sprite on the proper position.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //Overrided from sf::Drawable

protected:

private:
	void updatePos();

	sf::Sprite* shape_;
	sf::Sprite* staticSign_;
};