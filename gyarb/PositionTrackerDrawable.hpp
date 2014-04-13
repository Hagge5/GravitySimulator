//Does not #include header file, uses the "inclusion method" to get templates working correctly
	//In other words, this file is instead #included in the .h file rather than the other way around.

template<class T>
PositionTrackerDrawable<T>::PositionTrackerDrawable(sf::Color color, float radius, sf::Vector2<T> startPos, bool limited, int limit)
	: PositionTracker<T>(startPos, limited, limit) {

	this->sprite_ = sf::CircleShape(radius, 8);
	this->sprite_.setOrigin(radius, radius);
	this->sprite_.setFillColor(color);
}

template<class T>
PositionTrackerDrawable<T>::PositionTrackerDrawable(PositionTracker t, sf::Color color, float radius)
	: PositionTracker<T>(t) {
	
	this->sprite_ = sf::CircleShape(radius, 8);
	this->sprite_.setOrigin(radius, radius);
	this->sprite_.setFillColor(color);
}

template<class T>
PositionTrackerDrawable<T>::~PositionTrackerDrawable() {}

template<class T>
void PositionTrackerDrawable<T>::draw(sf::RenderTarget& target, sf::RenderStates states) {
	
	for(int i = 0; i < this->getSize(); i++) {
		this->sprite_.setPosition((float) this->at(i).x, (float) this->at(i).y);
		target.draw(this->sprite_, states);
	}
}