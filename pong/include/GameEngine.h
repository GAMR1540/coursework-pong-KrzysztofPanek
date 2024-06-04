#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Paddle.h"
#include "Ball.h"
#include "PowerUp.h"

class GameEngine
{
private:
	sf::RenderWindow& m_window;
	sf::Font m_font;
	sf::Text m_hud;
	sf::SoundBuffer m_ballBuffer;
	sf::SoundBuffer m_goalBuffer;	
	sf::SoundBuffer m_introBuffer;
	sf::SoundBuffer m_goverBuffer;
	sf::SoundBuffer m_SoundtrackBuffer;
	
	sf::Sound m_ballSound;
	sf::Sound m_goalSound;	
	sf::Sound m_introSound;
	sf::Sound m_goverSound;
	sf::Sound m_SoundtrackSnd;
	sf::Clock m_clock;


	Paddle m_paddle1;
	Paddle m_paddle2;
	Ball m_ball;
	Ball m_ball2;
	PowerUp m_powerUp;

	//int ballSize = 800;

	int powerUp_create;
	bool powerUp_exist;
	//int powerUp_x;
	//int powerUp_y;

	bool introSnd_done;
	int m_p1Score;
	int m_p2Score;
	bool ai;
	int rnd_max;
	int m_diff;
	int m_viewDist;
	int m_defend;
	bool ball2;
	char playerName[6] = "D.M.U";
	float ballSize=8;
	static const int m_maxScore = 3;
	enum GameStates {intro, mainMenu, vsAi, mPlayer, playing, gameOver, gamePaused, top5, nick};
	GameStates m_gStates;


public:
	GameEngine(sf::RenderWindow& window);
	void draw();
	void update();
	void rand128();
	void run();

};

