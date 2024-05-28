#include "GameEngine.h"

#include <iostream>
#include <random>
#include <windows.h>

using namespace std;

GameEngine::GameEngine(sf::RenderWindow& window) 
	: m_window(window),
	m_paddle1(sf::Vector2f(20, window.getSize().y / 2.f), 10, 100, sf::Color::Blue),
	m_paddle2(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y -100.f), 10, 100, sf::Color::Red),
	m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow)
{
	m_p1Score = 0;
	m_p2Score = 0;
	m_gStates = GameStates::intro;
	m_font.loadFromFile(".\\assets\\fonts\\digital-7.ttf");
	m_hud.setFont(m_font);
	m_hud.setCharacterSize(50);
	m_hud.setFillColor(sf::Color::White);

	m_hud.setPosition((m_window.getSize().x / 2.f) - 45.f, 10);

	m_paddle1.setSpeed(1000.f);
	m_paddle2.setSpeed(1000.f);
	
}

void GameEngine::draw()
{
	m_window.clear();
	m_paddle1.draw(m_window);
	m_paddle2.draw(m_window);
	m_ball.draw(m_window);
	m_window.draw(m_hud);
	m_window.display();
}
void GameEngine::rand128()
{
	//random AI
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 127);
	int random_number = dis(gen);


}

void GameEngine::update()
{
	// update hud
	std::stringstream ss;
	switch (m_gStates)
	{
	case GameEngine::intro:
		ss << "Press the Space\nkey to start";
		break;
	case GameEngine::playing:
		ss << m_p1Score << " - " << m_p2Score;
		break;
	case GameEngine::gameOver:
		if (m_p1Score > m_p2Score) {
			ss << "Player 1 wins";
		}
		else {
			ss << "Player 2 wins";
		}
		break;
	default:
		break;
	}
		
	m_hud.setString(ss.str());
}

void GameEngine::run()
{
	float dt;

	while (m_window.isOpen())
	{
		dt = m_clock.restart().asSeconds();

		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) m_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				m_gStates = GameStates::playing;
		}
		if (m_gStates == 1)
		{
		// ADD YOUR CODE HERE !!!
		
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			cout << "UP key pressed" << endl;
			m_paddle1.move(0, -m_paddle1.getSpeed() * dt);
		}*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_paddle1.moveUp(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_paddle1.moveDown(dt);
		}

		if ((m_ball.getPosition().x < 0))
		{
			m_p2Score++;

			//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		}
		if ((m_ball.getPosition().x > 800))
		{
			m_p1Score++;

			//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		}


		//AI
		if ((m_ball.getPosition().x < 0)||(m_ball.getPosition().x > 800))
		{
			m_ball.setPosition(800 / 2.f, 600 / 2.f);

			//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		}
		 


		 
		 
		 
		 
		//random AI
		// Get the mouse position relative to the desktop
		//sf::Vector2i mousePositionDesktop = sf::Mouse::getPosition();
		//random_device rd;
		//mt19937 gen(rd());
		//int rnd_max = 127 + mousePositionDesktop.y;
		//uniform_int_distribution<> dis(0, rnd_max);
		//int random_number = dis(gen);
		//cout << random_number << endl;
		////if ((random_number > rnd_max - rnd_max * 0.1) && (m_paddle2.getPosition().y < 600))
		//if (random_number > rnd_max-rnd_max*0.2)
		//{
		//	//move_up
		//	m_paddle2.moveUp(dt/5);
		//	//Sleep(100);
		//}
		////else if ((random_number < rnd_max * 0.11) && (m_paddle2.y < 600))
		//else if (random_number < rnd_max * 0.21)
		//{
		//	//move_down

		//	m_paddle2.moveDown(dt/5);
		//	//Sleep(100);
		//}
		/*
		//if (random_number > rnd_max * 0.95)
		if (random_number > 200)
		{
			//random AI -- easy mode

				//if ((random_number > rnd_max - rnd_max * 0.1) && (m_paddle2.getPosition().y < 600))
			if (random_number > rnd_max - rnd_max * 0.5)
			{
				//move_up
				m_paddle2.moveUp(dt / 5);
				//Sleep(100);
			}
			//else if ((random_number < rnd_max * 0.11) && (m_paddle2.y < 600))
			else if (random_number < rnd_max * 0.51)
			{
				//move_down

				m_paddle2.moveDown(dt / 5);
				//Sleep(100);
			}
		}
		else
		{
			//impossible
			//m_paddle2.getPosition.y() = m_ball.getPosition.y();
			//m_paddle2.setPosition(m_paddle2.getPosition().x, m_ball.getPosition().y);


		}*/

		
			m_ball.move(-dt, m_window);


			if ( m_paddle1.getBounds().contains(m_ball.getPosition()))
			{
				m_ball.updateVelocity(-1);
			}


			if (m_paddle2.getBounds().contains(m_ball.getPosition()))
			{
				m_ball.updateVelocity(1);
			}
		
		}
		
		//if (m_paddle2.getBounds().height)
		//{
		//	m_ball.move(-dt, m_window);
		//	
		//}

		//float p1y=m_paddle1.getPosition().y

		//if (m_ball.getPosition() < m_paddle1.getPosition())
		// update hud
		update();
		// draw shapes to screen
		draw();
	}
}
