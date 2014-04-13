#include "Widget.h"

Widget::Widget(sf::RenderWindow& window, sf::Rect<float> zone)
	: sf::Drawable() {

		this->triggerZone_ = zone;
		this->window_ = &window;
			
		//Note that the constructor doesen't call the onHover()/onHoverStop(). I'm lazy.
		this->hovered_ = this->isInside();
}

Widget::~Widget() {}

void Widget::update(sf::Time dt) {

	if(this->isInside()) {

		if (!this->hovered_) {
			this->hovered_ = true;
			this->onHover();
		}
	} else {

		if (this->hovered_) {
			this->hovered_ = false;
			this->onHoverStop();
		}
	}

	this->p_update(dt);
}

void Widget::setZone(sf::Rect<float> zone) {
	this->triggerZone_ = zone;
}

void Widget::checkClick(sf::Vector2<float> pos) {
	if (this->isInside(pos))
		this->onClick();
}

bool Widget::isInside(sf::Vector2<float> pos) {
	return this->triggerZone_.contains(pos);
}