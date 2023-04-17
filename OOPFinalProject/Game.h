#include<iostream>
#include<SFML/Graphics.hpp>
#include"Tetriminos.h"

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
	void CheckForLines(int& score);
	void SwapUp(int row);
	void PrintBoard(sf::RenderWindow*& window);

};

class Game
{
private:
	//Variables
	//Window
	
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::RectangleShape Block;
	sf::Font font;
	sf::Text scoreText, scoreNum;
	std::string name;
	Well well;
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
	void SetName(std::string n);
	void Update();
	void Render();
	void Quit();
	void PrintScore();
};

