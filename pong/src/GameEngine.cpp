#include "GameEngine.h"

#include <iostream>
#include <random>
#include <windows.h>

using namespace std;

int ballSize = 8;

GameEngine::GameEngine(sf::RenderWindow& window) 
	: m_window(window),
	m_paddle1(sf::Vector2f(20, window.getSize().y / 2.f), 10, 100, sf::Color::Blue),
	m_paddle2(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y -100.f), 10, 100, sf::Color::Red),
	m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), ballSize, 400.f, sf::Color::Yellow),
	m_ball2(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), ballSize, 400.f, sf::Color::Yellow)//,
	//error m_powerUp(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 16, 400.f, sf::Color orange(255, 160, 0)),
	
{
	m_p1Score = 0;
	m_p2Score = 0;
	ai = false;
	m_diff = 0;
	m_viewDist = 0;
	m_defend = 0;
	rnd_max = 800;
	ball2=true;
	//sf::Color orange(255, 160, 0);
	sf::Color c(0, 0, 0);

	m_gStates = GameStates::intro;
	m_font.loadFromFile(".\\assets\\fonts\\digital-7.ttf");
	m_hud.setFont(m_font);
	m_hud.setCharacterSize(255);
	//m_hud.setFillColor(sf::Color::White);
	m_hud.setFillColor(c);

	m_hud.setPosition((m_window.getSize().x / 6.f) - 45.f, 10);

	m_paddle1.setSpeed(1000.f);
	m_paddle2.setSpeed(1000.f);
	
}

void GameEngine::draw()
{
	m_window.clear();
	m_paddle1.draw(m_window);
	m_paddle2.draw(m_window);
	m_ball.draw(m_window);
	m_ball2.draw(m_window);
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
		ss << "P.O.N.G.";
		break;	
	case GameEngine::mainMenu:
		//ss << "Press the Space\nkey to start";
		ss << "    P.O.N.G.\n\n\nQ - 1 Player\nA - 2 Player\n\nZ - Top10\n\nEsc - Quit";
		break;
	case GameEngine::vsAi:
		//ss << "Press the Space\nkey to start";
		ss << "    P.O.N.G.\n\n\nChoose how smart\nis ypur opponent:\n\n1  - Amoeba\n2 - Noob\n3 - Pro\n4 - Terminator\n";
		break;
	case GameEngine::top10:
		//ss << "Press the Space\nkey to start";
		ss << "    P.O.N.G.\n\n\nTop 10\n";
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
	//}
	

	m_hud.setString(ss.str());
}

