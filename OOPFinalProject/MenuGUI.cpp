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
	levelText.setFont(font);
	levelNum.setFont(font);
	scoreText.setFont(font);
	scoreNum.setFont(font);
	levelx = 400;
	levely = 50;
	levelText.setPosition(levelx, levely);
	levelNum.setPosition(levelx + 150, levely);
	levelText.setCharacterSize(30);
	levelNum.setCharacterSize(30);
	levelText.setString("Level");
	nextTetx = 400;
	nextTety = 220;

	TetriminoBlock.setPosition(nextTetx, nextTety);
	TetriminoBlock.setSize(sf::Vector2f(170, 170));
	TetriminoBlock.setFillColor(sf::Color::Black);
	TetriminoBlock.setOutlineColor(sf::Color::White);
	TetriminoBlock.setOutlineThickness(5);

	scorex = 630;
	scorey = 20;
	scoreText.setPosition(scorex + 10, scorey + 50);
	scoreText.setString("Score");
	scoreNum.setPosition(scorex + 10, scorey + 100);

	//Intializes Name Spot

	NameText.setFont(font);
	NameText.setPosition(scorex, scorey);
	NameText.setCharacterSize(23);
	highscorex = 630;
	highscorey = 220;
	Highscore.setFont(font);
	Highscore.setPosition(highscorex + 10, highscorey + 10);
	Highscore.setCharacterSize(21);


	HighscoreBlock.setSize(sf::Vector2f(200, 400));
	HighscoreBlock.setPosition(highscorex, highscorey);
	HighscoreBlock.setFillColor(sf::Color(0, 0, 0, 255));
	HighscoreBlock.setOutlineColor(sf::Color::White);
	HighscoreBlock.setOutlineThickness(5);


	ScoreBlock.setSize(sf::Vector2f(200, 110));
	ScoreBlock.setPosition(scorex, scorey + 35);
	ScoreBlock.setFillColor(sf::Color(0, 0, 0, 255));
	ScoreBlock.setOutlineColor(sf::Color::White);
	ScoreBlock.setOutlineThickness(5);


	//Initialize "Enter name" block
	tutorialx = 380;
	tutorialy = 10;
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

	for (int i = highscorey + 55, k = 0; k < 5; i += 70, k++) {
		Playernames[k].setFont(font);
		Playernames[k].setPosition(highscorex + 10, i);
		Playernames[k].setCharacterSize(0);
	}
	for (int i = highscorey + 90, k = 0; k < 5; i += 70, k++) {
		Playernumbers[k].setFont(font);
		Playernumbers[k].setPosition(highscorex + 40, i);
		Playernumbers[k].setCharacterSize(0);
	}
	menuBlinking = MenuBlinkClock.getElapsedTime();

}
void MenuGUI::initializePlayerGUI(int* highscoreint) {
	for (int i = 0; i < 5; i++) {
		if (highscoreint[i] != 0) {
			Playernames[i].setCharacterSize(20);
			Playernumbers[i].setCharacterSize(18);
		}
	}
}
//Prints the menu for entering name
void MenuGUI::PrintName(sf::RenderWindow*& window) {
	menuBlinking = MenuBlinkClock.getElapsedTime();
	if (menuBlinking.asSeconds() > Blinkingtimer)
		for (int i = 0; i < 4; i++)
			window->draw(EnternameDisclaimer[i]);
	if (menuBlinking.asSeconds() > Blinkingtimer * 2)
		MenuBlinkClock.restart();
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
	//Print large block
	window->draw(ScoreBlock);
	//Print small block

	scoreNum.setString(intTostring(totalscore));
	window->draw(scoreText);
	window->draw(scoreNum);
}
void  MenuGUI::PrintTetriminoBlock(sf::RenderWindow*& window) {
	window->draw(TetriminoBlock);
}
MenuGUI::~MenuGUI() {

}