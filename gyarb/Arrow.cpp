#include "Arrow.h"

const float Arrow::LINE_THICKNESS_TO_HEAD_RADIUS = 2.0;

Arrow::Arrow(float thickness, sf::Vector2<float> start, sf::Vector2<float> end, sf::Color c) 
	: sf::Drawable() {
	
	this->line_ = new sf::RectangleShape(sf::Vector2<float>(GetDistanceBetweenPoints(start, end), thickness));
	this->line_->setOrigin(0, this->line_->getLocalBounds().height * 0.5);
	this->line_->setFillColor(c);
	this->line_->setPosition(start);
	this->line_->setRotation(GetAngleBetweenPointsDeg(start, end));

	this->head_ = new sf::CircleShape(thickness * LINE_THICKNESS_TO_HEAD_RADIUS, 3); //This becomes a triangle
	this->head_->setOrigin(this->head_->getRadius(), this->head_->getRadius());
	this->head_->setFillColor(c);
	
	this->syncHead();
}

Arrow::~Arrow() {
	delete this->head_;
	delete this->line_;
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*this->line_, states);
	target.draw(*this->head_, states);
}

void Arrow::setLength(float l) {
	this->line_->setSize(sf::Vector2<float>(l, this->line_->getSize().y));
	this->syncHead();
}

void Arrow::setRotation(float deg) {
	this->line_->setRotation(deg);
	this->syncHead();
}

float Arrow::getLength() {
	return this->line_->getLocalBounds().width;
}

void Arrow::syncHead() {
	static const float degToRad = 3.14159265 / 180;

	this->head_->setRotation(this->line_->getRotation() + 90);
	this->head_->setPosition(
		this->line_->getPosition().x + this->line_->getLocalBounds().width * cos(this->line_->getRotation() * degToRad),
		this->line_->getPosition().y + this->line_->getLocalBounds().width * sin(this->line_->getRotation()* degToRad));
}