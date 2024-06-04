#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f position, float width, float height, sf::Color color)
{
	m_size.x = width;
	m_size.y = height;
	m_shape.setSize(m_size);
	m_shape.setPosition(position);
	m_shape.getPosition();
	m_shape.setFillColor(color);
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.getPosition();
	//m_shape.setPosition();
}

void PowerUp::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void PowerUp::move(float dt, float windowYVal)
{
	//default
	////move up
	//if (m_shape.getPosition().y - m_shape.getSize().y / 2 > 0)
	//	m_shape.move(0, -m_speed * dt);
	////// move down
	//if (m_shape.getPosition().y + m_shape.getSize().y / 2 < window.getSize().y)
	//	m_shape.move(0, m_speed * dt);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//{
	//	int y=m_shape.getPosition().y;
	//	y--;
	//}
}

void PowerUp::moveUp(float dt)
{
	if (m_shape.getPosition().y - m_shape.getSize().y / 2 > 0)
		m_shape.move(0, -m_speed * dt);
}

void PowerUp::moveDown(float dt)
{//window.getSize().y
	if (m_shape.getPosition().y + m_shape.getSize().y / 2 < 600)
		m_shape.move(0, m_speed * dt);
}

sf::FloatRect PowerUp::getBounds() const
{
	return m_shape.getGlobalBounds();
}

sf::RectangleShape PowerUp::getShape()
{
	return m_shape;
}

void PowerUp::setSpeed(float speed)
{
	m_speed = speed;
}

float PowerUp::getSpeed()
{
	return m_speed;
}

sf::Vector2f PowerUp::getPosition()
{
	return m_shape.getPosition();
}


//#include "PowerUp.h"
//
//PowerUp::PowerUp(sf::Vector2f position, float radius, float speed, sf::Color color)
//{
//	m_speed = speed;
//	m_velocity.x = speed;
//	m_velocity.y = speed;
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
//void PowerUp::move(float dt, sf::RenderWindow& window)
//{
//	m_shape.move(m_velocity * dt);
//
//	if (m_shape.getPosition().y < 1 ||
//		m_shape.getPosition().y + m_shape.getRadius() * 2 > window.getSize().y - 1)
//		m_velocity.y = -m_velocity.y;
//}
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
//void PowerUp::updateVelocity(float val)
//{
//	m_velocity.x = m_speed * val;
//}
//
//sf::CircleShape PowerUp::getShape()
//{
//	return m_shape;
//}
//
//void PowerUp::setFillColor(sf::Color(cPowerUp))
//{
//	m_shape.setFillColor(cPowerUp);
//}
//
//
//



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
