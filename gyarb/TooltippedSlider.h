#pragma once

#include "Slider.h"

class TooltippedSlider : public Slider
{
public:
	TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::RenderWindow& window, sf::Sprite frontSprite, sf::Sprite backSprite, double initValPercent = 0.00, double minVal = 0.00, double maxVal = 1.00);
	TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::Rect<float> size, sf::RenderWindow& window, double initValPercent = 0.00, double minVal = 0.00, double maxVal = 1.00);
	TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::Vector2f tooltipPos, sf::RenderWindow& window, sf::Sprite frontSprite, sf::Sprite backSprite, double initValPercent = 0.00, double minVal = 0.00, double maxVal = 1.00);
	TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::Vector2f tooltipPos, sf::Rect<float> size, sf::RenderWindow& window, double initValPercent = 0.00, double minVal = 0.00, double maxVal = 1.00);
	virtual ~TooltippedSlider() {}

protected:
	virtual void p_draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void p_update(sf::Time dt);		//Used

	virtual void onHover()		{}			//Not used
	virtual void onHoverStop()	{}			//Not used
	virtual void onClick()		{}			//Not used
private:
	sf::Text tt_;
};