#include <SFML/Graphics.hpp>

class PowerUp
{
private:
	float m_speed;
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
public:
	PowerUp(sf::Vector2f position, float radius, float speed, sf::Color color);
	void draw(sf::RenderWindow& window);
	void move(float dt, sf::RenderWindow& window);

	sf::Vector2f getPosition();
	void setPosition(float x, float y);

	void updateVelocity(float val);
	sf::CircleShape getShape();

	void setFillColor(sf::Color(cPowerUp));

};




//#pragma once
//#include <SFML/Graphics.hpp>
//
//class PowerUp
//{
//private:
//	sf::CircleShape m_shape;
//public:
//	PowerUp(sf::Vector2f position, float radius, sf::Color color);
//	void draw(sf::RenderWindow& window);
//
//
//	sf::Vector2f getPosition();
//	void setPosition(float x, float y);
//
//	sf::CircleShape getShape();
//};
//
