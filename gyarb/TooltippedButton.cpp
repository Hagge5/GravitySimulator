#include "TooltippedButton.h"

TooltippedButton::TooltippedButton(sf::Text tooltip, sf::Vector2f tooltipPos, sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window)
	: Button(idleSprite, hoverSprite, window), tt_(tooltip) {
		this->tt_.setPosition(tooltipPos);
}
TooltippedButton::TooltippedButton(sf::Text tooltip, sf::Vector2f tooltipPos, sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window)
	: Button(idleSprite, hoverSprite, window), tt_(tooltip) {
		this->tt_.setPosition(tooltipPos);
}
TooltippedButton::TooltippedButton(sf::Text tooltip, sf::Vector2f tooltipPos, sf::Rect<float> size, sf::RenderWindow& window) 
	: Button(size, window), tt_(tooltip) {
		this->tt_.setPosition(tooltipPos);
}
TooltippedButton::TooltippedButton(sf::Text tooltip, sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window)
	: Button(idleSprite, hoverSprite, window), tt_(tooltip) {
		this->tt_.setPosition(this->getPosition().x, this->getPosition().y + this->getZone().height);
}
TooltippedButton::TooltippedButton(sf::Text tooltip, sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window)
	: Button(idleSprite, hoverSprite, window), tt_(tooltip) {
		this->tt_.setPosition(this->getPosition().x, this->getPosition().y + this->getZone().height);
}
TooltippedButton::TooltippedButton(sf::Text tooltip, sf::Rect<float> size, sf::RenderWindow& window) 
	: Button(size, window), tt_(tooltip) {
		this->tt_.setPosition(this->getPosition().x, this->getPosition().y + this->getZone().height);
}

void TooltippedButton::p_draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if(this->hovered())
		target.draw(this->tt_, states);

	this->Button::p_draw(target, states);
}

void TooltippedButton::p_update(sf::Time dt) {
	this->Button::p_update(dt);
}

void TooltippedButton::onHover() {
	this->Button::onHover();
}

void TooltippedButton::onClick() {
	this->Button::onClick();
}