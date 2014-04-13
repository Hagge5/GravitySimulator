#pragma once

//Included dependencies
#include "AnimatedSprite.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

class EffectManager : public sf::Drawable {
public:
	EffectManager();
	virtual ~EffectManager();

	void update(sf::Time dt);

	AnimatedSprite& add(sf::Vector2f pos, AnimatedSprite a);
	AnimatedSprite& add(sf::Vector2f pos, sf::Texture& spriteSheet, float frameWidth, float frameHeight, sf::Time timePerFrame, float scale = 1.0, bool multiRow = true, bool center = true);

	void clear();

private:
	//METHODS
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void removeFinished();

	//MEMBERS
	std::vector<AnimatedSprite> sfxs_;
};