#pragma once

//Included dependencies
#include "PositionTracker.h"
#include <deque>
#include <SFML\System.hpp> /* sf::Vector2 */
#include <SFML\Graphics.hpp> /* sf::Drawable, sf::Shape */

//Forward declared dependencies
	//None

//The class

template<class T> class PositionTrackerDrawable : public PositionTracker<T> {
public:
	PositionTrackerDrawable(sf::Color color = sf::Color::White, float radius = 1, sf::Vector2<T> startPos = sf::Vector2<T>(0, 0), bool limited = false, int limit = ALWAYS_KEEP_COUNT);
	PositionTrackerDrawable(PositionTracker t, sf::Color color = sf::Color::White, float radius = 1);
	virtual ~PositionTrackerDrawable();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
private:
	sf::CircleShape sprite_;
};

#include "PositionTrackerDrawable.hpp"