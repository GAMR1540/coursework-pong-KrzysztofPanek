#include "GameEngine.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <windows.h>

using namespace std;

//Some vars must be set outside GameEngine class
// 
//default ball size
int ballSize = 8;

// initial powerUp position
 int powerUp_x=-200;
 int powerUp_y=-200;

//initialise random number gen
random_device rd;
mt19937 gen(rd());




GameEngine::GameEngine(sf::RenderWindow& window) 
	: m_window(window),
	m_paddle1(sf::Vector2f(20, window.getSize().y / 2.f), 10, 100, sf::Color::Cyan),
	m_paddle2(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y - 100.f), 10, 100, sf::Color::Magenta),
	m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), ballSize, 400.f, sf::Color::Yellow),
	m_ball2(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), ballSize, 400.f, sf::Color::Yellow),
	//m_ball2(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), ballSize, 400.f, sf::Color(100, 100, 100,0))/*RGBA default transparent ball2*/,
	m_powerUp(sf::Vector2f(powerUp_x, powerUp_y), 32, 32, sf::Color::Green)
{
	// set default Position of image
	imgX = -20.f;  
	imgX1 = window.getSize().x - 320.f;
	imgY = 0.f;
	dirDown = true;

	//set up to draw an image
	png.loadFromFile(".\\assets\\gfx\\MyHeadQuater.png");
	img.setTexture(png);
	img1.setTexture(png);
	img.setPosition(imgX, imgY);
	img1.setPosition(imgX1, imgY);

	//score innitial values
	scored = false;
	scored_timeout = 1200;

	//colors
	ballR = 0;
	ballG = 0;
	ballB = 0;

	sf::Color cBall(ballR, ballG, ballB);

	//if gameplay sytrated >0
	game_start = 0;


	//game couver counter
	//gOverCounter = 13000;

	//for pause game
	///true if game has been stared
	paused = false;
	//prevent returng to game by mistake
	pause_delay = 2;

	// powerup vars
	powerUp_hide = 0;
	powerUp_create = 100;
	powerUp_exist = false;
	powerUp_set = false;

	//score fo player1 and p2
	m_p1Score = 0;
	m_p2Score = 0;

	//true when playing with AI
	//false when PvP
	ai = false;

	//Difficulty
	m_diff = 0;

	//distance of view of enemy
	m_viewDist = 0;


	// max random number
	rnd_max = m_window.getSize().y;

	//true when 2nd ball is in game
	//default false
	ball2=false;

	//draw fake ball txt
	fball_counter = 2000;

	//intro music turned on
	introSound_done = false;

	//default player name
	// for TOP5
	char playerName[6] = "D.M.U";

	//tmp colors
	sf::Color c(0, 0, 0);

	//AUDIO
	//create sound buffers 
	///loops are not mine, but according to license for non-commercial purposes doesn't need attribution.
	//other sound i made by myself mixing in Audacity.
	m_ballSound.setBuffer(m_ballBuffer);
	m_ballBuffer.loadFromFile(".\\assets\\audio\\pong_bounce.wav");
	m_goalSound.setBuffer(m_goalBuffer);
	m_goalBuffer.loadFromFile(".\\assets\\audio\\pong_goal.wav");	
	m_goverSound.setBuffer(m_goverBuffer);
	m_goverBuffer.loadFromFile(".\\assets\\audio\\pong_gover.wav");	
	m_introSound.setBuffer(m_introBuffer);
	m_introBuffer.loadFromFile(".\\assets\\audio\\pong_intro.wav");	
	m_drumsSound.setBuffer(m_drumsBuffer);
	m_drumsBuffer.loadFromFile(".\\assets\\audio\\pong_drumsloop0.ogg");
	m_SoundtrackSound.setLoop(true);	
	m_SoundtrackSound.setBuffer(m_SoundtrackBuffer);
	m_SoundtrackBuffer.loadFromFile(".\\assets\\audio\\pong_rockloop0.ogg");
	m_SoundtrackSound.setLoop(true);

	//intro
	m_gStates = GameStates::intro;
	m_font.loadFromFile(".\\assets\\fonts\\digital-7.ttf");
	m_hud.setFont(m_font);
	//set characters size for intro
	m_hud.setCharacterSize(255);
	//m_hud.setFillColor(sf::Color::White);
	m_hud.setFillColor(c);
	// change hud position
	m_hud.setPosition((m_window.getSize().x / 6.f) - 45.f, 10);

	//set speed of paddles
	m_paddle1.setSpeed(1000.f);
	m_paddle2.setSpeed(1000.f);
	
}

