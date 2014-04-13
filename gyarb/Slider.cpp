#include "Slider.h"

Slider::Slider(sf::RenderWindow& window, sf::Sprite frontSprite, sf::Sprite backSprite, double initValPercent, double minVal, double maxVal)
	: Widget(window, sf::Rect<float>(backSprite.getPosition().x, backSprite.getPosition().y, backSprite.getLocalBounds().width, backSprite.getLocalBounds().width)) {

	//Note that the size of the widget's triggerzone is equal to the size of the frontSprite

	this->front_ = frontSprite;
	this->back_ = backSprite;
	this->valPercent_ = initValPercent;

	this->minVal_ = minVal;
	this->maxVal_ = maxVal;

	this->front_.setOrigin(this->front_.getLocalBounds().width * 0.5, this->front_.getLocalBounds().height * 0.5);
	this->front_.setPosition(this->back_.getPosition().x + this->back_.getLocalBounds().width * this->getValuePercent(), this->back_.getPosition().y + this->back_.getLocalBounds().height * 0.5);
}

Slider::Slider(sf::Rect<float> size, sf::RenderWindow& window, double initValPercent, double minVal, double maxVal) 
	: Widget(window, sf::Rect<float>(size.left, size.top, size.width, size.height)) {

	const float TOP_HEIGHT = 1.8;
	const float TOP_WIDTH = 0.9;
	
	sf::Sprite s1 = sf::Sprite(*LoadTexture("SliderBack.png"));
	sf::Sprite s2 = sf::Sprite(*LoadTexture("ButtonSquare.png"));
	s1.setPosition(size.left, size.top);

	s1.setScale(
			size.width / s1.getLocalBounds().width,
			size.height / s1.getLocalBounds().height);
	s2.setScale(
			TOP_WIDTH * s1.getScale().y * s1.getLocalBounds().height / s2.getLocalBounds().width,
			TOP_HEIGHT * s1.getScale().y * s1.getLocalBounds().height / s2.getLocalBounds().height);

	this->front_ = s2;
	this->back_ = s1;

	this->valPercent_ = initValPercent;
	this->minVal_ = minVal;
	this->maxVal_ = maxVal;

	this->front_.setOrigin(this->front_.getLocalBounds().width * 0.5, this->front_.getLocalBounds().height * 0.5);
	this->front_.setPosition(this->back_.getPosition().x + this->back_.getGlobalBounds().width * this->getValuePercent(), this->back_.getPosition().y + this->back_.getGlobalBounds().height * 0.5);
}

Slider::~Slider() {}

double Slider::getValue() {
	return (this->minVal_ + this->getValuePercent() * (this->maxVal_ - this->minVal_));
}

double Slider::getValuePercent() {
	return this->valPercent_;
}

double Slider::getMax() {
	return this->maxVal_;
}

double Slider::getMin() {
	return this->minVal_;
}

void Slider::p_draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(this->back_, states);
	target.draw(this->front_, states);
}

void Slider::p_update(sf::Time dt) {
	if(this->hovered() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if(GetMouseCoords(*this->getWindow()).x >= this->minX() && (GetMouseCoords(*this->getWindow()).x) <= this->maxX()) {
			this->setSliderX(GetMouseCoords(*this->getWindow()).x);
		}
	}
}

void Slider::setSliderX(float newPosX) {
	//Updating the drawables position, and the triggerZone.
	this->front_.setPosition(newPosX, this->front_.getPosition().y);
	//Modyfing value
	this->valPercent_ = (double)(2 * (this->front_.getPosition().x - minX()) / (this->maxX() - this->minX()));
}