
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
	for (int i = 0; i < 5; i++) {
		highscorenames[i] = "";
		highscoreint[i] = 0;
	}
	std::ifstream fin;
	fin.open("Highscores.txt");
	int x = 0;
	while (x<5 && fin >> highscorenames[x] >> highscoreint[x]) {
		x++;
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
	timetofall = 1;
	score = 0;
	totalscore = 0;
	namesize = 1;
	scoresfinalized = 0;
	name = "";
	videoMode.height = 750;
	videoMode.width = 850;
	window = new sf::RenderWindow(videoMode, "Tetris", sf::Style::Default);
	window->setFramerateLimit(60);
	orignextTx = 12.35;
	orignextTy = 5.5;
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

	nextTx = orignextTx;
	nextTy = orignextTy;
	if (nexttype == 0) {
		CreateNextTetrimino<Ishape>();
		nextTx = orignextTx + 0.45;
		nextTy = orignextTy - 0.5;
		NextBlock->RotateUnbounded();
	}
	else if (nexttype == 1)
		CreateNextTetrimino<Jshape>();
	else if (nexttype == 2)
		CreateNextTetrimino<Lshape>();
	else if (nexttype == 3) {
		CreateNextTetrimino<Oshape>();
		nextTx = orignextTx;
		nextTy = orignextTy - 0.5;
	}
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
	if (CurrentBlock->Checkintersection(well)) {
		quit = true;
		delete CurrentBlock;
		CurrentBlock = nullptr;
	}
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
		if (isnameentered && !quit)
		{
			if (ev.key.code == sf::Keyboard::Left && ev.type == sf::Event::KeyPressed) {
				if (!quit)
					Move = 1;
			}
			else if (ev.key.code == sf::Keyboard::Right && ev.type == sf::Event::KeyPressed) {
				if (!quit)
					Move = 0;
			}
			else if (ev.key.code == sf::Keyboard::Up && ev.type == sf::Event::KeyPressed) {
				if (!quit)
					CurrentBlock->Rotate(well);
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
			else if (ev.key.code == sf::Keyboard::Q) {
				quit = 1;
				isnameentered = 1;
			}
		}
		else if (quit && ev.type==sf::Event::KeyPressed && ev.key.code==sf::Keyboard::R){
			Restart();
		}
		if (!isnameentered) {
			if (ev.type == sf::Event::TextEntered && ev.text.unicode < 127 && ev.text.unicode > 31) {
				if (getStringLength(name) < 8)
					name += ev.text.unicode;
			}
				else if (ev.key.code == sf::Keyboard::Backspace) {
					namesize = getStringLength(name);
					if (namesize > 0) {
						std::string newname = name.substr(0, namesize - 1);
						newname[namesize - 1] = '\0';
						name = newname;
					}
					else
						name = "";
				}
				else if (ev.key.code == sf::Keyboard::Enter)
					isnameentered = 1;
			menu.NameText.setString(name);
		}
	}
}

void Game::Restart() {
	InitializeHighscores();
	delete NextBlock;
	NextBlock = nullptr;
	quit = 0;
	fastfalling = 0;
	Move = -1;
	timetofall = 1;
	score = 0;
	totalscore = 0;
	scoresfinalized = 0;
	int type = rand() % numofpiecesavailable;
	nexttype = rand() % numofpiecesavailable;
	well.ResetBoard();
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
	nextTx = orignextTx;
	nextTy = orignextTy;
	if (nexttype == 0) {
		CreateNextTetrimino<Ishape>();
		nextTx = orignextTx + 0.45;
		nextTy = orignextTy - 0.5;
		NextBlock->RotateUnbounded();
	}
	else if (nexttype == 1)
		CreateNextTetrimino<Jshape>();
	else if (nexttype == 2)
		CreateNextTetrimino<Lshape>();
	else if (nexttype == 3) {
		CreateNextTetrimino<Oshape>();
		nextTx = orignextTx;
		nextTy = orignextTy - 0.5;
	}
	else if (nexttype == 4)
		CreateNextTetrimino<Sshape>();
	else if (nexttype == 5)
		CreateNextTetrimino<Tshape>();
	else if (nexttype == 6)
		CreateNextTetrimino<Zshape>();
}
//The update loop is very simple, first we poll the user inputs through the pollevents function, 
//then we run several if statements to run the block spawning, dropping and line checking functions
//These if statements are superseded by condition that they only run if the game is running and the name is entered

