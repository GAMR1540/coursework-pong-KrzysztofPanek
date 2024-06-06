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
	sf::SoundBuffer m_drumsBuffer;
	
	sf::Sound m_drumsSound;
	sf::Sound m_ballSound;
	sf::Sound m_goalSound;	
	sf::Sound m_introSound;
	sf::Sound m_goverSound;
	sf::Sound m_SoundtrackSound;
	sf::Clock m_clock;


	Paddle m_paddle1;
	Paddle m_paddle2;
	Ball m_ball;
	Ball m_ball2;
	PowerUp m_powerUp;

	//game has been started in play mode
	bool game_start;


	// vars for ball color
	float ballR = 0;
	float ballG = 0;
	float ballB = 0;


	//score innitial values
	bool scored;
	int scored_timeout;


	//game couver counter
	int gOverCounter;

	//for pause game
	///true if game has been stared
	bool paused;
	int pause_delay;

	//vars fo powerUp
	int powerUp_create;
	bool powerUp_exist;
	bool powerUp_set;
	//hide powerup
	int powerUp_hide;



	bool introSound_done;
	int m_p1Score;
	int m_p2Score;
	bool ai;
	int rnd_max;
	int m_diff;
	int m_viewDist;
	int m_defend;
	bool ball2;
	char playerName[6] = "D.M.U";
	//float ballSize;
	static const int m_maxScore = 3;
	enum GameStates {intro, mainMenu, vsAi, mPlayer, playing, gameOver, gamePaused, top5, nick, PvP_playing, pauseMenu};
	GameStates m_gStates;


public:
	GameEngine(sf::RenderWindow& window);
	void draw();
	void update();
	void rand128();
	void run();

	void setDefaultFontSize()
	{
		m_hud.setPosition((m_window.getSize().x / 2.f) - 40.f, 10);
		m_hud.setCharacterSize(40);
	}

	void setLargeFontSize()
	{
		m_hud.setPosition((m_window.getSize().x / 2.f) - 80.f, 10);
		m_hud.setCharacterSize(80);
	}
};

