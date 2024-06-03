#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f position, float radius, float speed, sf::Color color)
{
	m_speed = speed;
	m_velocity.x = speed;
	m_velocity.y = speed;
	m_shape.setRadius(radius);
	m_shape.setPosition(position);
	m_shape.setFillColor(color);
	m_shape.setOrigin(m_shape.getRadius() / 2, m_shape.getRadius() / 2);
}

void PowerUp::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void PowerUp::move(float dt, sf::RenderWindow& window)
{
	m_shape.move(m_velocity * dt);

	if (m_shape.getPosition().y < 1 ||
		m_shape.getPosition().y + m_shape.getRadius() * 2 > window.getSize().y - 1)
		m_velocity.y = -m_velocity.y;
}

sf::Vector2f PowerUp::getPosition()
{
	return m_shape.getPosition();
}

void PowerUp::setPosition(float x, float y)
{
	m_shape.setPosition(x, y);
}

void PowerUp::updateVelocity(float val)
{
	m_velocity.x = m_speed * val;
}

sf::CircleShape PowerUp::getShape()
{
	return m_shape;
}

void PowerUp::setFillColor(sf::Color(cPowerUp))
{
	m_shape.setFillColor(cPowerUp);
}






//#include "PowerUp.h"
//
//
//PowerUp::PowerUp(sf::Vector2f position, float radius, sf::Color color)
//{
//	m_shape.setRadius(radius);
//	m_shape.setPosition(position);
//	m_shape.setFillColor(color);
//	m_shape.setOrigin(m_shape.getRadius() / 2, m_shape.getRadius() / 2);
//}
//
//void PowerUp::draw(sf::RenderWindow& window)
//{
//	window.draw(m_shape);
//}
//
//
//sf::Vector2f PowerUp::getPosition()
//{
//	return m_shape.getPosition();
//}
//
//void PowerUp::setPosition(float x, float y)
//{
//	m_shape.setPosition(x, y);
//}
//
//
//
//sf::CircleShape PowerUp::getShape()
//{
//	return m_shape;
//}
//
//
//
//
