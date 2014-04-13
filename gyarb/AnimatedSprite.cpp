#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture& spriteSheet, float frameWidth, float frameHeight, sf::Time timePerFrame, bool multiRow, bool bounce)
	: sf::Sprite(spriteSheet) {

		this->fwidth_ = frameWidth;
		this->fheight_ = frameHeight;
		this->ftime_ = timePerFrame;

		this->bounce_ = bounce;
		this->multiRow_ = multiRow;

		this->laps_ = 0;
		this->bufferTime_ = sf::microseconds(0);
		this->currentFrame_.x = 0;
		this->currentFrame_.y = 0;
		this->add_ = 1;

		this->update(sf::microseconds(0));
}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::update(sf::Time dt) {

	//Adding the time elapsed to the buffer.
	this->bufferTime_ += dt;

	//Check if we should move on to the next frame, multiple times if necessary.
	while(this->bufferTime_ > this->ftime_) {
		this->nextFrame();
		this->bufferTime_ -= this->ftime_;
	}

	//Setting the textureRect is what causes a certain part of the sheet, our frame, to be shown.
	this->setTextureRect(sf::IntRect(
		this->currentFrame_.x * this->fwidth_,
		this->currentFrame_.y * this->fheight_,
		this->fwidth_,
		this->fheight_));
}

void AnimatedSprite::setRow(int row) {
	this->currentFrame_.y = row;
}

void AnimatedSprite::setColumn(int column) {
	this->currentFrame_.x = column;
}

void AnimatedSprite::nextFrame() {
	float nextPosX = (this->currentFrame_.x + this->add_) * this->fwidth_;
	bool end = false;
	
	//If the next position would be outside the sheets boundries...
	if(nextPosX >= this->getTexture()->getSize().x || nextPosX <= 0) {
		//We've reached the end. How do we continue?
		if(this->multiRow_) {
			//If it is multirow, we'll need to check the Y axis as well. Pretty much same checks as above.
			float nextPosY = (this->currentFrame_.y + this->add_) * this->fheight_;
			if(nextPosY < this->getTexture()->getSize().y || nextPosY <= 0) {
				//Moving the frame in the Y position rather than x
				this->currentFrame_.y += this->add_;
				this->currentFrame_.x = -1;
			} else
				//It's not outside on the x axis, it should reset
				end = true;	
		} else
			//It's outside on the x axis and not multirow, reset.
			end = true;
	}
	
	//If we've reached the end of the animation...
	if(end) {
		//Checking if right end and incrementing laps
		if(this->add_ > 0)
			this->laps_++;

		if(!this->bounce_) { 
			//We won't bounce.
			//Set the frame to the first one.
			this->currentFrame_.x = 0;
			if(!this->multiRow_) this->currentFrame_.y = 0; //We onlt move in the Y axis through updates if we use multiRow.
			//We won't move to the next frame immidietly; return.
			return;

		} else
			//Time to bounce!
			this->add_ = -this->add_; //Reverses the direction (-(-1) = 1 and -(1) = -1)
	}

	this->currentFrame_.x += this->add_; //The next frame in the order
}