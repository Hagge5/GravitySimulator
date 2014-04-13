#pragma once

//Included dependencies
#include "AnimatedSprite.h"
#include "TooltippedButton.h"
#include "TooltippedSlider.h"
#include "Switch.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

//Forward declared dependencies
class Scene;

class HeadsUpDisplay {

public:
	HeadsUpDisplay(std::string tooltipFontPath, Scene* whichScene, sf::RenderWindow* whichWindow, double massMax, double mediumMass, double largeMass);
	~HeadsUpDisplay();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
	void update(sf::Time dt);
	void checkClick(sf::Vector2<int> pos);

	void onWindowResize(sf::Vector2u wsize);

	sf::View*	getView()		{ return &(this->v_);					}
	double		getMaxMass()	{ return this->addBodyMass_->getMax();	}

private:
	void checkButtons();

	Scene* scn_;
	sf::RenderWindow* wdw_;

	sf::View v_;

	//Different widgets
	TooltippedButton* addBody_;
	TooltippedSlider* addBodyMass_;

	Switch* addBodyStatic_;
	TooltippedButton* addBodyStaticTooltip_;
	
	double mediumMass_;
	double largeMass_;
	TooltippedButton* addBodySmall_;
	TooltippedButton* addBodyMedium_;
	TooltippedButton* addBodyLarge_;

	Switch* pause_;
	TooltippedButton* clear_;

	sf::Font tooltipFont_;
	std::vector<Widget*> allWidgets_;
};