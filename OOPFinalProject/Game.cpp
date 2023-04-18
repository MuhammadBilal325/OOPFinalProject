#include"Game.h"
#include<math.h>



void Game::InitializeHighscores()
{
	name = "Jerry";
	for (int i = 0; i < 5; i++)
		highscoreint[i] = 0;
	std::ifstream fin;
	fin.open("Highscores.txt");
	int x = 0;
	while (x<5 && fin >>highscorenames[x]>>highscoreint[x]) {
		x++;
	}
	highscoressize = x;
	fin.close();
}

Game::Game()
{
	InitializeHighscores();
	quit = 0;
	fastfalling = 0;
	isnameentered = 0;
	timer = 0;
	timer2 = 0;
	Move = -1;
	speed = 60;
	usingspeed = 60;
	score = 0;
	totalscore = 0;
	namesize = 1;
	name = "";
	videoMode.height = 800;
	videoMode.width = 600;
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Default);
	window->setFramerateLimit(60);
	int type = rand() % 7;
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
	name = "";
	//Intializes Name Spot
	menu.NameText.setString(name);
	for (int i = 0; i < highscoressize; i++) {

		menu.Playernames[i].setCharacterSize(20);
		menu.Playernumbers[i].setCharacterSize(18);
	}
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
		if (isnameentered) {
			if (ev.key.code == sf::Keyboard::Left && ev.type == sf::Event::KeyReleased) {
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
			else if (ev.key.code == sf::Keyboard::K) {
				score += 1000;
				totalscore += 1000;
			}
		}
		else if (ev.type == sf::Event::TextEntered && ev.text.unicode<127 && ev.text.unicode > 31) {
				std::cout << ev.text.unicode;
				name += ev.text.unicode;;
				menu.NameText.setString(name);
		}
		else if (ev.key.code==sf::Keyboard::Backspace) {
			namesize = 0;
			for (int i = 0; name[i] != '\0'; i++)
				++namesize;
			if (namesize > 0) {
				char* newarr = new char[namesize];
				for (int i = 0; i < namesize; i++)
					newarr[i] = name[i];
				newarr[namesize - 1] = '\0';
				name = newarr;
				delete[]newarr;
			}
			else
				name = "";
			menu.NameText.setString(name);
		}
		else if (ev.key.code == sf::Keyboard::Enter) {
			isnameentered = 1;
			menu.NameText.setString(name);
		}

	}
}
void Game::Update()
{
	PollEvents();  //Get user input
	if (!quit && isnameentered)
	{
		if (!CurrentBlock->IsControllable()) {
			fastfalling = 0;
			int type = rand() % 7;
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
			CurrentBlock->Fall(well.GetBoard());         
		}
		well.CheckForLines(score,totalscore);
		timer++;
		timer2++;
	}
	score %= 8000;
}

void Game::Quit() {

}

void Game::FinalizeScores()
{
	for (int i = 0; i < highscoressize; i++) {
		for (int j = i; j < highscoressize; j++) {
			if (highscoreint[i] < highscoreint[j]) {
				swap(highscoreint[i], highscoreint[j]);
				swap(highscorenames[i], highscorenames[j]);
			}
		}
	}
	int largest = highscoressize - 1;
	for (int i = 0; i < highscoressize; i++) {
		if (highscoreint[i] > highscoreint[largest] && highscoreint[i] < totalscore)
			largest = i;
	}
	if (totalscore > highscoreint[largest]) {
		highscoreint[largest] = totalscore;
		highscorenames[largest] = name;
	}
	std::ofstream fout;

	fout.open("Highscores.txt");
	for (int i = 0; i < highscoressize; i++) {
		fout << highscorenames[i] << " " << highscoreint[i] << std::endl;
	}
	fout.close();
}
void Game::Render()
{
	window->clear();
	menu.PrintLevel(window, totalscore);
    menu.PrintScore(window,totalscore);
	menu.PrintPlayers(window,highscorenames,highscoreint);
	well.PrintBoard(window);
	if(!quit && isnameentered)
	CurrentBlock->DrawTetrimino(window);
	if (!isnameentered)
		menu.PrintName(window);
	if (quit) {
		FinalizeScores();
		Quit();
	}
	window->display();
}
