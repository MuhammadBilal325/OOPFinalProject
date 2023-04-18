#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
class MenuGUI {
	friend class Game;
private:
	sf::RectangleShape Block, ScoreBlock, PlayerBlock,HighscoreBlock;
	sf::RectangleShape NameBlock;
	sf::Text EnternameDisclaimer[4];
	sf::Font font;
	sf::Text scoreText, levelText,levelNum, scoreNum, Tetromino;
	sf::Text Highscore, Playernames[5], Playernumbers[5];
	sf::Text NameText;

public:
	MenuGUI();
	~MenuGUI();
	void PrintName(sf::RenderWindow*&window);
	void PrintScore(sf::RenderWindow*& window,int&);
	void PrintLevel(sf::RenderWindow*& window, int&);
	void PrintPlayers(sf::RenderWindow*& window,std::string*highscorenames,int*highscoreint);
	
};