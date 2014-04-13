#pragma once

#include "Button.h"

class TooltippedButton : public Button
{
public:
	TooltippedButton(sf::Text tooltip, sf::Vector2f tooltipPos, sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window);
	TooltippedButton(sf::Text tooltip, sf::Vector2f tooltipPos, sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window);
	TooltippedButton(sf::Text tooltip, sf::Vector2f tooltipPos, sf::Rect<float> size, sf::RenderWindow& window); //Creates a default button
	TooltippedButton(sf::Text tooltip, sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window);
	TooltippedButton(sf::Text tooltip, sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window);
	TooltippedButton(sf::Text tooltip, sf::Rect<float> size, sf::RenderWindow& window); //Creates a default button

protected:
	virtual void p_draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void p_update(sf::Time dt);
	virtual void onHover();
	virtual void onClick();
	virtual void onHoverStop(){}	//Not used
private:
	sf::Text tt_;
};