void GameEngine::run()
{
	float dt;
	float spd = 1;
	int countD = 50;
	float r = 0;
	float g = 0;
	float b = 0;
	while (m_window.isOpen())
	{
		dt = m_clock.restart().asSeconds();
		if (m_gStates == 0)
		{
			sf::Color c(r, g, b);
			m_hud.setFillColor(c);
			countD--;
			cout << countD << endl;
			if (r < 255) r+=0.025;
			//else if (g < 255) g += 0.1;
			//else if (b < 255) b += 0.1;
			else
			{
				g = 255;
				b = 255;
				sf::Color c(r, g, b);
				m_hud.setFillColor(c);
				//default m_hud.setPosition((m_window.getSize().x / 2.f) - 45.f, 10);
				m_hud.setPosition((m_window.getSize().x / 2.f) - 70.f, 10);
				m_hud.setCharacterSize(40);
				m_gStates = GameStates::mainMenu;
			}
		}
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) m_window.close();

			//m_gStates = GameStates::intro
			if (m_gStates == 0)
			{

				/*sf::Color c(r, g, b);
				m_hud.setFillColor(c);*/

				//if (countD < 1) m_gStates = GameStates::mainMenu;
				
				//if (event.type == sf::Event::Closed) m_window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}

			//m_gStates = GameStates::mainMenu
			if (m_gStates == 1)
			{
				//if (event.type == sf::Event::Closed) m_window.close();
				//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				//	m_window.close();

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
				{
					m_gStates = GameStates::vsAi;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
				{
					m_gStates = GameStates::mPlayer;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
				{
					m_gStates = GameStates::mainMenu;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}

			}

			//m_gStates = GameStates::vsAi
			if (m_gStates == 2)
			{
				//if (event.type == sf::Event::Closed) m_window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;
				//if (event.type == sf::Event::KeyPressed && ((event.key.code == sf::Keyboard::Num1) || (event.key.code == sf::Keyboard::Num2) || (event.key.code == sf::Keyboard::Num3)))
				//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				
				//turn on AI
				ai = true;
				
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
				{
					m_diff = 4;
					m_viewDist = 600;
					int rnd_max = 800;
					int rnd_min = 600;
					spd = 0.5;
					ballSize = 12;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
				{
					m_diff = 3;
					m_viewDist = 300;
					int rnd_max = 700;
					int rnd_min = 300;
					spd = 0.75;
					ballSize = 10;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
				{
					m_diff = 2;
					m_viewDist = 300;
					int rnd_max = 700;
					int rnd_min = 300;
					spd = 1;
					ballSize = 8;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
				{
					m_diff = 1;
					m_viewDist = 100;
					int rnd_max = 300;
					int rnd_min = 0;
					spd = 1.5;
					ballSize = 6;
				}


				if (m_diff != 0)
					//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
					m_gStates = GameStates::playing;
			}
			//m_gStates = GameStates::mPlayer
			if (m_gStates == 3)
			{
				//if (event.type == sf::Event::Closed) m_window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;

				//turn off AI
				ai = false;
				
				//m_diff = 0;
				m_gStates = GameStates::playing;

			}

			//m_gStates = GameStates::top10
			if (m_gStates == 7)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;

				m_gStates = GameStates::top10;

			}
		}

		//m_gStates = GameStates::playing
		if (m_gStates == 4)
		{
			/*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_gStates = GameStates::mainMenu;*/
			//cout << m_diff;
		// ADD YOUR CODE HERE !!!
		
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			cout << "UP key pressed" << endl;
			m_paddle1.move(0, -m_paddle1.getSpeed() * dt);
		}*/
		
		//menu , pause in future	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_gStates = GameStates::mainMenu;
		}	
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_paddle1.moveUp(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_paddle1.moveDown(dt);
		}

		// increse player score
		if ((m_ball.getPosition().x < 0))
		{
			m_p2Score++;

			//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		}
		else if ((m_ball.getPosition().x > 800))
		{
			m_p1Score++;

			//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		}

		//Score for 2nd ball
		//if (ball2)
		//{
		//	if ((m_ball2.getPosition().x < 0))
		//	{
		//		m_p2Score++;

		//		//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
		//		//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		//	}
		//	else if ((m_ball2.getPosition().x > 800))
		//	{
		//		m_p1Score++;

		//		//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
		//		//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		//	}
		//}

		//Restet ball position
		if ((m_ball.getPosition().x < 0)||(m_ball.getPosition().x > 800))
		{
			//random AI
					// Get the mouse position relative to the desktop
			//sf::Vector2i mousePositionDesktop = sf::Mouse::getPosition();
			if (ai)
			{	random_device rd;
				mt19937 gen(rd());
				//int rnd_max = 127 + mousePositionDesktop.y;
				/*int rnd_max = 800;*/

				uniform_int_distribution<> dis(300, rnd_max);
				//int m_viewDist = dis(gen);
				m_viewDist = dis(gen);
				if (m_diff== 1) if (m_viewDist>720) m_viewDist = 800;
				if (m_diff== 2) if (m_viewDist < 520 || (m_viewDist < 710 && m_viewDist>680)) m_viewDist = 800;
				if (m_diff== 3) if (m_viewDist < 50) m_viewDist = 800;
				if (m_diff == 4)
				{
					if (m_viewDist < 32)
					{
						m_viewDist = 800;
					}
					else if (m_viewDist >400)
					{
						m_viewDist = 200;
					}
				}
				cout << m_viewDist << endl; 
			}
			
			m_ball.setPosition(800 / 2.f, 600 / 2.f);
			if (ball2)
			{
				m_ball2.setPosition(800 / 4.f, 600 / 4.f); 
			}
			

			//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
		}
		 
		//AI
		if (m_ball.getPosition().x > m_viewDist && (m_ball.getPosition().y < m_paddle2.getPosition().y))
		{
			m_paddle2.moveUp(dt / m_diff);
		}		
		else if (m_ball.getPosition().x> m_viewDist && (m_ball.getPosition().y > m_paddle2.getPosition().y))
		{
			m_paddle2.moveDown(dt / m_diff);
		}
		//AI for 2nd BALL
		if (ball2)
		{
			if (m_ball2.getPosition().x > m_viewDist && (m_ball2.getPosition().y < m_paddle2.getPosition().y))
			{
				m_paddle2.moveUp(dt / m_diff);
			}
			else if (m_ball2.getPosition().x > m_viewDist && (m_ball2.getPosition().y > m_paddle2.getPosition().y))
			{
				m_paddle2.moveDown(dt / m_diff);
			}
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
			if (ball2)
			{
				m_ball2.move(-dt, m_window);
			}
			
			///bounce ball 1

			if ( m_paddle1.getBounds().contains(m_ball.getPosition()))
			{
				if (ai)
				{
					random_device rd;
					mt19937 gen(rd());
					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = 800;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = 800;
					cout << m_viewDist << endl;
				}

				if (m_diff > 1) spd += 0.01;
				m_ball.updateVelocity(-spd);

				
			}


			if (m_paddle2.getBounds().contains(m_ball.getPosition()))
			{
				if (ai)
				{
					random_device rd;
					mt19937 gen(rd());
					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = 800;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = 800;
					cout << m_viewDist << endl;
				}
				
				
				if (m_diff > 1) spd += 0.01;
				m_ball.updateVelocity(spd);
			}


			///////bounce ball2
			if (m_paddle1.getBounds().contains(m_ball2.getPosition()))
			{
				if (ai)
				{
					random_device rd;
					mt19937 gen(rd());
					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = 800;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = 800;
					cout << m_viewDist << endl;
				}

				if (m_diff > 1) spd += 0.01;
				m_ball2.updateVelocity(-spd);


			}


			if (m_paddle2.getBounds().contains(m_ball2.getPosition()))
			{
				if (ai)
				{
					random_device rd;
					mt19937 gen(rd());
					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = 800;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = 800;
					cout << m_viewDist << endl;
				}


				if (m_diff > 1) spd += 0.01;
				m_ball2.updateVelocity(spd);
			}

			if (m_p1Score>19 || m_p2Score > 19)
			{
				m_gStates= GameEngine::gameOver;
			}
		
		}

		//////powerups
		//errorif (m_powerup.getBounds().contains(m_ball.getPosition()))
		/*{
			//bigball
			ballSize=20;
			//smallball
			ballSize=5;

			//slowball
			spd/=2;
			m_ball.updateVelocity(spd);
		}
		*/
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