// draw game objects on the screen (hud etc.)
void GameEngine::draw()
{
	m_window.clear();
	//draw bg
	sf::RectangleShape bg(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	bg.setFillColor(sf::Color(0, 100, 30));
	bg.setPosition(0, 0);
	m_window.draw(bg);

	//drawing code for menus
	if (m_gStates > 0 && m_gStates < 4)
	{
		//set up hud
		m_hud.setPosition((m_window.getSize().x / 2.f) - 90.f, 10);
		
		//draw menu side lines
		sf::RectangleShape sideLineL(sf::Vector2f(8, m_window.getSize().y));
		sf::RectangleShape sideLineR(sf::Vector2f(8, m_window.getSize().y));
		sideLineL.setFillColor(sf::Color(100, 100, 100));
		sideLineR.setFillColor(sf::Color(100, 100, 100));
		sideLineL.setPosition(200, 0);
		m_window.draw(sideLineL);
		sideLineR.setPosition(m_window.getSize().y, 0);
		m_window.draw(sideLineR);

		//change img position
		if (dirDown)
		{
			if (imgY < m_window.getSize().y - 300) imgY += 0.1;
			else dirDown = false;
		}
		else
		{
			if (imgY > 1) imgY -= 0.1;
			else dirDown = true;
		}

		// Draw the image
		img.setPosition(imgX, imgY);
		img1.setPosition(imgX1, imgY);
		m_window.draw(img);
		m_window.draw(img1);
	}
	// draw image in intro 	
	if (m_gStates == 0)
	{
		// Draw the image
		img.setPosition(((m_window.getSize().x / 2.f) - 200.f), 250.f);
		m_window.draw(img);

		//reset balls position (just in case)
		m_ball.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
		m_ball2.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
	}
	// draw image when scored or game over
	if (scored == true || m_gStates == 5)
	{
		// Draw the image
		if (m_gStates == 5) m_hud.setPosition((m_window.getSize().x / 2.f) - 180.f, 10);
		img.setPosition(((m_window.getSize().x / 2.f) - 200.f), 100.f);
		m_window.draw(img);
	}
		
	if (m_gStates == 4)
	{
		//draw halfway line
		sf::RectangleShape halfWayLine(sf::Vector2f(8, m_window.getSize().y));
		halfWayLine.setFillColor(sf::Color(100, 100, 100));
		halfWayLine.setPosition(400, 0);
		
		//draw circle on the middle of field
		sf::CircleShape centerCircle(50);
		centerCircle.setFillColor(sf::Color(100, 100, 100));
		centerCircle.setPosition(355, 250);
		
		//draw circle on the middle of field
		sf::CircleShape centerCircle1(42);
		centerCircle1.setFillColor(sf::Color(0, 100, 30));
		centerCircle1.setPosition(360, 260);
		

		// hide markings when scored
		if (scored == false)
		{
			m_window.draw(halfWayLine);
			m_window.draw(centerCircle);
			m_window.draw(centerCircle1);
		}

		//POWERUP
		if (powerUp_create < 32 || powerUp_exist)
		{
			if (powerUp_set==false)
			{
				powerUp_hide = 10000;
				powerUp_exist = true;

				////set powerup random position 
				uniform_int_distribution<> disPX(100, 700);
				int powerUp_x = disPX(gen);
				uniform_int_distribution<> disPY(100, 500);
				int powerUp_y = disPY(gen);
				powerUp_set = true;
			}

			 
			m_powerUp.setPosition(powerUp_x, powerUp_y);

			//shaking powerup
			uniform_int_distribution<> disPbgX(-20, 20);
			int powerUp_shakeX = disPbgX(gen);
			uniform_int_distribution<> disPbgY(-20, 20);
			int powerUp_shakeY = disPbgY(gen);
			m_powerUp.setPosition(powerUp_x+ powerUp_shakeX, powerUp_y+ powerUp_shakeY);


			
		}
		if (powerUp_exist && powerUp_hide > 0 && !scored) m_powerUp.draw(m_window);
		
		m_paddle1.draw(m_window);
		m_paddle2.draw(m_window);
		m_ball.draw(m_window);
		if (ball2) m_ball2.draw(m_window);

		
	}
	m_window.draw(m_hud);
	m_window.display();
}

//set up random numbers gen for 128 
void GameEngine::rand128()
{
	//random AI
	uniform_int_distribution<> dis(0, 127);
	int random_number = dis(gen);
}

void GameEngine::update()
{
	// update hud
	stringstream ss;


	//top 5
	// read from top 5 file
	string top5File = "top.5";
	ifstream inputFile(top5File);

	//if file doesnt extst create default one;
	if (!inputFile.is_open())
	{
		ofstream outputFile(top5File);

		if (outputFile.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				outputFile << "D M U 000000\n";
			}
			outputFile.close();
			//cout << "default top5 file has benn created";
		}

	}

	//string record;
	// 
		// Use a stringstream to read the entire file content
	ostringstream buffer;
	buffer << inputFile.rdbuf();

	// Store the content in a string
	string records = buffer.str();

	/////


	switch (m_gStates)
	{
	case GameEngine::intro:
		ss << "P.O.N.G.";
		break;		
	case GameEngine::nick:
		ss << "P.O.N.G."<<endl;
		ss << "Your nickname (max. 5 chars)"<<endl;
		break;	
	case GameEngine::mainMenu:
		ss << "    P.O.N.G.\n\n\nQ - 1 Player\nA - 2 Player\n\nZ - top5\n\nEsc - Quit\n\n\n\nby\nKrzysztof Panek";
		break;	
	case GameEngine::pauseMenu:
		ss << "    P.O.N.G.\n\n\nEsc - resume game\nA - Abandon game\n";
		break;
	case GameEngine::vsAiMenu:
		ss << "    P.O.N.G.\n\n\nChoose\nis your opponent:\n\n1  - Amoeba\n2 - Noob\n3 - Pro\n4 - Terminator\n\n\nEsc - Back";
		break;	
	case GameEngine::mPlayerMenu:
		ss << "    P.O.N.G.\n\n\Player1\tPlayer2\n\n\t\tColor\nBlue\t\t\tRed\n\n\tControls\nW,S\t\tUp, Down\n\n\nEsc - Back\n\nSPACE - Start\n";
		break;
	case GameEngine::top5:

		ss << "    P.O.N.G.\n\n\n    Top 5\n\n";
		ss << records << endl<< "Esc - Back";


		inputFile.close();
		break;
	case GameEngine::playing:
		ss << m_p1Score << " - " << m_p2Score;
		if (scored == true)	ss << "\n\n\n\n\nGOAL";
		if ((powerUp_create < 32 && ball2 && fball_counter>0) && (m_ball.getPosition().x > 0) && (m_ball.getPosition().x < m_window.getSize().x))	ss << "\n\n\nFAKE BALL";

		break;
	case GameEngine::gameOver:

		if (m_p1Score > m_p2Score) {
			ss << "Player 1 wins\n\n\n\n\n\n" << "\t" << m_p1Score << " - " << m_p2Score;
		}
		else {
			ss << "Player 2 wins\n\n\n\n\n\n" << "\t" << m_p1Score << " - " << m_p2Score;
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
	int countD = 3000;
	float r = 0;
	float g = 0;
	float b = 0;
	while (m_window.isOpen())
	{
		dt = m_clock.restart().asSeconds();
		if (m_gStates == 0)
		{


			//play intro sound once
			if (introSound_done == false)
			{
				m_introSound.play();
				introSound_done = true;
			}
			//// change color Red channel
			if (r < 255) 
			{
				r+=0.05;
				sf::Color c(r, g, b);
				m_hud.setFillColor(c);
			}
			else
			{
				setDefaultFontSize();
				m_gStates = GameStates::mainMenu;
			}
		}
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) m_window.close();

			//m_gStates = GameStates::intro
			// Game Intro
			if (m_gStates == 0)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}

			//m_gStates = GameStates::mainMenu
			//code for Main Menu
			else if (m_gStates == 1)
			{
				setDefaultFontSize();
				spd = 1;

				//play music in the loop
				if (m_drumsSound.getStatus() != sf::Sound::Playing) m_drumsSound.play();
	
				//go according to press button
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
				{
					m_gStates = GameStates::vsAiMenu;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
				{
					m_gStates = GameStates::mPlayerMenu;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
				{
					m_gStates = GameStates::top5;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}

			}			
/////pauseMenu			
			else if (m_gStates == 10)
			{
				setDefaultFontSize();
				// Check if the intro music is still playing, and stop it 
				if (m_SoundtrackSound.getStatus() == sf::Sound::Playing) {
					m_SoundtrackSound.stop();
				}
				
				if (pause_delay < 1)
				{
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					{
						//paused = false;
						m_gStates = GameStates::playing;
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
					{
						paused = false;
						m_gStates = GameStates::mainMenu;
					}
				}
				else pause_delay--;

			}

			//m_gStates = GameStates::vsAiMenu
			// Player vs PC Menu
			else if (m_gStates == 2)
			{
				//move hud
				m_hud.setPosition((m_window.getSize().x / 2.f) - 80.f, 10);
				//press esc to main menu
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;
			
				//turn on AI
				ai = true;
				
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
				{
					m_diff = 4;
					m_viewDist = m_window.getSize().y;
					int rnd_max = m_window.getSize().x;
					int rnd_min = m_window.getSize().y;
					spd = 0.5;
					ballSize = 12;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
				{
					m_diff = 3;
					m_viewDist = 300;
					int rnd_max = m_window.getSize().y;
					int rnd_min = 300;
					spd = 1;//0.75;
					ballSize = 10;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
				{
					m_diff = 2;
					m_viewDist = 300;
					int rnd_max = 500;
					int rnd_min = 200;
					spd = 1;
					ballSize = 8;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
				{
					m_diff = 1;
					m_viewDist = 100;
					int rnd_max = 200;
					int rnd_min = 0;
					spd = 1.5;
					ballSize = 4;
					ball2 = true;
				}


				if (m_diff != 0)
					//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
					m_gStates = GameStates::playing;
			}
			//m_gStates = GameStates::mPlayerMenu
			// Player vs Player menu
			if (m_gStates == 3)
			{
				//if (event.type == sf::Event::Closed) m_window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;

				//turn off AI
				ai = false;
				
				//m_diff = 0;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				{
					m_gStates = GameStates::playing;
				}
			}

			//m_gStates = GameStates::top5
			else if (m_gStates == 7)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;
			}

			//m_gStates = GameStates::nick
			else if (m_gStates == 8)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;
			}
		}

		//m_gStates = GameStates::game over
		if (m_gStates == 5)
		{	
			//m_hud.setPosition((m_window.getSize().x / 2.f) - 180.f, 10);
			//if (gOverCounter > 0) gOverCounter--;
			//else
			//{
				Sleep(5000);
				

				// Check if the intro music is still playing, and stop it 
				if (m_SoundtrackSound.getStatus() == sf::Sound::Playing) {
					m_SoundtrackSound.stop();
				}

				//gOverCounter = 13000;
				//reset all vars to default values
				m_p1Score = 0;
				m_p2Score = 0;
				m_diff = 0;
				spd = 1;
				scored = false;
				fball_counter = 2000;
				m_ball.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
				m_ball2.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

				setDefaultFontSize();
				m_gStates = GameStates::mainMenu; 
			//}
			
		}
		//m_gStates = GameStates::playing
		else if (m_gStates == 4)
		{


			if (game_start == false)
			{
				m_hud.setPosition((m_window.getSize().x / 2.f) - 40.f, 10);

				// Check if the intro music is still playing, and stop it 
				if (m_drumsSound.getStatus() == sf::Sound::Playing) {
					m_drumsSound.stop();
				}
				game_start = true;
			}
				//play music in the loop
				if (m_SoundtrackSound.getStatus() != sf::Sound::Playing) {
					m_SoundtrackSound.play();
				}

				//hide power up hwn time run out
				if (powerUp_hide > 2)
				{
					powerUp_hide --;
					/*cout << "powerUp_hide:" << powerUp_hide << endl;
					cout << "XXXXXXXXXXXX:    " << powerUp_x << endl;
					cout << "YYYYYYYYYYYY:    " << powerUp_y << endl;*/
				}
				else if (powerUp_hide > 0)
				{
					m_powerUp.setPosition(1000, 1000);

				}

			//pause game
			if (paused == true)
			{
				paused = false;
				Sleep(200);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				//pause game
				paused = true;
				m_gStates = GameStates::pauseMenu;
			}


			//set default char size when score
			if (scored)
			{
				scored_timeout--;
				if (scored_timeout < 1)
				{
					setDefaultFontSize();
					scored = false;
				}
			}



			// increse player score
			if ((m_ball.getPosition().x < 0))
			{
				setLargeFontSize();
				scored = true;
				m_goalSound.play();
				Sleep(400);
				countD = 3000;
				m_p2Score++;
			}
			else if ((m_ball.getPosition().x > m_window.getSize().x))
			{
				setLargeFontSize();
				scored = true;
				m_goalSound.play();
				Sleep(400);
				countD = 3000;
				m_p1Score++;

			}	
			

//////PLAYER1 MOVE
			if (scored == false)
			{
				if (m_paddle1.getPosition().y > 55 && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					m_paddle1.moveUp(dt);
					//cout << m_paddle1.getPosition().y << endl;
					//cout << ai << endl;
				}
				else if (m_paddle1.getPosition().y < 555 && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					m_paddle1.moveDown(dt);
					//cout << m_paddle1.getPosition().y << endl;
				}
				////////PLAYER2 MOVE
				if (ai == false)
				{
					if (m_paddle2.getPosition().y > 55 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						m_paddle2.moveUp(dt);
						//cout << m_paddle2.getPosition().y << endl;
					}
					else if (m_paddle2.getPosition().y < 555 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						m_paddle2.moveDown(dt);
						//cout << m_paddle2.getPosition().y << endl;
					}
				}

			}
			//Restet ball position
			if ((m_ball.getPosition().x < 0) || (m_ball.getPosition().x > m_window.getSize().x))
			{
				
				 
				// tmp
				// Get the mouse position relative to the desktop
				//sf::Vector2i mousePositionDesktop = sf::Mouse::getPosition();


//////////random AI - give player chance to win
				if (ai)
				{

					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = m_window.getSize().x;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);
					if (m_diff == 4) if (m_viewDist > 720) m_viewDist = m_window.getSize().x;
					if (m_diff == 3) if (m_viewDist < 520 || (m_viewDist < 710 && m_viewDist>680)) m_viewDist = m_window.getSize().x;
					if (m_diff == 2) if (m_viewDist < 50) m_viewDist = m_window.getSize().x;
					if (m_diff == 1)
					{
						if (m_viewDist < 32)
						{
							m_viewDist = m_window.getSize().x;
						}
						else if (m_viewDist > 400)
						{
							m_viewDist = 200;
						}
					}
					////cout << m_viewDist << endl;
				}

			
				
				//Set position of Balls (if 2nd exist)
				if (ball2)
				{
					//Set position of 1st Ball
					//on 1/3h m_ball.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y * 0.3);
					m_ball.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
					//Set position of 2nd Ball
					//on 2/3h m_ball2.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y * 0.6);
					m_ball2.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
					scored_timeout = 1200;
				}
				else
				{
					//Set position of 1st Ball
					m_ball.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
					scored_timeout = 1200;
				}


				//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
				//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
			}

			//AI movement according to ball position
			if (ai)
			{
				if (m_ball.getPosition().x > m_viewDist && (m_ball.getPosition().y < m_paddle2.getPosition().y))
				{
					m_paddle2.moveUp(dt / m_diff);
				}
				else if (m_ball.getPosition().x > m_viewDist && (m_ball.getPosition().y > m_paddle2.getPosition().y))
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

			}

			//move balls
			//if (ballR==255 && ballG==255)
			//{
				//sf::Color cBall(ballR, ballG, ballB);
				//m_ball.setFillColor(cBall);
				////cout << "ballR " << ballR<<endl;
				//sf::Color c(r, g, b);
				if (countD > 0)
				{
					countD--;
					////cout << countD << endl;
					
				}
				if (countD < 1000)
				{
					//sf::Color cBall(255, 255, 0);
					//m_ball.setFillColor(cBall);
					 
					// move first ball
					m_ball.move(-dt, m_window);
					
					//countD = 2000;
					if (ball2 && countD < 5)
					{
						//fball_counter = 2000;
						m_ball2.setFillColor(sf::Color::Yellow);
						m_ball2.move(-dt, m_window);

					}
				}

				///////bounce ball1 on paddle1
			if ( m_paddle1.getBounds().contains(m_ball.getPosition()))
			{
				m_ball.getVelocityX();
				m_ball.getVelocityY();
				
				m_ballSound.play();

				if (ai)
				{
					uniform_int_distribution<> dis(300, rnd_max);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
			
				}

				if (m_diff > 1) spd += 0.01;
				m_ball.updateVelocity(-spd);
				if (powerUp_exist==false)
				{
					uniform_int_distribution<> dis(0, 128);
					powerUp_create = dis(gen);

					if (powerUp_create < 32)
					{
						uniform_int_distribution<> powerX_dis(255, (m_window.getSize().x - 255));
						powerUp_x = powerX_dis(gen);
						uniform_int_distribution<> powerY_dis(255, (m_window.getSize().y - 255));
						powerUp_y = powerY_dis(gen);
						powerUp_hide = 10000;
					}


				}
				
			}

			//bouce ball1 on paddle2
			if (m_paddle2.getBounds().contains(m_ball.getPosition()))
			{
				m_ballSound.play();
				if (ai)
				{
					uniform_int_distribution<> dis(300, rnd_max);
	
					m_viewDist = dis(gen);

					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
	
				}
				
				//calc n set new speed of ball
				if (m_diff > 1) spd += 0.01;
				m_ball.updateVelocity(spd);
				if (powerUp_exist == false)
				{
					uniform_int_distribution<> dis(0, 128);
					powerUp_create = dis(gen);
					if (powerUp_create < 32)
					{
						uniform_int_distribution<> powerX_dis(255, (m_window.getSize().x - 255));
						powerUp_x = powerX_dis(gen);
						uniform_int_distribution<> powerY_dis(255, (m_window.getSize().y - 255));
						powerUp_y = powerY_dis(gen);
						powerUp_hide = 10000;
					}
		

				}
			}

			if (ball2)
			{
				///////bounce ball2 on paddle1
				if (m_paddle1.getBounds().contains(m_ball2.getPosition()))
				{
					m_ballSound.play();
					if (ai)
					{

						//int rnd_max = 127 + mousePositionDesktop.y;
						/*int rnd_max = m_window.getSize().x;*/

						uniform_int_distribution<> dis(300, rnd_max);
				
						m_viewDist = dis(gen);
						if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
					
					}
					//calc n set new speed of ball
					if (m_diff > 1) spd += 0.01;
					m_ball2.updateVelocity(-spd);
					if (powerUp_exist == false)
					{
						uniform_int_distribution<> dis(0, 128);
						powerUp_create = dis(gen);
						if (powerUp_create < 32)
						{
							
							uniform_int_distribution<> powerX_dis(255, (m_window.getSize().x - 255));
							powerUp_x = powerX_dis(gen);
							uniform_int_distribution<> powerY_dis(255, (m_window.getSize().y - 255));
							powerUp_y = powerY_dis(gen);
						}
	
					}
				}
			
				//ball2 collision with powerUp
				if ((powerUp_exist) && (m_powerUp.getBounds().contains(m_ball2.getPosition())))
				{
					//choose random power up
					uniform_int_distribution<> pwr(0, 5);
					int pwr_choose = pwr(gen);

					if (pwr_choose < 3)
					{
						//m_paddle1.setSize(m_size);
						m_ball2.updateVelocity(-0.5);
						m_ball.updateVelocity(0.5);
					}
					else
					{
						m_ball2.updateVelocity(-0.5);
						m_ball.updateVelocity(0.5);
					}

					powerUp_exist = false;
				}
			}
			//ball1 collision with powerUp
			if ((m_powerUp.getBounds().contains(m_ball.getPosition())))
			{
				//choose random power up
				uniform_int_distribution<> pwr(0, 5);
				int pwr_choose = pwr(gen);
				ball2 = true;
				if (pwr_choose < 3)
				{
					//m_paddle1.setSize(m_size);
					m_ball2.updateVelocity(-0.5);
					m_ball.updateVelocity(0.5);
				}
				else
				{
					m_ball2.updateVelocity(0.5);
					m_ball.updateVelocity(-0.5);
				}

				powerUp_exist = false;
				
			}
			///////bounce ball2 on paddle2
			if (m_paddle2.getBounds().contains(m_ball2.getPosition()))
			{
				m_ballSound.play();

				if (ai)
				{
					uniform_int_distribution<> dis(300, rnd_max);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
				}


				if (m_diff > 1) spd += 0.01;
				m_ball2.updateVelocity(spd);
				if (powerUp_exist == false)
				{
					uniform_int_distribution<> dis(0, 128);
					powerUp_create = dis(gen);
					if (powerUp_create < 32)
					{
						uniform_int_distribution<> powerX_dis(255, (m_window.getSize().x - 255));
						powerUp_x = powerX_dis(gen);
						uniform_int_distribution<> powerY_dis(255, (m_window.getSize().y - 255));
						powerUp_y = powerY_dis(gen);
					}

				}
			}

			//if score=20 player wins
			if (m_p1Score>19 || m_p2Score > 19)
			{
				m_goverSound.play();
				
				scored_timeout = 2000;
				setLargeFontSize();
				m_gStates= GameEngine::gameOver;
			}
		
		}


		// update hud
		update();
		// draw shapes to screen
		draw();
	}
}
