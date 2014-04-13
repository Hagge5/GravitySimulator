#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <math.h>

//DEFINITIONS
//The templates and inline will create problems otherwise
template<class T>
inline T GetVectorSum(sf::Vector2<T> vec) {
	return sqrt((float)vec.x * vec.x + vec.y * vec.y);
}

template<class T>
inline T GetDistanceBetweenPoints(sf::Vector2<T> p1, sf::Vector2<T> p2) {
	return GetVectorSum(sf::Vector2<T>(p1.x - p2.x, p1.y - p2.y));
}

template<class T>
inline float GetAngleBetweenPoints(sf::Vector2<T> p1, sf::Vector2<T> p2) {
	return atan2((float) p2.y - p1.y, (float) p2.x - p1.x);
}

template<class T>
inline float GetAngleBetweenPointsDeg(sf::Vector2<T> p1, sf::Vector2<T> p2) {
	static const float radToDeg = 180 / 3.14159265;
	return atan2((float) p2.y - p1.y, (float) p2.x - p1.x) * radToDeg;
}

//DECLARATIONS
sf::Vector2<float> GetMouseCoords(sf::RenderWindow& whichWindow);
sf::Vector2<float> V2dToV2f(sf::Vector2<double> v2d);
