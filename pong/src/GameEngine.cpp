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
	m_paddle1(sf::Vector2f(20, window.getSize().y / 2.f), 10, 100, sf::Color::Blue),
	m_paddle2(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y - 100.f), 10, 100, sf::Color::Red),
	m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), ballSize, 400.f, sf::Color::Yellow),
	m_ball2(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), ballSize, 400.f, sf::Color::White),
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
	gOverCounter = 2000;

	//for pause game
	///true if game has been stared
	paused = false;
	pause_delay = 2;

	// powerup vars
	powerUp_hide = 0;
	powerUp_create = 100;
	powerUp_exist = false;
	powerUp_set = false;

	//score
	m_p1Score = 0;
	m_p2Score = 0;

	//true when playing with AI
	//false when PvP
	ai = false;

	//Difficulty
	m_diff = 0;

	//distance of view of enemy
	m_viewDist = 0;

	m_defend = 0;

	// max random number
	rnd_max = 600;

	//true when 2nd ball is in game
	//default false
	ball2=false;

	introSound_done = false;

	//default player name
	// for TOP5
	char playerName[6] = "D.M.U";

	//tmp colors
	//sf::Color orange(255, 160, 0);
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
	if (m_gStates > 0 && m_gStates < 4)
	{
		//set up hud
		m_hud.setPosition((m_window.getSize().x / 2.f) - 90.f, 10);
		//draw menu side lines
		sf::RectangleShape sideLineL(sf::Vector2f(8, 600));
		sf::RectangleShape sideLineR(sf::Vector2f(8, 600));
		sideLineL.setFillColor(sf::Color(100, 100, 100));
		sideLineR.setFillColor(sf::Color(100, 100, 100));
		sideLineL.setPosition(200, 0);
		m_window.draw(sideLineL);
		sideLineR.setPosition(600, 0);
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
		
	if (m_gStates == 0)
	{
		// Draw the image
		img.setPosition(((m_window.getSize().x / 2.f) - 200.f), 250.f);
		m_window.draw(img);
	}	
	if (scored == true || )
	{
		// Draw the image
		img.setPosition(((m_window.getSize().x / 2.f) - 200.f), 100.f);
		m_window.draw(img);
	}
		
	if (m_gStates == 4)
	{
		//draw halfway line
		sf::RectangleShape halfWayLine(sf::Vector2f(8, 600));
		halfWayLine.setFillColor(sf::Color(100, 100, 100));
		halfWayLine.setPosition(400, 0);
		

		sf::CircleShape centerCircle(50);
		centerCircle.setFillColor(sf::Color(100, 100, 100));
		centerCircle.setPosition(355, 250);
		

		sf::CircleShape centerCircle1(42);
		centerCircle1.setFillColor(sf::Color(0, 0, 0));
		centerCircle1.setPosition(360, 260);
		
		// hide markings when scored
		if (scored == false)
		{
			m_window.draw(halfWayLine);
			m_window.draw(centerCircle);
			m_window.draw(centerCircle1);
		}
		//if (powerUp_create < 32)
		if (powerUp_create < 32 || powerUp_exist)
		{
			if (powerUp_set==false)
			{
			powerUp_hide = 10000;
			powerUp_exist = true;
			////draw halfway line
			//sf::RectangleShape halfWayLine(sf::Vector2f(8, 600));
			//halfWayLine.setFillColor(sf::Color(100, 100, 100));
			//halfWayLine.setPosition(400, 0);
			//m_window.draw(halfWayLine);
			
				uniform_int_distribution<> disPX(100, 700);
				int powerUp_x = disPX(gen);
				uniform_int_distribution<> disPY(100, 500);
				int powerUp_y = disPY(gen);
				powerUp_set = true;
			}

			 
			m_powerUp.setPosition(powerUp_x, powerUp_y);

			//drwa powrup bg
			uniform_int_distribution<> disPbgX(-20, 20);
			int powerUp_shakeX = disPbgX(gen);
			uniform_int_distribution<> disPbgY(-20, 20);
			int powerUp_shakeY = disPbgY(gen);
			m_powerUp.setPosition(powerUp_x+ powerUp_shakeX, powerUp_y+ powerUp_shakeY);
			/*sf::RectangleShape powerUp_bg(sf::Vector2f(50, 50));
			powerUp_bg.setFillColor(sf::Color::Yellow);
			powerUp_bg.setPosition(powerUp_x- powerUp_bgX, powerUp_y- powerUp_bgY);
			m_window.draw(powerUp_bg)*/;

			
		}
		if (powerUp_exist && powerUp_hide > 0) m_powerUp.draw(m_window);
		//m_powerUp.draw(m_window);
		m_paddle1.draw(m_window);
		m_paddle2.draw(m_window);
		m_ball.draw(m_window);
		m_ball2.draw(m_window);

		
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
		//ss << "Press the Space\nkey to start";
		ss << "    P.O.N.G.\n\n\nQ - 1 Player\nA - 2 Player\n\nZ - top5\n\nEsc - Quit";
		break;	
	case GameEngine::pauseMenu:
		//ss << "Press the Space\nkey to start";
		ss << "    P.O.N.G.\n\n\nEsc - resume game\nA - Abandon game\n";
		break;
	case GameEngine::vsAi:
		//ss << "Press the Space\nkey to start";
		ss << "    P.O.N.G.\n\n\nChoose\nis your opponent:\n\n1  - Amoeba\n2 - Noob\n3 - Pro\n4 - Terminator\n\n\nEsc - Back";
		break;	
	case GameEngine::mPlayer:
		//ss << "Press the Space\nkey to start";
		ss << "    P.O.N.G.\n\n\Player1\tPlayer2\n\n\t\tColor\nBlue\t\t\tRed\n\n\tControls\nW,S,A,D\t\tArrows\n\n\nEsc - Back\n\nSPACE - Start\n";
		break;
	case GameEngine::top5:

		ss << "    P.O.N.G.\n\n\n    Top 5\n\n";
		ss << records << endl<< "Esc - Back";
		//while (getline(inputFile, records)) 
		//{
		//	ss << "    P.O.N.G.\n\n\ntop 5\n";
		//	ss << records << endl;
		//}

		inputFile.close();
		break;
	case GameEngine::playing:
		ss << m_p1Score << " - " << m_p2Score;
		if (scored == true)	ss << "\n\n\n\n\nGOAL";
		if ((powerUp_exist) && (m_powerUp.getBounds().contains(m_ball.getPosition())))	ss << "\n\n\nFAKE BALL";
		//if (powerUp_create < 32)	ss << "\n\n\nFAKE BALL";

		break;
	case GameEngine::gameOver:

		if (m_p1Score > m_p2Score) {
			ss << "\n\nPlayer 1 wins\n"<<m_p1Score << " - " << m_p2Score;
		}
		else {
			ss << "\n\nPlayer 2 wins\n" << m_p1Score << " - " << m_p2Score;
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
		////cout << ballSize << endl;
		if (m_gStates == 0)
		{


			//play intro sound once
			if (introSound_done == false)
			{
				m_introSound.play();
				introSound_done = true;
			}
			//play music in the loop
			//else if (introSound_done == true && (m_introSound.getStatus() != sf::Sound::Playing) && (m_drumsSound.getStatus() != sf::Sound::Playing))
			//{
			//	m_drumsSound.play();
			//}

			////cout << "ballR " << ballR << endl;

/*			countD--;
			//cout << countD << endl*/;
			
			if (r < 255) 
			{
				r+=0.05;
				sf::Color c(r, g, b);
				m_hud.setFillColor(c);
			}
			//else if (g < 255) g += 0.1;
			//else if (b < 255) b += 0.1;
			else
			{
				//g = 255;
				//b = 255;
				//sf::Color c(r, g, b);
				//m_hud.setFillColor(c);
				//default m_hud.setPosition((m_window.getSize().x / 2.f) - 45.f, 10);
				setDefaultFontSize();
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
			else if (m_gStates == 1)
			{
				setDefaultFontSize();


				//play music in the loop
				if (m_drumsSound.getStatus() != sf::Sound::Playing) m_drumsSound.play();
	/*			if (introSound_done == true && (m_introSound.getStatus() != sf::Sound::Playing) && (m_drumsSound.getStatus() != sf::Sound::Playing))
				{
					m_drumsSound.play();
				}*/				

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

			//m_gStates = GameStates::vsAi
			else if (m_gStates == 2)
			{
				m_hud.setPosition((m_window.getSize().x / 2.f) - 80.f, 10);
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
					int rnd_max = m_window.getSize().x;
					int rnd_min = 600;
					spd = 0.5;
					ballSize = 12;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
				{
					m_diff = 3;
					m_viewDist = 300;
					int rnd_max = 600;
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
			//m_gStates = GameStates::mPlayer
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

				//m_gStates = GameStates::top5;

			}

			//m_gStates = GameStates::nick
			else if (m_gStates == 8)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					m_gStates = GameStates::mainMenu;

				//m_gStates = GameStates::nick;

			}
		}

		//m_gStates = GameStates::game over
		if (m_gStates == 5)
		{	
			if (gOverCounter > 0) gOverCounter--;
			else
			{
				Sleep(3000);
				

				// Check if the intro music is still playing, and stop it 
				if (m_SoundtrackSound.getStatus() == sf::Sound::Playing) {
					m_SoundtrackSound.stop();
				}

				gOverCounter = 3000;
				//reset all vars to default values
				m_p1Score = 0;
				m_p2Score = 0;
				m_diff = 0;
				scored = false;
				m_gStates = GameStates::mainMenu; 
			}
			
		}
		//m_gStates = GameStates::playing
		else if (m_gStates == 4)
		{
//////////////FOR DEBUG
			//cout << dt << endl;

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


			/*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_gStates = GameStates::mainMenu;*/
				////cout << m_diff;
			// ADD YOUR CODE HERE !!!

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				//cout << "UP key pressed" << endl;
				m_paddle1.move(0, -m_paddle1.getSpeed() * dt);
			}*/

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
				//to qiut
				//reset all vars to default values
				/*m_p1Score = 0;
				m_p2Score = 0;
				scored_timeout = 1200;
				m_hud.setCharacterSize(40);*/
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

			//cout << scored_timeout << endl;
			//cout << countD << endl;


			// increse player score
			if ((m_ball.getPosition().x < 0))
			{
				setLargeFontSize();
				scored = true;
				m_goalSound.play();
				Sleep(400);
				countD = 2000;
				m_p2Score++;

				//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
				//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
			}
			else if ((m_ball.getPosition().x > m_window.getSize().x))
			{
				setLargeFontSize();
				scored = true;
				m_goalSound.play();
				Sleep(400);
				countD = 2000;
				m_p1Score++;

				//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
				//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
			}
			//Paddle1 - Human Player move paddle
			//This setup prevent to go paddle outside screen when score
			//else

//////PLAYER1 MOVE
			if (m_paddle1.getPosition().y > 55 && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_paddle1.moveUp(dt);
				cout << m_paddle1.getPosition().y << endl;
				cout << ai << endl;
			}
			else if (m_paddle1.getPosition().y < 555 && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_paddle1.moveDown(dt);
				cout << m_paddle1.getPosition().y << endl;
			}
////////PLAYER2 MOVE
			if (ai == false)
			{
				if (m_paddle2.getPosition().y > 55 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_paddle2.moveUp(dt);
					cout << m_paddle2.getPosition().y << endl;
				}
				else if (m_paddle2.getPosition().y < 555 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_paddle2.moveDown(dt);
					cout << m_paddle2.getPosition().y << endl;
				}
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
			//	else if ((m_ball2.getPosition().x > m_window.getSize().x))
			//	{
			//		m_p1Score++;

			//		//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			//		//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
			//	}
			//}

			//Restet ball position
			if ((m_ball.getPosition().x < 0) || (m_ball.getPosition().x > m_window.getSize().x))
			{
				//random AI
						// Get the mouse position relative to the desktop
				//sf::Vector2i mousePositionDesktop = sf::Mouse::getPosition();
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
					//on 1/3h m_ball.setPosition(m_window.getSize().x / 2.f, 600 * 0.3);
					m_ball.setPosition(m_window.getSize().x / 2.f, 600 / 2.f);
					//Set position of 2nd Ball
					//on 2/3h m_ball2.setPosition(m_window.getSize().x / 2.f, 600 * 0.6);
					m_ball2.setPosition(m_window.getSize().x / 2.f, 600 / 2.f);
					scored_timeout = 1200;
				}
				else
				{
					//Set position of 1st Ball
					m_ball.setPosition(m_window.getSize().x / 2.f, 600 / 2.f);
					scored_timeout = 1200;
				}


				//m_ball.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
				//m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::Yellow);
			}

			//AI
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


			//random AI
			// Get the mouse position relative to the desktop
			//sf::Vector2i mousePositionDesktop = sf::Mouse::getPosition();
			//random_device rd;
			//mt19937 gen(rd());
			//int rnd_max = 127 + mousePositionDesktop.y;
			//uniform_int_distribution<> dis(0, rnd_max);
			//int random_number = dis(gen);
			////cout << random_number << endl;
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
					if (ball2 && countD < 2)
					{
						m_ball2.setFillColor(sf::Color::Yellow);
						m_ball2.move(-dt, m_window);

					}
				}
			//}
			//else
			//{
			//	ballR++;
			//	ballG++;
			//	sf::Color cBall(ballR, ballG, ballB);
			//	m_ball.setFillColor(cBall);
			//}
			///bounce ball 1

			if ( m_paddle1.getBounds().contains(m_ball.getPosition()))
			{
				m_ball.getVelocityX();
				m_ball.getVelocityY();
				
				m_ballSound.play();

				if (ai)
				{
					
					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = m_window.getSize().x;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
					////cout << m_viewDist << endl;
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

					cout << powerUp_create<<endl;
					cout << powerUp_exist << endl;

				}
				
			}


			if (m_paddle2.getBounds().contains(m_ball.getPosition()))
			{
				m_ballSound.play();
				if (ai)
				{
					
					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = m_window.getSize().x;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);

					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
					////cout << m_viewDist << endl;
				}
				
				
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
					cout << powerUp_create << endl;
					cout << powerUp_exist << endl;

				}
			}

			if (ball2)
			{
				///////bounce ball2
				if (m_paddle1.getBounds().contains(m_ball2.getPosition()))
				{
					m_ballSound.play();
					if (ai)
					{

						//int rnd_max = 127 + mousePositionDesktop.y;
						/*int rnd_max = m_window.getSize().x;*/

						uniform_int_distribution<> dis(300, rnd_max);
						//int m_viewDist = dis(gen);
						m_viewDist = dis(gen);
						if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
						//cout << m_viewDist << endl;
					}

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
						cout << powerUp_create << endl;
						cout << powerUp_exist << endl;
					}
				}
			
			 
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
					//else if (pwr_choose < 3)
					//{
					//	//m_paddle1.setSize(m_size);
					//	m_ball2.updateVelocity(0.5);
					//	m_ball.updateVelocity(2);
					//}
					else
					{
						m_ball2.updateVelocity(-0.5);
						m_ball.updateVelocity(0.5);
					}

					powerUp_exist = false;
				}
			}
			if ((powerUp_exist) && (m_powerUp.getBounds().contains(m_ball.getPosition())))
			{
				//choose random power up
				uniform_int_distribution<> pwr(0, 5);
				int pwr_choose = pwr(gen);
				ball2 = true;
				if (pwr_choose < 3)
				{
					//m_paddle1.setSize(m_size);
					m_ball2.updateVelocity(0.5);
					m_ball.updateVelocity(-0.5);
				}
				//else if (pwr_choose < 3)
				//{
				//	//m_paddle1.setSize(m_size);
				//	m_ball2.updateVelocity(0.5);
				//	m_ball.updateVelocity(2);
				//}
				else
				{
					m_ball2.updateVelocity(0.5);
					m_ball.updateVelocity(-0.5);
				}

				powerUp_exist = false;
			}

			/////////////////////////////////////////
			//if (centerCircle.getBounds().contains(m_ball2.getPosition()))
			//{
			//	m_ballSound.play();

			//	if (ai)
			//	{
			//		
			//		//int rnd_max = 127 + mousePositionDesktop.y;
			//		/*int rnd_max = m_window.getSize().x;*/

			//		uniform_int_distribution<> dis(300, rnd_max);
			//		//int m_viewDist = dis(gen);
			//		m_viewDist = dis(gen);
			//		if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
			//		//cout << m_viewDist << endl;
			//	}


			//	if (m_diff > 1) spd += 0.01;
			//	m_ball2.updateVelocity(spd);
			//	if (powerUp_exist == false)
			//	{
			//		uniform_int_distribution<> dis(0, 128);
			//		powerUp_create = dis(gen);
			//		if (powerUp_create < 32)
			//		{
			//			uniform_int_distribution<> powerX_dis(127, (m_window.getSize().x - 127));
			//			powerUp_x = powerX_dis(gen);
			//			uniform_int_distribution<> powerY_dis(127, (m_window.getSize().y - 127));
			//			powerUp_y = powerY_dis(gen);
			//		}
			//		cout << powerUp_create << endl;
			//		cout << powerUp_exist << endl;
			//	}
			//}			
			/////////////////////////


			if (m_paddle2.getBounds().contains(m_ball2.getPosition()))
			{
				m_ballSound.play();

				if (ai)
				{
					
					//int rnd_max = 127 + mousePositionDesktop.y;
					/*int rnd_max = m_window.getSize().x;*/

					uniform_int_distribution<> dis(300, rnd_max);
					//int m_viewDist = dis(gen);
					m_viewDist = dis(gen);
					if (m_viewDist < 32 || (m_viewDist < 710 && m_viewDist>660)) m_viewDist = m_window.getSize().x;
					//cout << m_viewDist << endl;
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
					cout << powerUp_create << endl;
					cout << powerUp_exist << endl;
				}
			}

			if (m_p1Score>19 || m_p2Score > 19)
			{
				m_goverSound.play();
				
				scored_timeout = 1200;
				setLargeFontSize();
				m_gStates= GameEngine::gameOver;
			}
		
		}

		//float p1y=m_paddle1.getPosition().y

		//if (m_ball.getPosition() < m_paddle1.getPosition())
		// update hud
		update();
		// draw shapes to screen
		draw();
	}
}
