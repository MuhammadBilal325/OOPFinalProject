#include<iostream>
#include<SFML/Graphics.hpp>
#include"Tetriminos.h"

class Game
{
private:
	//Variables
	//Window
	int board[20][10]=
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::RectangleShape Block;
	sf::Sprite Board;
	sf::Texture BoardTexture;

	int timer = 0;
	int timer2 = 0;
	int blocknum = 0;
	Tetrimino* Blocks = new Tetrimino[1];
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();
	//Getter Setter
	const bool getWindowState() const;
	//Functions
	void PollEvents();
	void CreateTetrimino();
	void UpdateBoard();
	void Update();
	void Render();
	void PrintBoard();
	void PrintBoardcout();
};

