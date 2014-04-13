#pragma once

//Included dependencies
#include <vector>
#include <SFML\System.hpp> /* Vector2 */

//Forward declared dependencies
	//None

//The class

template<class T> class Vector2Buffer {
public:
	Vector2Buffer();
	virtual ~Vector2Buffer();

	sf::Vector2<T>* add(sf::Vector2<T> val); //Returns pointer to the new vector
	sf::Vector2<T> getSum();

	void clear();
	inline int getSize()						const {	return this->vec_.size();	}
	inline sf::Vector2<T>* at(int i)				{	return &(this->vec_[i]);	}
	inline sf::Vector2<T>* operator[](int i)		{	return this->at(i);			}

	inline std::vector<sf::Vector2<T>>* asVector()	{	return (&(this->vec_));		}
private:
	std::vector<sf::Vector2<T>> vec_;
};

#include "Vector2Buffer.hpp"