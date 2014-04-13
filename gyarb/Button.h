#pragma once

//Included dependencies
#include "TextureLoader.h"
#include "AnimatedSprite.h"
#include "Widget.h"				/* Base class */
#include <SFML\Graphics.hpp>	/* sf::Rect, sf::Sprite and more */
#include <SFML\System.hpp>		/* sf::Vector2, sf::Time */

class Button : public Widget {
public:
	Button(sf::Sprite* idleSprite, sf::Sprite* hoverSprite, sf::RenderWindow& window);
	Button(sf::Sprite* idleSprite, AnimatedSprite* hoverSprite, sf::RenderWindow& window);
	Button(sf::Rect<float> size, sf::RenderWindow& window); //Creates a default button
	virtual ~Button();

	inline	sf::Vector2<float>	getPosition()		const {	return this->idleSprite_->getPosition();	}
	inline	sf::Sprite*			getIdleSprite()		const {	return this->idleSprite_;					}
	inline	sf::Sprite*			getHoverSprite()	const {	return this->hoverSprite_;					}
			void				resetAnimation();

			bool				clickPending();

protected:
	virtual void p_draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void p_update(sf::Time dt);
	virtual void onHover();
	virtual void onClick();

	virtual void onHoverStop(){}			//Not used

private:
	bool clicked_;

	sf::Sprite* idleSprite_;
	sf::Sprite* hoverSprite_;

	AnimatedSprite* a_;
};