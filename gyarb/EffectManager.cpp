#include "EffectManager.h"

EffectManager::EffectManager() {

}

EffectManager::~EffectManager() {
	this->sfxs_.clear();
}

void EffectManager::update(sf::Time dt) {
	this->removeFinished();

	for(auto it = this->sfxs_.begin(); it != this->sfxs_.end(); it++)
		it->update(dt);
}

AnimatedSprite& EffectManager::add(sf::Vector2f pos, AnimatedSprite a) {
	this->sfxs_.push_back(a);
	this->sfxs_.back().setPosition(pos);
	return this->sfxs_.back();
}

AnimatedSprite& EffectManager::add(sf::Vector2f pos, sf::Texture& spriteSheet, float frameWidth, float frameHeight, sf::Time timePerFrame, float scale, bool multiRow, bool center) {
	this->sfxs_.push_back(AnimatedSprite(spriteSheet, frameWidth, frameHeight, timePerFrame, multiRow, false));
	this->sfxs_.back().setScale(scale, scale);
	this->sfxs_.back().setPosition(pos);
	if(center) this->sfxs_.back().setOrigin(frameWidth * 0.5, frameHeight * 0.5); 
	return this->sfxs_.back();
}

void EffectManager::clear() {
	this->sfxs_.erase(std::remove_if(sfxs_.begin(), sfxs_.end(), 
		[](AnimatedSprite& a) { return true; }) , sfxs_.end());
}

void EffectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(auto it = this->sfxs_.begin(); it != this->sfxs_.end(); it++)
		target.draw(*it, states);
}

void EffectManager::removeFinished() {
	this->sfxs_.erase(std::remove_if(sfxs_.begin(), sfxs_.end(), 
		[](AnimatedSprite& a) { return a.getLaps() >= 1; }) , sfxs_.end());
}