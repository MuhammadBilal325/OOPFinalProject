#include<iostream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include"Tetriminos.h"
#include"MenuGUI.h"
template<typename T>
void swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}
class Well {
private:
	int** board;
	sf::Sprite Board;
	sf::Sprite Tiles[8];
	sf::Texture Tiletextures[8];
	sf::Texture BoardTexture;
public:
	Well();
	~Well();
	int** GetBoard() { return board; }
	void CheckForLines(int& score,int&totalscore);
	void SwapUp(int row);
	void PrintBoard(sf::RenderWindow*& window);

};

class Game
{
private:
	//Variables
	
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	MenuGUI menu;
	std::string highscorenames[5];
	int highscoressize,highscoreint[5];
	std::string name;
	int namesize;
	Well well;
	bool quit ,fastfalling,isnameentered;
	int timer ,timer2, Move , speed ,usingspeed,score,totalscore;
	Tetrimino* CurrentBlock;
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
	void Update();
	void Render();
	void Quit();
	void FinalizeScores();
};

