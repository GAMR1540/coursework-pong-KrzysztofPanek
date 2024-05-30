#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Paddle.h"
#include "Ball.h"
//error #include "PowerUp.h"

class GameEngine
{
private:
	sf::RenderWindow& m_window;
	sf::Font m_font;
	sf::Text m_hud;
	sf::SoundBuffer m_ballBuffer;
	sf::Sound m_ballSound;
	sf::Clock m_clock;


	Paddle m_paddle1;
	Paddle m_paddle2;
	Ball m_ball;
	Ball m_ball2;
	//error PowerUp pup;

	int ballSize;
	int m_p1Score;
	int m_p2Score;
	bool ai;
	int rnd_max;
	int m_diff;
	int m_viewDist;
	int m_defend;
	bool ball2;
	char playerName;
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

