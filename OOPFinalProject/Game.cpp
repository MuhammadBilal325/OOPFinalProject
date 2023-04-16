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
	if (!font.loadFromFile("./Textures/1up.ttf")) {
		std::cout << "Error loading font file" << std::endl;
	}
	scoreText.setFont(font);
	scoreNum.setFont(font);
	scoreText.setPosition(400, 250);
	scoreNum.setPosition(400, 300);
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
		else if (ev.key.code == sf::Keyboard::Left) {
			if (!quit)
				Move = 1;
		}
		else if (ev.key.code == sf::Keyboard::Right) { 
			if (!quit)
				Move = 0;
		}
		else if (ev.key.code == sf::Keyboard::Up && ev.type == sf::Event::KeyReleased){ 
			if (!quit)
				CurrentBlock->Rotate(board);
		}
		else if (ev.key.code == sf::Keyboard::Down) {
			if (!quit) {
				fastfalling = 1;
			}
		}
		
	}
}
void Game::SetName(std::string n)
{
	name = n;
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
			score += 100;
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
			fastfalling = 0;
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
		if (fastfalling)
			usingspeed = 5;
		else {
			usingspeed = speed -((score/1000)*0.1)*speed;
		}
		if (timer2 % 15 == 0) {
			if (Move != -1) {
				CurrentBlock->ShiftX(Move, board); Move = -1;
			}
		}
		if (timer % usingspeed == 0 && !quit) {
			timer = 0;
			CurrentBlock->Fall(board);         //We make the blocks fall every 30 ticks
		}
		CheckForLines();
		timer++;
		timer2++;
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

void Game::PrintScore()
{
	scoreText.setString("score");
	scoreNum.setString(std::to_string(score));
	window->draw(scoreText);
	window->draw(scoreNum);
}
void Game::Render()
{
	window->clear();
	PrintScore();
	PrintBoard();
	window->display();
}
