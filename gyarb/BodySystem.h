#pragma once

#include "TextureLoader.h"
#include "GravitationalBodyDrawable.h"
#include "PositionTrackerDrawable.h"
#include "AnimatedSprite.h"
#include "EffectManager.h"
#include <vector>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class BodySystem {
public:
	BodySystem(double collisionRange, sf::Color trailColor, float trailRadius, float spriteScale, float sfxScale, int trailLength = 2, EffectManager* explosionManager = nullptr);
	~BodySystem();

	GravitationalBodyDrawable* add(sf::Texture& texture, double mass, bool isStatic, sf::Vector2<double> pos, sf::Vector2<double> initVeloc = sf::Vector2<double>(0, 0));

	void update(sf::Time dt);
	void draw(sf::RenderWindow& wdw, sf::Time future);

	void clear();
	void eraese(int index);
	void eraese(Body* o);

	void changeBounds(sf::View& view);
	void changeBounds(sf::Rect<double> r);
	void disableBounds();

private:

	//METHODS
		void checkForDestroy();

	//MEMBERS
			//AESTHETICS
				sf::Color trailColor_;
				int trailLength_;
				float trailRadius_;
				float spriteScale_;
				float sfxScale_;

			//LOGIC
				double collisionRange_;
				sf::Rect<double> destroyBounds_;
				bool boundsEnabled_;

				std::vector<MassBody*> massBodies_;
				std::vector<GravitationalBodyDrawable*> bodies_;
				std::vector<PositionTrackerDrawable<double>*> trackers_;

				EffectManager* explosions_;

			//CONSTANTS
				static const double		DESTROY_RECT_ADDITIONAL_SIZE_PERCENT;
};