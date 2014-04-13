#pragma once

#include "Widget.h"
#include "TextureLoader.h"
#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Slider : public Widget {
public:
	Slider(sf::RenderWindow& window, sf::Sprite frontSprite, sf::Sprite backSprite, double initValPercent = 0.00, double minVal = 0.00, double maxVal = 1.00);
	Slider(sf::Rect<float> size, sf::RenderWindow& window, double initValPercent = 0.00, double minVal = 0.00, double maxVal = 1.00);
	virtual ~Slider();

	double getValue();
	double getValuePercent();

	double getMax();
	double getMin();

protected:
	virtual void p_draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void p_update(sf::Time dt);		//Used

	virtual void onHover()		{}			//Not used
	virtual void onHoverStop()	{}			//Not used
	virtual void onClick()		{}			//Not used

	inline	float minX() const	{ return this->back_.getPosition().x; }
	inline	float maxX() const	{ return this->back_.getPosition().x + this->back_.getLocalBounds().width; }

private:
	inline void setSliderX(float newPosX);

	sf::Sprite front_;
	sf::Sprite back_;
	double valPercent_;

	double minVal_;
	double maxVal_;
};