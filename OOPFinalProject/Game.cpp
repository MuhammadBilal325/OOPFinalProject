#include"Game.h"
#include<math.h>

template<typename T>
void swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}
Game::Game()
{
	char tiletexturepath[21] = "./Textures/Tile1.png";
	if (!BoardTexture.loadFromFile("./Textures/board.png")) {
		std::cout << "Error loading board..." << std::endl;
	}
	for (int i = 0; i < 8; i++)
	{
		tiletexturepath[15] = i + 1 + 48;
		if (!Tiletextures[i].loadFromFile(tiletexturepath)) {
			std::cout << "Error loading TileTexture..." << std::endl;
		}
		Tiles[i] = sf::Sprite(Tiletextures[i]);
	}
	Board = sf::Sprite(BoardTexture);
	Board.setScale(1, 1);
	Board.setPosition(20, 20);
	videoMode.height = 800;
	videoMode.width = 600;
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Default);
	window->setFramerateLimit(60);
	CreateTetrimino<Ishape>();
}

Game::~Game()
{
	delete window;
	delete CurrentBlock;
}

const bool Game::getWindowState() const
{
	return window->isOpen();
}
template<typename T>
void Game::CreateTetrimino() {
	T NewBlock;
	CurrentBlock = new T;
	*CurrentBlock = NewBlock;
	if (CurrentBlock->Checkintersection(board))
		quit = true;
}

void Game::PollEvents()
{
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		if (ev.key.code == sf::Keyboard::Left)
			if (!quit)
				Move = 1;
		if (ev.key.code == sf::Keyboard::Right)
			if (!quit)
				Move = 0;
		if (ev.key.code == sf::Keyboard::R && ev.type == sf::Event::KeyReleased)
			if (!quit)
				Rotate = 1;
	}
}


void Game::SwapUp(int row)
{
	for (int i = row; i > 0; i--)
		for (int j = 0; j < 10; j++)
			swap(board[i][j], board[i - 1][j]);
}
void Game::CheckForLines() {
	bool continuos = 1;
	for (int i = 0; i < 20; i++)
	{
		continuos = 1;
		for (int j = 0; j < 10; j++)
			if (board[i][j] == 0)
				continuos = 0;
		if (continuos)
		{
			for (int j = 0; j < 10; j++)
				board[i][j] = 0;
			SwapUp(i);
			i--;
		}
	}
}
void Game::Update()
{
	PollEvents();  //Get user input
	if (!quit)
	{
		if (!CurrentBlock->IsControllable()) {
			int type = rand() % 7;
			CurrentBlock->SetTetrimino(board);
			delete CurrentBlock;
			if (type == 0)
				CreateTetrimino<Ishape>();
			else if (type == 1)
				CreateTetrimino<Jshape>();
			else if (type == 2)
				CreateTetrimino<Lshape>();
			else if (type == 3)
				CreateTetrimino<Oshape>();
			else if (type == 4)
				CreateTetrimino<Sshape>();
			else if (type == 5)
				CreateTetrimino<Tshape>();
			else if (type == 6)
				CreateTetrimino<Zshape>();
			if (CurrentBlock->Checkintersection(board))
				quit = 1;
		}
		if (timer % speed == 0 && !quit) {
			timer = 0;
			CurrentBlock->Fall(board);         //We make the blocks fall every 30 ticks
			if (Move != -1) {
				CurrentBlock->ShiftX(Move, board); Move = -1;
			}
			if (Rotate != -1) {
				CurrentBlock->Rotate(board); Rotate = -1;
			}
		}
		CheckForLines();
		timer++;
	}
}

void Game::Quit() {
	Block.setSize(sf::Vector2f(500, 300));
	Block.setFillColor(sf::Color::Red);
	Block.setPosition(50, 200);
}
void Game::PrintBoard()
{
	window->draw(Board);
	CurrentBlock->SetTetrimino(board);
	for (int i = 20, k = 0; i < 20 * 36 && k < 20; i += 36, k++)
		for (int j = 20, l = 0; j < 20 * 36 && l < 10; j += 36, l++)
		{
			Tiles[board[k][l]].setPosition(j, i);
			window->draw(Tiles[board[k][l]]);
		}
	window->draw(Tiles[0]);
	CurrentBlock->ResetTetrimino(board);
	if (quit) {
		Quit();
		window->draw(Block);
	}
}
void Game::Render()
{
	window->clear();
	PrintBoard();
	window->display();
}
