#include"Game.h"
template<typename T>
void swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
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
	delete CurrentBlock;
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
				CurrentBlock->ShiftX(1, board);
		if (ev.key.code == sf::Keyboard::Right)
			if (!quit)
				CurrentBlock->ShiftX(0, board);
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
			CurrentBlock->SetTetrimino(board);
			CreateTetrimino<Ishape>();
		}
		if (timer % 30 == 0) {
			timer = 0;
			CurrentBlock->Fall(board);         //We make the blocks fall every 30 ticks
		}
		CheckForLines();
		timer++;
		timer2++;
	}
}

void Game::PrintBoard()
{
	Block.setSize(sf::Vector2f(23, 23));
	Block.setFillColor(sf::Color(255, 255, 255, 255));
	window->draw(Board);
	CurrentBlock->SetTetrimino(board);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
		{
			Block.setPosition((j * 36) + 26.5, (i * 36) + 27);
			if (board[i][j] == 0)
				Block.setFillColor(sf::Color::White);
			else if (board[i][j] == 1)
				Block.setFillColor(sf::Color::Red);
			window->draw(Block);
		}
	CurrentBlock->ResetTetrimino(board);
	if (quit)
		Quit();
	window->draw(Block);
}
void Game::Quit() {
	Block.setSize(sf::Vector2f(500, 300));
	Block.setFillColor(sf::Color::Red);
	Block.setPosition(50, 200);

}
void Game::Render()
{
	window->clear();
	PrintBoard();
	window->display();
}
