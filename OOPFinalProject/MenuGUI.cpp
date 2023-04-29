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
MenuGUI::MenuGUI() {
	if (!font.loadFromFile("./Textures/1up.ttf")) {
		std::cout << "Error loading font file" << std::endl;
	}
	scorex = 400;
	scorey = 250;
	levelx = 400;
	levely = 360;
	linex = 400;
	liney = 470;
	nextTetx = 400;
	nextTety = 40;
	namex = 400;
	namey = 250;
	highscorex = 630;
	highscorey = 40;
	Quitx = 200;
	Quity = 150;
	tutorialx = 380;
	tutorialy = 10;
	levelText.setFont(font);
	levelNum.setFont(font);
	scoreText.setFont(font);
	scoreNum.setFont(font);
	lineText.setFont(font);
	lineNum.setFont(font);
	levelText.setPosition(levelx+10, levely+50);
	levelNum.setPosition(levelx + 10, levely+100);
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

	PlayerStatsBlock.setPosition(390, 230);
	PlayerStatsBlock.setSize(sf::Vector2f(220, 400));
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
	QuitBlock.setSize(sf::Vector2f(400, 400));
	QuitBlock.setPosition(Quitx+13, Quity);
	QuitBlock.setFillColor(sf::Color(100, 0, 0, 255));
	QuitBlock.setOutlineColor(sf::Color::White);
	QuitBlock.setOutlineThickness(5);

	QuitText.setFont(font);
	QuitText.setCharacterSize(36);
	QuitText.setString("You lost!");
	QuitText.setPosition(Quitx+85, Quity+310);
	//Initialize "Enter name" block
	for (int k = 0, i = tutorialy; k < 4; k++, i += 50) {
		EnternameDisclaimer[k].setFont(font);
		EnternameDisclaimer[k].setPosition(tutorialx, i);
		EnternameDisclaimer[k].setCharacterSize(25);
	}
	EnternameDisclaimer[0].setString("Input Name");
	EnternameDisclaimer[1].setString("To Proceed");
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
	menuBlinking = MenuBlinkClock.getElapsedTime();

}
void MenuGUI::initializePlayerGUI(int* highscoreint) {
	for (int i = 0; i < 5; i++) {
		if (highscoreint[i] != 0) {
			Playernames[i].setCharacterSize(25);
			Playernumbers[i].setCharacterSize(23);
		}
	}
}
//Prints the menu for entering name
void MenuGUI::PrintNameEnter(sf::RenderWindow*& window) {
	menuBlinking = MenuBlinkClock.getElapsedTime();
	if (menuBlinking.asSeconds() > Blinkingtimer)
		for (int i = 0; i < 4; i++)
			window->draw(EnternameDisclaimer[i]);
	if (menuBlinking.asSeconds() > Blinkingtimer * 2)
		MenuBlinkClock.restart();
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
	window->draw(NameText);
	//Print small block

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
	window->draw(QuitText);
}
MenuGUI::~MenuGUI() {

}