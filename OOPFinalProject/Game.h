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

	bool quit = 0;
	int timer = 0;
	int timer2 = 0;
	Tetrimino* CurrentBlock;
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();
	//Getter Setter
	const bool getWindowState() const;
	//Functions
	void PollEvents();
	template<typename T>void CreateTetrimino();
	void UpdateBoard();
	void CheckForLines();
	void SwapUp(int row);
	void Update();
	void Render();
	void Quit();
	void PrintBoard();
	void PrintBoardcout();
};

