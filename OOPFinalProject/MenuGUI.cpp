
#include"MenuGUI.h"
std::string intTostring(int input) {
	if (input == 0)
		return "0";
	std::string result = "";
	while (input != 0) {
		result = char(input % 10 + '0') + result;
		input /= 10;
	}
	return result;
}
void HSVtoRGB(float H, float S, float V,int&R,int&G,int&B) {
	float s = S / 100;
	float v = V / 100;
	float C = s * v;
	float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	float m = v - C;
	float r, g, b;
	if (H >= 0 && H < 60) {
		r = C, g = X, b = 0;
	}
	else if (H >= 60 && H < 120) {
		r = X, g = C, b = 0;
	}
	else if (H >= 120 && H < 180) {
		r = 0, g = C, b = X;
	}
	else if (H >= 180 && H < 240) {
		r = 0, g = X, b = C;
	}
	else if (H >= 240 && H < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}
	 R = (r + m) * 255;
	 G = (g + m) * 255;
	 B = (b + m) * 255;
}
void MenuGUI::SetTetrisColor() {
	int R=0, G=0, B=0;
	int speed = 100;
	if(TetrisColorClock.getElapsedTime().asSeconds() *speed>= 360)
		TetrisColorClock.restart();
 	HSVtoRGB(TetrisColorClock.getElapsedTime().asSeconds() * speed, 100, 100, R, G, B);
	TETRIS.setFillColor(sf::Color(R, G, B));
}
MenuGUI::MenuGUI() {
	if (!font.loadFromFile("./Textures/1up.ttf")) {
		std::cout << "Error loading font file" << std::endl;
	}
	if (!EndingSkullTexture[0].loadFromFile("./Textures/Skull.png")) {
		std::cout << "Error loading Skull texture file" << std::endl;
	}
	if (!EndingSkullTexture[1].loadFromFile("./Textures/Skull1.png")) {
		std::cout << "Error loading Skull texture file" << std::endl;
	}
	scorex = 400;
	scorey = 350;
	levelx = 400;
	levely = 460;
	linex = 400;
	liney = 570;
	nextTetx = 400;
	nextTety = 140;
	namex = 410;
	namey = 350;
	highscorex = 630;
	highscorey = 140;
	Quitx = 25;
	Quity = 25;
	tutorialx = 150;
	tutorialy = 300;
	levelText.setFont(font);
	levelNum.setFont(font);
	scoreText.setFont(font);
	scoreNum.setFont(font);
	lineText.setFont(font);
	lineNum.setFont(font);
	TETRIS.setFont(font);
	TETRIS.setPosition(430, 20);
	TETRIS.setCharacterSize(75);
	TETRIS.setString("TETRIS");
	levelText.setPosition(levelx + 10, levely + 50);
	levelNum.setPosition(levelx + 10, levely + 100);
	levelText.setCharacterSize(30);
	levelNum.setCharacterSize(30);
	levelText.setString("Level:");

	scoreText.setPosition(scorex + 10, scorey + 50);
	scoreNum.setPosition(scorex + 10, scorey + 100);
	scoreText.setString("Score:");

	lineText.setPosition(linex + 10, liney + 50);
	lineNum.setPosition(linex + 10, liney + 100);
	lineText.setCharacterSize(30);
	lineNum.setCharacterSize(30);
	lineText.setString("Lines:");

	TetriminoBlock.setPosition(nextTetx, nextTety);
	TetriminoBlock.setSize(sf::Vector2f(170, 170));
	TetriminoBlock.setFillColor(sf::Color::Black);
	TetriminoBlock.setOutlineColor(sf::Color::White);
	TetriminoBlock.setOutlineThickness(5);


	//Intializes Name Spot

	NameText.setFont(font);
	NameText.setPosition(namex, namey);
	NameText.setCharacterSize(26);

	PlayerStatsBlock.setPosition(400, 330);
	PlayerStatsBlock.setSize(sf::Vector2f(200, 400));
	PlayerStatsBlock.setFillColor(sf::Color(0, 0, 0, 0));
	PlayerStatsBlock.setOutlineColor(sf::Color::White);
	PlayerStatsBlock.setOutlineThickness(5);

	Highscore.setFont(font);
	Highscore.setPosition(highscorex + 10, highscorey + 10);
	Highscore.setCharacterSize(21);


	HighscoreBlock.setSize(sf::Vector2f(200, 590));
	HighscoreBlock.setPosition(highscorex, highscorey);
	HighscoreBlock.setFillColor(sf::Color(0, 0, 0, 255));
	HighscoreBlock.setOutlineColor(sf::Color::White);
	HighscoreBlock.setOutlineThickness(5);


	//Initialize Quit Block
	QuitBlock.setSize(sf::Vector2f(-5 + 36 * 10, -5 + 36 * 20));
	QuitBlock.setPosition(Quitx, Quity);
	QuitBlock.setFillColor(sf::Color(100, 0, 0, 180));
	QuitBlock.setOutlineColor(sf::Color::White);
	QuitBlock.setOutlineThickness(5);
	QuitBlock.setOutlineColor(sf::Color(255, 0, 0, 255));

	QuitText.setFont(font);
	QuitText.setCharacterSize(36);
	QuitText.setString("You lost!");
	QuitText.setPosition(Quitx + 50, Quity + 600);
	for (int i = 0; i < 2; i++) {
		EndingSkullSprite[i].setTexture(EndingSkullTexture[i]);
		EndingSkullSprite[i].setPosition(20, 150);
		EndingSkullSprite[i].setScale(sf::Vector2f(0.8, 0.8));
	}

	Restart.setFont(font);
	Restart.setCharacterSize(25);
	Restart.setString("Press R to Restart");
	Restart.setPosition(Quitx, Quity + 650);
	//Initialize "Enter name" block
	for (int k = 0, i = tutorialy; k < 4; k++, i += 50) {
		EnternameDisclaimer[k].setFont(font);
		EnternameDisclaimer[k].setPosition(tutorialx, i);
		EnternameDisclaimer[k].setCharacterSize(25);
	}
	EnternameDisclaimer[0].setString("Input Name");
	EnternameDisclaimer[1].setString("To Proceed:");
	EnternameDisclaimer[2].setString("Press Enter");
	EnternameDisclaimer[3].setString("To confirm");
	Blinkingtimer = 0.5;
	//Initializes tetromino and player menu for gui
	Tetromino.setFont(font);

	for (int i = highscorey + 55, k = 0; k < 5; i += 100, k++) {
		Playernames[k].setFont(font);
		Playernames[k].setPosition(highscorex + 10, i);
		Playernames[k].setCharacterSize(0);
	}
	for (int i = highscorey + 90, k = 0; k < 5; i += 100, k++) {
		Playernumbers[k].setFont(font);
		Playernumbers[k].setPosition(highscorex + 40, i);
		Playernumbers[k].setCharacterSize(0);
	}
	Blinking = BlinkClock.getElapsedTime();

}
void MenuGUI::initializePlayerGUI(int* highscoreint) {
	for (int i = 0; i < 5; i++) {
		if (highscoreint[i] != 0) {
			Playernames[i].setCharacterSize(25);
			Playernumbers[i].setCharacterSize(23);
		}
	}
}
void MenuGUI::PrintTetris(sf::RenderWindow*&window) {
	window->draw(TETRIS);
}
//Prints the menu for entering name
void MenuGUI::PrintNameEnter(sf::RenderWindow*& window) {
	Blinking = BlinkClock.getElapsedTime();
	if (Blinking.asSeconds() > Blinkingtimer)
		for (int i = 0; i < 4; i++)
			window->draw(EnternameDisclaimer[i]);
	if (Blinking.asSeconds() > Blinkingtimer * 2)
		BlinkClock.restart();
}
void MenuGUI::PrintName(sf::RenderWindow*& window) {
	window->draw(NameText);
}
void MenuGUI::PrintPlayers(sf::RenderWindow*& window, std::string* highscorenames, int* highscoreint) {
	window->draw(HighscoreBlock);
	Highscore.setString("High Scores");
	for (int i = 0; i < 5; i++) {
		if (highscoreint[i] != 0) {
			Playernames[i].setString(highscorenames[i]);
			Playernumbers[i].setString(intTostring(highscoreint[i]));
			window->draw(Playernames[i]);
			window->draw(Playernumbers[i]);
		}
	}
	window->draw(Highscore);
}
void MenuGUI::PrintLevel(sf::RenderWindow*& window, int& totalscore) {
	window->draw(levelText);
	levelNum.setString(intTostring((totalscore / 1000) + 1));
	window->draw(levelNum);
}
void MenuGUI::PrintScore(sf::RenderWindow*& window, int& totalscore) {
	scoreNum.setString(intTostring(totalscore));
	window->draw(scoreText);
	window->draw(scoreNum);

	window->draw(PlayerStatsBlock);
}
void MenuGUI::PrintLines(sf::RenderWindow*& window, int& totalscore) {
	window->draw(lineText);
	lineNum.setString(intTostring(totalscore / 100));
	window->draw(lineNum);
}
void  MenuGUI::PrintTetriminoBlock(sf::RenderWindow*& window) {
	window->draw(TetriminoBlock);
}
void MenuGUI::PrintQuitScreen(sf::RenderWindow*& window) {
	window->draw(QuitBlock);
	Blinking = BlinkClock.getElapsedTime();
	if (Blinking.asSeconds() > Blinkingtimer) {
		window->draw(EndingSkullSprite[0]);
	}
	else {
		window->draw(EndingSkullSprite[1]);
	}
	if (Blinking.asSeconds() > Blinkingtimer * 2) {
		BlinkClock.restart();
	}
	window->draw(QuitText);
	window->draw(Restart);
}
MenuGUI::~MenuGUI() {

}