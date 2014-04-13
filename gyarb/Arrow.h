#pragma once

//Included dependencies
#include "UtilFuncs.h"
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Arrow : public sf::Drawable {
public:
	Arrow(float thickness, sf::Vector2<float> start = sf::Vector2<float>(0,0), sf::Vector2<float> end = sf::Vector2<float>(0,0), sf::Color c = sf::Color::White);
	~Arrow();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	
	void setLength(float l);
	void setRotation(float deg);	

	inline float getLength();


private:	

	void syncHead();	

	sf::CircleShape*		head_;
	sf::RectangleShape*		line_;

	static const float LINE_THICKNESS_TO_HEAD_RADIUS; //Defined in cpp file
};