void Game::Update()
{
	//std::cout << sf::Mouse::getPosition(*window).x << " " << sf::Mouse::getPosition(*window).y << std::endl;
	PollEvents();  //Get user input
	fallingtime = fallingclock.getElapsedTime();      //Get elapsed time for falling and movement clocks
	movementtime = movementclock.getElapsedTime();
	if (!quit && isnameentered)  //We only run game functions if game hasnt been quit and if name is entered
	{
		if (!CurrentBlock->IsControllable()) //If currentblock is no longer controllable then we need to set the current block into the board and make a new random block
		{
			CurrentBlock->SetTetrimino(well);
			well.CheckForLines(score, totalscore);
			fastfalling = 0;
			int type = nexttype;
			nexttype = rand() % numofpiecesavailable;
			delete CurrentBlock;
			delete NextBlock;
			CurrentBlock = nullptr;
			NextBlock = nullptr;
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
			nextTx = orignextTx;
			nextTy = orignextTy;
			if (nexttype == 0) {
				CreateNextTetrimino<Ishape>();
				nextTx = orignextTx + 0.45;
				nextTy = orignextTy - 0.5;
				NextBlock->RotateUnbounded();
			}
			else if (nexttype == 1)
				CreateNextTetrimino<Jshape>();
			else if (nexttype == 2)
				CreateNextTetrimino<Lshape>();
			else if (nexttype == 3) {
				CreateNextTetrimino<Oshape>();
				nextTx = orignextTx;
				nextTy = orignextTy - 0.5;
			}
			else if (nexttype == 4)
				CreateNextTetrimino<Sshape>();
			else if (nexttype == 5)
				CreateNextTetrimino<Tshape>();
			else if (nexttype == 6)
				CreateNextTetrimino<Zshape>();
		}
		if (fastfalling)
			timetofall = 0.025;
		else {
			timetofall = 1;
			for (int i = 0; i < score / 1000; i++)
				timetofall *= 0.9;
		}
		if (movementtime.asSeconds() >= 0.05)
			if (Move != -1) {
				movementclock.restart();
				CurrentBlock->ShiftX(Move, well);
				Move = -1;
			}
		if (fallingtime.asSeconds() >= timetofall) {
			fallingclock.restart();
			CurrentBlock->Fall(well);
		}
		
	}
	if (quit) {
		FinalizeScores();
	}
	score %= 8000;
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
	//If there are 5 highscores already we replace the appropiate one with ours
	else if (highscoressize == 5) {
		if (highscoreint[4] < totalscore) {
			highscoreint[4] = totalscore;
			highscorenames[4] = name;
		}
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
	menu.PrintName(window);
	menu.PrintTetris(window);
	if (isnameentered) {
		menu.PrintPlayers(window, highscorenames, highscoreint);//Print the leaderboard and previous highscores
		menu.PrintScore(window, totalscore);//Print the current score
		menu.PrintLevel(window, totalscore);//Print the current level
		menu.PrintLines(window, totalscore);
		well.PrintBoard(window);//Print the actual board for playing
		//Print the Block where the next tetromino to come will be printed
		menu.PrintTetriminoBlock(window);
		NextBlock->DrawTetriminoatCoordinates(window, nextTx, nextTy);
		if (!quit)
			CurrentBlock->DrawTetrimino(window);
	}
	else
		menu.PrintNameEnter(window);
	//If game has been quit, finalize the scores and print quit screen
	if (quit) {
		menu.PrintQuitScreen(window);
	}
	window->display();
}
