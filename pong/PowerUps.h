#pragma once
#include <SFML/Graphics.hpp>

class PowerUp
{
private:
	sf::CircleShape m_shape;
public:
	PowerUp(sf::Vector2f position, float radius, sf::Color color);
	void draw(sf::RenderWindow& window);


	sf::Vector2f getPosition();
	void setPosition(float x, float y);

	sf::CircleShape getShape();
};

