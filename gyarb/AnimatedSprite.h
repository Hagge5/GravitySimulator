#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class AnimatedSprite : public sf::Sprite {
public:
	AnimatedSprite(sf::Texture& spriteSheet, float frameWidth, float frameHeight, sf::Time timePerFrame, bool multiRow = true, bool bounce = false);
	~AnimatedSprite();

	void update(sf::Time dt);
	void setRow(int row);
	void setColumn(int column);

	inline int getLaps() const { return this->laps_; }

private:

	//Methods
	void nextFrame();

	//Members
	int laps_;
	float fwidth_;
	float fheight_;
	sf::Time ftime_;

	sf::Time bufferTime_;
	sf::Vector2<int> currentFrame_;

	bool bounce_;
	bool multiRow_;
	int add_; //The number that's added on next frame, either +1 or -1.
};

/*=======================
//SHORT SUMMARY
//=======================

The class animates a spritesheet. It only find new frames in the x-axis to accomodate to multiple
animation sequences within the same sheet.

Make a sheet where each cell has a fixed size, and the frames follow one another from left to right
for the simplest animation possible.

If bounce is enabled, the animation will do the sequence in reverse rather than start over when it reaches the end.

What multirow does is, when enabled, causes the animation to go through all the frames rather than just them on a single row.

========================*/