#include "Button.h"

Button::Button(sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window)
	: Widget(window, sf::Rect<float>(idleSprite->getPosition().x, idleSprite->getPosition().y, idleSprite->getLocalBounds().width * idleSprite->getScale().x, idleSprite->getLocalBounds().height * idleSprite->getScale().y)) {

		this->clicked_ = false;
		this->idleSprite_ = idleSprite;
		this->hoverSprite_ = hoverSprite;
		this->a_ = nullptr;
}

Button::Button(sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window)
	: Widget(window, sf::Rect<float>(idleSprite->getPosition().x, idleSprite->getPosition().y, idleSprite->getLocalBounds().width * idleSprite->getScale().x, idleSprite->getLocalBounds().height * idleSprite->getScale().y)) {

		this->clicked_ = false;
		this->idleSprite_ = idleSprite;
		this->hoverSprite_ = hoverSprite;
		this->a_ = hoverSprite;
}

Button::Button(sf::Rect<float> size, sf::RenderWindow& window)
	: Widget(window, size) {

		this->clicked_ = false;

		this->a_ = new AnimatedSprite(*LoadTexture("gfx\\ButtonSquareFlashing.png"), 130, 130, sf::seconds(0.05), false, true);
		this->idleSprite_ = new sf::Sprite(*LoadTexture("gfx\\ButtonSquare.png"));
		this->hoverSprite_ = this->a_;

		this->getIdleSprite()->scale(
			size.width / this->getIdleSprite()->getLocalBounds().width,
			size.height / this->getIdleSprite()->getLocalBounds().height);
		this->getHoverSprite()->scale(
			size.width / this->getHoverSprite()->getLocalBounds().width,
			size.height / this->getHoverSprite()->getLocalBounds().height);

		this->idleSprite_->setPosition(size.left, size.top);
		this->hoverSprite_->setPosition(size.left, size.top);
}

Button::~Button() {
	delete this->idleSprite_;
	delete this->hoverSprite_;
}

void Button::resetAnimation() {
	if(this->a_ != nullptr)
		this->a_->setColumn(0);
}

bool Button::clickPending() {
	bool r = this->clicked_;
	this->clicked_ = false;
	return r;
}

void Button::p_draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if(this->hovered())
		target.draw(*this->hoverSprite_, states);
	else
		target.draw(*this->idleSprite_, states);
}

void Button::p_update(sf::Time dt) {
	if(this->a_ != nullptr)
		this->a_->update(dt);
}

void Button::onHover() {
	this->resetAnimation();
}

void Button::onClick() {
	this->clicked_ = true;
}