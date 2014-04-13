#include "TooltippedSlider.h"

TooltippedSlider::TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::RenderWindow& window, sf::Sprite frontSprite, sf::Sprite backSprite, double initValPercent, double minVal, double maxVal)
	: Slider(window, frontSprite, backSprite, initValPercent, minVal, maxVal) {
	this->tt_ = sf::Text("", tooltipFont, tooltipSize);
	this->tt_.setPosition(backSprite.getGlobalBounds().left, backSprite.getGlobalBounds().top + backSprite.getGlobalBounds().height);
}

TooltippedSlider::TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::Rect<float> size, sf::RenderWindow& window, double initValPercent, double minVal, double maxVal)
	: Slider(size, window, initValPercent, minVal, maxVal) {
	this->tt_ = sf::Text("", tooltipFont, tooltipSize);
	this->tt_.setPosition(size.left, size.top + size.height);
}

TooltippedSlider::TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::Vector2f tooltipPos, sf::RenderWindow& window, sf::Sprite frontSprite, sf::Sprite backSprite, double initValPercent, double minVal, double maxVal)
	: Slider(window, frontSprite, backSprite, initValPercent, minVal, maxVal) {
	this->tt_ = sf::Text("", tooltipFont, tooltipSize);
	this->tt_.setPosition(tooltipPos);
}

TooltippedSlider::TooltippedSlider(sf::Font& tooltipFont, unsigned int tooltipSize, sf::Vector2f tooltipPos, sf::Rect<float> size, sf::RenderWindow& window, double initValPercent, double minVal, double maxVal)
	: Slider(size, window, initValPercent, minVal, maxVal) {
	this->tt_ = sf::Text("", tooltipFont, tooltipSize);
	this->tt_.setPosition(tooltipPos);
}

void TooltippedSlider::p_draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if(this->hovered())
		target.draw(this->tt_, states);

	this->Slider::p_draw(target, states);
}

void TooltippedSlider::p_update(sf::Time dt) {
	this->tt_.setString(std::to_string((long double) this->getValue()).substr(0, 4));
	this->Slider::p_update(dt);
}