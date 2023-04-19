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

	levelText.setPosition(400, 150);
	levelNum.setPosition(520, 150);
	levelText.setCharacterSize(25);
	levelNum.setCharacterSize(25);
	levelText.setString("Level");

	scoreText.setPosition(400, 250);
	scoreText.setString("Score");
	scoreNum.setPosition(400, 300);

	//Intializes Name Spot
	NameText.setFont(font);
	NameText.setPosition(390, 200);
	NameText.setCharacterSize(23);

	Highscore.setFont(font);
	Highscore.setPosition(400, 380);
	Highscore.setCharacterSize(21);

	HighscoreBlock.setSize(sf::Vector2f(200, 400));
	HighscoreBlock.setPosition(390, 370);
	HighscoreBlock.setFillColor(sf::Color(0, 0, 0, 255));
	HighscoreBlock.setOutlineColor(sf::Color::White);
	HighscoreBlock.setOutlineThickness(5);

	ScoreBlock.setSize(sf::Vector2f(200, 110));
	ScoreBlock.setPosition(390, 235);
	ScoreBlock.setFillColor(sf::Color(0, 0, 0, 255));
	ScoreBlock.setOutlineColor(sf::Color::White);
	ScoreBlock.setOutlineThickness(5);


	//Initialize Nameblocks
	NameBlock.setPosition(20, 20);
	NameBlock.setFillColor(sf::Color::Black);
	NameBlock.setSize(sf::Vector2f(360, 720));
	for (int k = 0, i = 100; k < 4; k++, i += 50) {
		EnternameDisclaimer[k].setFont(font);
		EnternameDisclaimer[k].setPosition(120, i);
		EnternameDisclaimer[k].setCharacterSize(25);
	}
	EnternameDisclaimer[0].setString("Input Name");
	EnternameDisclaimer[1].setString("To Proceed:");
	EnternameDisclaimer[2].setString("Press Enter");
	EnternameDisclaimer[3].setString("To confirm");
	//Initializes tetromino and player menu for gui
	Tetromino.setFont(font);

	for (int i = 425, k = 0; k < 5; i += 70, k++) {
		Playernames[k].setFont(font);
		Playernames[k].setPosition(400, i);
		Playernames[k].setCharacterSize(0);
	}
	for (int i = 460, k = 0; k < 5; i += 70, k++) {
		Playernumbers[k].setFont(font);
		Playernumbers[k].setPosition(430, i);
		Playernumbers[k].setCharacterSize(0);
	}
}
void MenuGUI::initializePlayerGUI(int*highscoreint) {
	for (int i = 0; i < 5; i++) {
		if (highscoreint[i] != 0) {
		Playernames[i].setCharacterSize(20);
		Playernumbers[i].setCharacterSize(18);
		}
	}
}
void MenuGUI::PrintName(sf::RenderWindow*& window) {
	window->draw(NameBlock);
	for (int i = 0; i < 4; i++)
		window->draw(EnternameDisclaimer[i]);
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
MenuGUI::~MenuGUI() {

}