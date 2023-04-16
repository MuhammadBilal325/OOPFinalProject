#include<iostream>
#include<SFML/Graphics.hpp>
#include"Tetriminos.h"

class Game
{
private:
	//Variables
	//Window
	int board[20][10] =
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
	sf::Sprite Tiles[8];
	sf::Texture Tiletextures[8];
	sf::Texture BoardTexture;
	sf::Font font;
	sf::Text scoreText,scoreNum;
	std::string name;
	bool quit = 0,fastfalling=0;
	int timer = 0,timer2=0, Move = -1, speed = 60,usingspeed=60,score=0;
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
	void SetName(std::string n);
	void Update();
	void Render();
	void Quit();
	void PrintBoard();
	void PrintScore();
	void PrintBoardcout();
};

