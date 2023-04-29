#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
class MenuGUI {
	friend class Game;
private:
	sf::RectangleShape Block, PlayerBlock, HighscoreBlock,QuitBlock;
	sf::RectangleShape NameBlock;
	sf::RectangleShape TetriminoBlock;
	sf::RectangleShape PlayerStatsBlock;
	sf::Clock BlinkClock;
	sf::Time Blinking;
	float Blinkingtimer;
	sf::Text EnternameDisclaimer[4];
	sf::Font font;
	sf::Text TETRIS,scoreText, levelText, levelNum, scoreNum, lineText, lineNum, Tetromino, QuitText;
	sf::Text Highscore, Playernames[5], Playernumbers[5];
	sf::Text NameText;

	sf::Sprite EndingSkullSprite[2];
	sf::Texture EndingSkullTexture[2];
	//coordinates for easy repositioning of gui elements
	int namex, namey;
	int scorex, scorey;
	int levelx, levely;
	int tutorialx, tutorialy;
	int nextTetx, nextTety;
	int highscorex, highscorey;
	int Quitx, Quity;
	int linex, liney;
public:
	MenuGUI();
	~MenuGUI();
	void initializePlayerGUI(int*);
	void PrintTetris(sf::RenderWindow*&window);
	void PrintNameEnter(sf::RenderWindow*& window);
	void PrintName(sf::RenderWindow*& window);
	void PrintScore(sf::RenderWindow*& window, int&);
	void PrintLevel(sf::RenderWindow*& window, int&);
	void PrintLines(sf::RenderWindow*& window, int&);
	void PrintTetriminoBlock(sf::RenderWindow*& window);
	void PrintPlayers(sf::RenderWindow*& window, std::string* highscorenames, int* highscoreint);
	void PrintQuitScreen(sf::RenderWindow*& window);
};