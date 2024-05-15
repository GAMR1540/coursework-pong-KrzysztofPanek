#include "Paddle.h"

Paddle::Paddle(sf::Vector2f position, float width, float height, sf::Color color)
{
	m_size.x = width;
	m_size.y = height;
	m_shape.setSize(m_size);
	m_shape.setPosition(position);
	m_shape.setFillColor(color);
	m_shape.setOrigin(m_shape.getSize() / 2.f);
}

void Paddle::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Paddle::move(float dt, float windowYVal)
{	
	//default
	//move up
	//if (m_shape.getPosition().y - m_shape.getSize().y / 2 > windowYVal)
	//	m_shape.move(0, -m_speed * dt);
	//// move down
	//if (m_shape.getPosition().y + m_shape.getSize().y / 2 < windowYVal)
	//	m_shape.move(0, m_speed * dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		int y=m_shape.getPosition().y;
		y--;
	}
}

sf::FloatRect Paddle::getBounds() const
{
	return m_shape.getGlobalBounds();
}

sf::RectangleShape Paddle::getShape()
{
	return m_shape;
}

void Paddle::setSpeed(float speed)
{
	m_speed = speed;
}
