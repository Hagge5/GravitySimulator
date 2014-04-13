#include "Switch.h"

Switch::Switch(sf::Sprite* onSprite, sf::Sprite* offSprite, sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window, bool initVal) 
	: Button(idleSprite, hoverSprite, window) {

		this->onSprite_ = onSprite;
		this->offSprite_ = offSprite;
		this->isOn_ = initVal;
}

Switch::Switch(sf::Sprite* onSprite, sf::Sprite* offSprite, sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window, bool initVal)
	: Button(idleSprite, hoverSprite, window) {

		this->onSprite_ = onSprite;
		this->offSprite_ = offSprite;
		this->isOn_ = initVal;
}

Switch::Switch(sf::FloatRect size, sf::RenderWindow& window, bool initVal)
	: Button(new sf::Sprite(*LoadTexture("CheckBox.png")), new sf::Sprite(*LoadTexture("CheckBoxHovered.png")), window) {

		this->getIdleSprite()->setPosition(size.left, size.top);
		this->getHoverSprite()->setPosition(size.left, size.top);

		this->getIdleSprite()->scale(
			size.width / this->getIdleSprite()->getLocalBounds().width,
			size.height / this->getIdleSprite()->getLocalBounds().height);
		this->getHoverSprite()->scale(
			size.width / this->getHoverSprite()->getLocalBounds().width,
			size.height / this->getHoverSprite()->getLocalBounds().height);

		this->setZone(size);

		this->onSprite_ = new sf::Sprite(*LoadTexture("CheckMark.png"));
		this->offSprite_ = new sf::Sprite();
		this->isOn_ = initVal;

		this->onSprite_->setScale(
			size.width / this->onSprite_->getLocalBounds().width, 
			size.height / this->onSprite_->getLocalBounds().height);

		this->onSprite_->setPosition(size.left, size.top);
		this->offSprite_->setPosition(size.left, size.top);
}

Switch::~Switch() {
	delete this->onSprite_;
	delete this->offSprite_;
}

void Switch::p_draw(sf::RenderTarget &target, sf::RenderStates states) const {
	this->Button::p_draw(target, states);

	if(this->isOn())
		target.draw(*this->onSprite_, states);
	else
		target.draw(*this->offSprite_, states);
}

void Switch::onClick() {
	this->invert();
}

void Switch::p_update(sf::Time dt) {
	this->Button::p_update(dt);
}

void Switch::onHover() {
	this->Button::onHover();
}