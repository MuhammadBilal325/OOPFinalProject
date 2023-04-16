#include"Game.h"

void IncreaseDynarray(Tetrimino*& arr, int s)
{
	Tetrimino* newarr = new Tetrimino[s + 1];
	for (int i = 0; i < s; i++)
		newarr[i] = arr[i];
	delete[]arr;
	arr = newarr;
}
Game::Game()
{
	if (!BoardTexture.loadFromFile("./Textures/board.png")) {
		std::cout << "Error loading board..." << std::endl;
	}
	Board = sf::Sprite(BoardTexture);
	Board.setScale(1, 1);
	Board.setPosition(20, 20);
	videoMode.height = 800;
	videoMode.width = 600;
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Default);
	window->setFramerateLimit(60);
	CreateTetrimino();
}

Game::~Game()
{
	delete window;
	delete[]Blocks;
}

const bool Game::getWindowState() const
{
	return window->isOpen();
}
void Game::CreateTetrimino() {
	Ishape NewBlock;
	if (blocknum > 0)
		IncreaseDynarray(Blocks, blocknum);
	Blocks[blocknum] = NewBlock;
	blocknum++;
}

void Game::PollEvents()
{
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		if (ev.key.code == sf::Keyboard::Left)
		{
			Blocks[blocknum - 1].ShiftX(1,board);
		}
		if (ev.key.code == sf::Keyboard::Right)
		{
			Blocks[blocknum - 1].ShiftX(0,board);
		}
	}
}
void Game::UpdateBoard() {
	for (int k = 0; k < blocknum; k++)
	{
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++)
				if (Blocks[k].GetX() == j)
					if (Blocks[k].GetY() == i)
						Blocks[k].SetTetrimino(board);
	}
}

void Game::Update()
{
	PollEvents();  //Get user input
	if(!Blocks[blocknum-1].IsControllable())
		CreateTetrimino();
	if (timer % 30 == 0) { 
		timer = 0;
		for (int i = 0; i < blocknum; i++)
			if(Blocks[i].IsControllable())
			Blocks[i].Fall(board);         //We make the blocks fall every 5 ticks
	}
	UpdateBoard();//Update board so new blocks can appear/disappear regardless of falling ticks	
	timer++;
	timer2++;
}

void Game::PrintBoard()
{
	Block.setSize(sf::Vector2f(23, 23));
	Block.setFillColor(sf::Color(255, 255, 255, 255));
	window->draw(Board);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
		{
			Block.setPosition((j*36)+26.5,(i*36)+27);
			if (board[i][j] == 0)
				Block.setFillColor(sf::Color::White);
			else if (board[i][j] == 1)
				Block.setFillColor(sf::Color::Red);
			window->draw(Block);
		}
	window->draw(Block);
}
void Game::Render()
{
	window->clear();
	PrintBoard();
	window->display();
}
