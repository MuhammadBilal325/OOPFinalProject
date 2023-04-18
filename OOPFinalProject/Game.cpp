#include"Game.h"
#include<math.h>

Game::Game()
{
	if (!font.loadFromFile("./Textures/1up.ttf")) {
		std::cout << "Error loading font file" << std::endl;
	}
	scoreText.setFont(font);
	scoreNum.setFont(font);
	scoreText.setPosition(400, 250);
	scoreNum.setPosition(400, 300);
	videoMode.height = 800;
	videoMode.width = 600;
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Default);
	window->setFramerateLimit(60);
	int type = rand() % 6;
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
	Render();
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
	CurrentBlock = new T;
	if (CurrentBlock->Checkintersection(well.GetBoard()))
		quit = true;
}

void Game::PollEvents()
{
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		else if (ev.key.code == sf::Keyboard::Left && ev.type == sf::Event::KeyReleased) {
			if (!quit)
				Move = 1;
		}
		else if (ev.key.code == sf::Keyboard::Right && ev.type == sf::Event::KeyReleased) {
			if (!quit)
				Move = 0;
		}
		else if (ev.key.code == sf::Keyboard::Up && ev.type == sf::Event::KeyReleased) {
			if (!quit)
				CurrentBlock->Rotate(well.GetBoard());
		}
		else if (ev.key.code == sf::Keyboard::Down && ev.type == sf::Event::KeyPressed) {
			if (!quit) {
				fastfalling = 1;
			}
		}
		else if (ev.key.code == sf::Keyboard::Down && ev.type == sf::Event::KeyReleased) {
			if (!quit) {
				fastfalling = 0;
			}
		}

	}
}
void Game::SetName(std::string n)
{
	name = n;
}

void Game::Update()
{
	PollEvents();  //Get user input
	if (!quit)
	{
		if (!CurrentBlock->IsControllable()) {
			fastfalling = 0;
			int type = rand() % 6;
			CurrentBlock->SetTetrimino(well.GetBoard());
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
			if (CurrentBlock->Checkintersection(well.GetBoard()))
				quit = 1;
		}
		if (fastfalling)
			usingspeed = 3;
		else
			usingspeed = speed - ((score / 1000) * 0.1) * speed;
		if (timer2 % 10 == 0)
			if (Move != -1) {
				CurrentBlock->ShiftX(Move, well.GetBoard());
				Move = -1;
			}
		if (timer % usingspeed == 0 && !quit) {
			timer = 0;
			CurrentBlock->Fall(well.GetBoard());         //We make the blocks fall every 30 ticks
		}
		well.CheckForLines(score);
		timer++;
		timer2++;
	}
}

void Game::Quit() {
	//Block.setSize(sf::Vector2f(500, 300));
	//Block.setFillColor(sf::Color::Red);
	//Block.setPosition(50, 200);
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
	well.PrintBoard(window);
	if(!quit)
	CurrentBlock->DrawTetrimino(window);
	if (quit) {
		Quit();
		window->draw(Block);
	}
	window->display();
}
