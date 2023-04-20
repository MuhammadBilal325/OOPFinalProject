#include"Game.h"
#include<math.h>
int numofpiecesavailable = 7;
int getStringLength(std::string s) {
	int i = 0;
	for (; s[i] != '\0'; i++);
	return i;
}
void ReplaceStringchar(std::string& s, char c, char r) {
	int size = getStringLength(s);
	for (int i = 0; i < size; i++)
		if (s[i] == c)
			s[i] = r;
}
void Game::InitializeHighscores()
{
	for (int i = 0; i < 5; i++)
		highscoreint[i] = 0;
	std::ifstream fin;
	fin.open("Highscores.txt");
	int x = 0;
	while (x<5 && fin >> highscorenames[x] >> highscoreint[x]) {
		x++;
	}
	if (x < 5)
		for (int i = x; i < 5; i++) {
			highscorenames[i] = "";
			highscoreint[x] = 0;
		}

	for (int i = 0; i < 5; i++) {
		ReplaceStringchar(highscorenames[i], '-', ' ');
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
	Move = -1;
	speed = 60;
	fallinginterval = 60;
	score = 0;
	totalscore = 0;
	namesize = 1;
	scoresfinalized = 0;
	name = "";
	videoMode.height = 800;
	videoMode.width = 600;
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Default);
	window->setFramerateLimit(60);
	int type = rand() % numofpiecesavailable;
	nexttype = rand() % numofpiecesavailable;
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

	if (nexttype == 0)
		CreateNextTetrimino<Ishape>();
	else if (nexttype == 1)
		CreateNextTetrimino<Jshape>();
	else if (nexttype == 2)
		CreateNextTetrimino<Lshape>();
	else if (nexttype == 3)
		CreateNextTetrimino<Oshape>();
	else if (nexttype == 4)
		CreateNextTetrimino<Sshape>();
	else if (nexttype == 5)
		CreateNextTetrimino<Tshape>();
	else if (nexttype == 6)
		CreateNextTetrimino<Zshape>();


	name = "";
	//Intializes Name Spot
	menu.NameText.setString(name);
	menu.initializePlayerGUI(highscoreint);
	fallingtime = fallingclock.getElapsedTime();
	movementtime = movementclock.getElapsedTime();
	Render();
}

Game::~Game()
{
	delete window;
	delete CurrentBlock;
	delete NextBlock;
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
template<typename T>
void Game::CreateNextTetrimino() {
	NextBlock = new T;
	NextBlock->SetControllable(0);
}

void Game::PollEvents()
{
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		if (ev.key.code == sf::Keyboard::Escape)
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
		else if (ev.type == sf::Event::TextEntered && ev.text.unicode < 127 && ev.text.unicode > 31) {
			if (getStringLength(name) < 9) {
				name += ev.text.unicode;;
				menu.NameText.setString(name);
			}
		}
		else if (ev.key.code == sf::Keyboard::Backspace) {
			namesize = getStringLength(name);
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
//The update loop is very simple, first we poll the user inputs through the pollevents function, 
//then we run several if statements to run the block spawning, dropping and line checking functions
//These if statements are superseded by condition that they only run if the game is running and the name is entered

void Game::Update()
{
	PollEvents();  //Get user input
	fallingtime = fallingclock.getElapsedTime();
	movementtime = movementclock.getElapsedTime();
	if (!quit && isnameentered)
	{
		if (!CurrentBlock->IsControllable()) {
			fastfalling = 0;
			int type = nexttype;
			nexttype = rand() % numofpiecesavailable;
			CurrentBlock->SetTetrimino(well.GetBoard());
			delete CurrentBlock;
			delete NextBlock;
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
			if (nexttype == 0)
				CreateNextTetrimino<Ishape>();
			else if (nexttype == 1)
				CreateNextTetrimino<Jshape>();
			else if (nexttype == 2)
				CreateNextTetrimino<Lshape>();
			else if (nexttype == 3)
				CreateNextTetrimino<Oshape>();
			else if (nexttype == 4)
				CreateNextTetrimino<Sshape>();
			else if (nexttype == 5)
				CreateNextTetrimino<Tshape>();
			else if (nexttype == 6)
				CreateNextTetrimino<Zshape>();
		}
		if (fastfalling)
			fallinginterval = 3;
		else
			fallinginterval = speed - ((score / 1000) * 0.1) * speed;
		if (movementtime.asSeconds() >= 0.1)
			if (Move != -1) {
				movementclock.restart();
				CurrentBlock->ShiftX(Move, well.GetBoard());
				Move = -1;
			}
		if (fallingtime.asSeconds() * 60 >= fallinginterval && !quit) {
			fallingclock.restart();
			CurrentBlock->Fall(well.GetBoard());
		}
		well.CheckForLines(score, totalscore);
	}
	score %= 8000;
}

void Game::Quit() {

}

void Game::FinalizeScores()
{
	//If scores have already been written we just return
	if (scoresfinalized)
		return;
	scoresfinalized = 1;
	//If highscores are less than 5 then we write ours at the end
	if (highscoressize < 5) {
		highscoreint[highscoressize] = totalscore;
		highscorenames[highscoressize] = name;
		menu.initializePlayerGUI(highscoreint);
	}
	//Rearrange the scores
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			if (highscoreint[i] < highscoreint[j]) {
				swap(highscoreint[i], highscoreint[j]);
				swap(highscorenames[i], highscorenames[j]);
			}
		}
	}
	//If there are 5 highscores already we replace the appropiate one with ours
	if (highscoressize == 5) {

		int largest = 4;
		for (int i = 0; i < 5; i++) {
			if (highscoreint[i] > highscoreint[largest] && highscoreint[i] < totalscore)
				largest = i;
		}
		if (totalscore > highscoreint[largest]) {
			highscoreint[largest] = totalscore;
			highscorenames[largest] = name;
		}
	}
	//Write the highscores back to the text file
	std::ofstream fout;
	//We replace all spaces with hyphens before writing
	for (int i = 0; i < 5; i++) {
		ReplaceStringchar(highscorenames[i], ' ', '-');
	}
	fout.open("Highscores.txt");
	for (int i = 0; i < 5; i++) {
		if (highscoreint[i] != 0)
			fout << highscorenames[i] << " " << highscoreint[i] << std::endl;
	}
	fout.close();
	//Replace all hyphens with spaces after writing
	for (int i = 0; i < 5; i++) {
		ReplaceStringchar(highscorenames[i], '-', ' ');
	}
}
//The printing function prints all the elements one by one
void Game::Render()
{
	window->clear();
	menu.PrintLevel(window, totalscore);//Print the current level
	menu.PrintScore(window, totalscore);//Print the current score
	menu.PrintPlayers(window, highscorenames, highscoreint);//Print the leaderboard and previous highscores
	well.PrintBoard(window);//Print the actual board for playing
	//If game is running and name has been entered, print the next tetromino in a window at the top right
	if (!quit && isnameentered) {
		menu.PrintTetriminoBlock(window); //Print the Block where the next tetromino to come will be printed
		NextBlock->DrawTetriminoatCoordinates(window, 12, 1);
		CurrentBlock->DrawTetrimino(window);
	}
	if (!isnameentered)
		menu.PrintName(window);
	//If game has been quit, finalize the scores and print quit screen
	if (quit) {
		FinalizeScores();
		Quit();
	}
	window->display();
}
