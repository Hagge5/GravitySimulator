#include "UtilFuncs.h"

sf::Vector2<float> GetMouseCoords(sf::RenderWindow& whichWindow) {
	return whichWindow.mapPixelToCoords(sf::Mouse::getPosition(whichWindow));
}

sf::Vector2<float> V2dToV2f(sf::Vector2<double> v2d) {
	return sf::Vector2<float>(v2d.x, v2d.y);
}