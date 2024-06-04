#include <SFML/Graphics.hpp>
#include <iostream>

class Paddle
{
private:
	float m_speed = 400.f;
	sf::Vector2f m_size;
	sf::RectangleShape m_shape;

public:
	Paddle(sf::Vector2f position, float width, float height, sf::Color color);
	void draw(sf::RenderWindow& window);
	void move(float dt, float windowYVal);
	sf::FloatRect getBounds() const;
	sf::RectangleShape getShape();

	void setSpeed(float speed);
	void setSize(float size);
	float getSpeed();
	void moveUp(float dt);
	void moveDown(float dt);
	//int getPosition();
	sf::Vector2f setPosition();
	sf::Vector2f getPosition();

};

