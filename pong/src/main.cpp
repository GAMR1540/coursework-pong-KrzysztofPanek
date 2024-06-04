#include <iostream>
#include "GameEngine.h"

int main()
{
	//with AA
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "P.O.N.G.", sf::Style::Default, settings);

	//sf::RenderWindow window(sf::VideoMode(800, 600), "Pong", sf::Style::Default);

	GameEngine gameEngine(window);
	gameEngine.run();
}