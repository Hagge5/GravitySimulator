#pragma once

//Included dependencies
#include "UtilFuncs.h"			/* GetMouseCoords(...)				*/
#include <SFML\Graphics.hpp>	/* sf::Rect, sf::Drawable and more	*/
#include <SFML\System.hpp>		/* sf::Vector2, sf::Mouse, sf::Time */


//====================================================================
//	Widget is the base class of all buttons, and other HUD clickables

class Widget : public sf::Drawable {
public:
	Widget(sf::RenderWindow& window, sf::Rect<float> zone);
	virtual ~Widget();

	void update(sf::Time dt);				//Checks cursor location and calls appropriate methods, the hover ones. Also calls a virtual update method.
	void checkClick(sf::Vector2<float> pos);	//Call this if a mouse-click event was fired, with the position as an argument, to execute onClick().
	
	inline	sf::Rect<float>& getZone() { return this->triggerZone_; }
			void setZone(sf::Rect<float> zone);

	inline	bool hovered() const { return this->hovered_;	}

protected:
	virtual void p_draw(sf::RenderTarget &target, sf::RenderStates states) const {} //Used for drawing
	virtual void p_update(sf::Time dt) {}	//Called whenever update(...) is called. Useful for animated graphics.
	virtual void onHover()		{}			//Called once when the cursor is on the button
	virtual void onHoverStop()	{}			//Called once when the cursor is off the button
	virtual void onClick()		{}			//Called once when the widget is left-clicked
	
	inline	bool isInside(sf::Vector2<float> pos); //Checks if the given position is inside the triggerZone
	inline	bool isInside() { return this->isInside( GetMouseCoords(*this->window_));	}

	inline sf::RenderWindow* getWindow() { return this->window_; }

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		this->p_draw(target, states);
	}

	sf::RenderWindow* window_;
	sf::Rect<float> triggerZone_;
	bool hovered_;
};