#include<iostream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include"Tetriminos.h"
#include"MenuGUI.h"

class Game
{
private:
	//Variables

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Clock fallingclock, movementclock;
	sf::Time fallingtime, movementtime;
	MenuGUI menu;
	std::string highscorenames[5];
	int highscoressize, highscoreint[5];
	std::string name;
	int namesize;
	Well well;
	bool quit, fastfalling, isnameentered, scoresfinalized;
	int  Move, speed, fallinginterval, score, totalscore;

	float nextTx, nextTy;

	Tetrimino* CurrentBlock;
	Tetrimino* NextBlock;
	int nexttype;
public:
	//Constructors and Destructors
	Game();
	~Game();
	//Initializor
	void InitializeHighscores();
	//Getter Setter
	const bool getWindowState() const;
	//Functions
	void PollEvents();
	template<typename T>void CreateTetrimino();
	template<typename T>void CreateNextTetrimino();
	void Update();
	void Render();
	void Quit();
	void FinalizeScores();
};

