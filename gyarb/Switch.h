#pragma once

#include "TextureLoader.h"
#include "AnimatedSprite.h"
#include "Button.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>


class Switch : public Button {
public:
	Switch(sf::Sprite* onSprite, sf::Sprite* offSprite, sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window, bool initVal = false);
	Switch(sf::Sprite* onSprite, sf::Sprite* offSprite, sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window, bool initVal = false);
	Switch(sf::FloatRect size, sf::RenderWindow& window, bool initVal = false); //Creates a default checkbox
	~Switch();

	inline	void invert()	{ this->isOn_ = !this->isOn_;	}
	inline	void turnOff()	{ this->isOn_ = false;			}
	inline	void turnOn()	{ this->isOn_ = true;			}

	bool isOn() const		{ return this->isOn_; }

protected:
	virtual void onClick();
	virtual void p_draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void p_update(sf::Time dt);
	virtual void onHover();

	virtual void onHoverStop(){}			//Not used
private:
	bool isOn_;
	sf::Sprite* onSprite_;
	sf::Sprite* offSprite_;
};