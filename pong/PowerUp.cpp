#include "PowerUp.h"


PowerUp::PowerUp(sf::Vector2f position, float radius, sf::Color color)
{
	m_shape.setRadius(radius);
	m_shape.setPosition(position);
	m_shape.setFillColor(color);
	m_shape.setOrigin(m_shape.getRadius() / 2, m_shape.getRadius() / 2);
}

void PowerUp::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}


sf::Vector2f PowerUp::getPosition()
{
	return m_shape.getPosition();
}

void PowerUp::setPosition(float x, float y)
{
	m_shape.setPosition(x, y);
}



sf::CircleShape PowerUp::getShape()
{
	return m_shape;
}




