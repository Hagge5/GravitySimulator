#pragma once

//Included dependencies
#include "Arrow.h"
#include "UtilFuncs.h"
#include "TextureLoader.h"
#include "EffectManager.h"
#include "BodySystem.h"
#include "HeadsUpDisplay.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

class Scene {
public:
	Scene(sf::RenderWindow* window, sf::Time dt, int ups, float objectScale, float sfxScale, double massMax, bool showTrails = true, int trailLimit = 2048);
	virtual ~Scene();

	void update();
	void continousUpdate();
	
	inline sf::RenderWindow*	getWindow()		{ return this->wdw_;		}
	inline sf::View*			getPlanetView()	{ return &(this->view_);	}
	
	AnimatedSprite* addExplosion(sf::Vector2<float> pos);
	void userCreateBody(double mass, bool isStatic);

	void clear();

	inline bool isPaused()	  const { return this->paused_;	}
	inline void pause()				{ this->paused_ = true; }
	inline void unPause()			{ this->paused_ = false;}
	inline void setPause(bool b)	{ this->paused_ = b;	}

private:

	//MEMBERS
	float objectScale_;
	bool paused_;
	bool wantExit_;
	bool showTrails_;

	sf::Time bufferTime_;
	sf::Time dt_;
	sf::Time frametimePerUpdate_;

	sf::RenderWindow* wdw_;
	sf::View view_;
	sf::Clock clock_;

	sf::Sprite backGround_;
	EffectManager explosions_;
	BodySystem* bodSys_;
	HeadsUpDisplay* hud_;

	//METHODS
	GravitationalBodyDrawable* addBody(double mass, bool isStatic, sf::Vector2<double> pos, sf::Vector2<double> initVeloc = sf::Vector2<double>(0, 0), bool scale = true);

	void draw(sf::Time future);
	void eventPoll();

	void loadTextures();
	void initDefaults();
	void resizeBackground();

	std::string determineTexture(double mass);
	
	//CONSTANTS
	static const float		TRAIL_RADIUS;					//2039203
	static const sf::Color	TRAIL_COLOR;					//sf::Color::White
	static const int		UPDATE_FRAMETIME_MAX;			//0,25 seconds (250000 microseconds)
	static const float		BODY_CONSTANT_SCALE;			//0.0008
	static const double		DESTROY_RECT_ADDITIONAL_SIZE;	//0.1
	static const double		DESTROY_BODY_COLLISION_RANGE;	
	static const float		VIEWCORDS_PER_PIXEL;			//0.016

	static const double		BODY_PLANET_BREAKOFF_PERCENT;	
	static const double		BODY_SUN_BREAKOFF_PERCENT;		
};