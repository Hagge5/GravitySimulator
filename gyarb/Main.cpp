#include "Scene.h"

int main() {
	sf::RenderWindow w(sf::VideoMode(960, 540), "Gravity Simulator 2014");

	//Create the scene
	Scene sc(
		&w,
		sf::milliseconds(230000), 
		1000, 
		1,
		1, 
		50,
		false, 
		2);
	
	//Let the scene execute
	sc.continousUpdate();

	return 0;
}