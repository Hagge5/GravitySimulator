//Does not #include header file, uses the "inclusion method" to get templates working correctly
	//In other words, this file is instead #included in the .h file rather than the other way around.


//====================
//CONSTRUCTOR / DESTRUCTOR
//====================

template<class T>
PositionTracker<T>::PositionTracker(sf::Vector2<T> startPos, bool limited, int limit) {
	this->limited_ = limited;
	this->limit_ = limit;

	for(int i = 0; i < ALWAYS_KEEP_COUNT; i++)
		this->queue_.push_front(startPos);
}

template<class T>
PositionTracker<T>::~PositionTracker() {}


//====================
//NEW POS
//====================

template<class T>
void PositionTracker<T>::addPos(sf::Vector2<T> pos) {
	this->push_front(pos);

	if (this->isLimited() && this->getSize() > this->getLimit())	//We enforce the limit; if we have more elements than allowed...
		this->pop_back();	//... we remove the oldest element, i.e the one in the back.
}

template<class T>
void PositionTracker<T>::addPos(T x, T y) {
	this->addPos(sf::Vector2<T>(x, y));
}


//====================
//CLEAR
//====================


template<class T>
void PositionTracker<T>::clearAll() {
	for(int i = 0; i < this->getSize(); i++)
		this->pop_back();
}

template<class T>
bool PositionTracker<T>::clearAmount(int am = 1) {
	if (am > this->getSize() - this->ALWAYS_KEEP_COUNT); //Can't clear more than allowed keep count
		return false;

	for(int i = 0; i < am; i++)
		this->pop_back();

	return true;
}

template<class T>
void PositionTracker<T>::safeClearAll() {
	this->clearAmount(this->getSize() - this->ALWAYS_KEEP_COUNT);
}

//====================
//LIMIT-RELATED
//====================

template<class T>
void PositionTracker<T>::disableLimit() {
	return this->limited_ = false;
}

template<class T>
void PositionTracker<T>::enableLimit() {
	return this->limited_ = true;
}

template<class T>
void PositionTracker<T>::setLimit(int limit) {
	this->limit_ = limit;
	this->disableLimit();
}

//====================
//PROTECTED
//====================

template<class T>
void PositionTracker<T>::push_front(sf::Vector2<T> pos) {
	this->queue_.push_front(pos);
}

template<class T>
void PositionTracker<T>::pop_back() {
	this->queue_.pop_back();
}