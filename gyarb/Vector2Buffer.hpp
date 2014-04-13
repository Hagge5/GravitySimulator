//Does not include header file, uses the "inclusion method" to get templates working correctly
	//In other words, this file is instead included in the .h file

template<class T>
Vector2Buffer<T>::Vector2Buffer() {}

template<class T>
Vector2Buffer<T>::~Vector2Buffer() {}

template<class T>
sf::Vector2<T>* Vector2Buffer<T>::add(sf::Vector2<T> val) {

	//Inserts the new value
	this->asVector()->push_back(val);
	return &this->asVector()->at(this->asVector()->size() - 1);
}

template<class T>
sf::Vector2<T> Vector2Buffer<T>::getSum() {
	T x = 0; T y = 0;

	for(unsigned int i = 0; i < this->asVector()->size(); i++) {
		x += this->asVector()->at(i).x;
		y += this->asVector()->at(i).y;
	}

	return sf::Vector2<T>(x, y);
}

template<class T>
void Vector2Buffer<T>::clear() {
	for(unsigned int i = 0; i < this->asVector()->size(); i++)
		this->asVector()->pop_back();
}