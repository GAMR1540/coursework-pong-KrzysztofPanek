#include "Ball.h"

Ball::Ball(sf::Vector2f position, float radius, float speed, sf::Color color)
{
	m_speed = speed;
	m_velocity.x = speed;
	m_velocity.y = speed;
	m_shape.setRadius(radius);
	m_shape.setPosition(position);
	m_shape.setFillColor(color);
	m_shape.setOrigin(m_shape.getRadius() / 2, m_shape.getRadius() / 2);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Ball::move(float dt, sf::RenderWindow& window)
{
	//if (dt == 0)
	//{
	//	dt = 1;
	//}	
	//
	//if (m_velocity.y == 0)
	//{
	//	m_velocity.y = 1;
	//}

	m_shape.move(m_velocity * dt);

	if (m_shape.getPosition().y < 2 ||
		m_shape.getPosition().y + m_shape.getRadius() * 2 > window.getSize().y - 2)
		m_velocity.y = -m_velocity.y;
}

sf::Vector2f Ball::getPosition()
{
	return m_shape.getPosition();
}

void Ball::setPosition(float x, float y)
{
	m_shape.setPosition(x, y);
}

void Ball::updateVelocity(float val)
{
	m_velocity.x = m_speed * val;
}
int Ball::getVelocityX()
{
	return m_velocity.x;
}

int Ball::getVelocityY()
{
	return m_velocity.y;
}

sf::CircleShape Ball::getShape()
{
	return m_shape;
}

void Ball::setFillColor(sf::Color(cBall))
{
	m_shape.setFillColor(cBall);
}



