#include<iostream>
#include"Game.h"
#include"SFML/Graphics.hpp"
Well::Well() {
	board = new int* [20];
	for (int i = 0; i < 20; i++)
		board[i] = new int[10];
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			board[i][j] = 0;
	char tiletexturepath[21] = "./Textures/Tile1.png";
	if (!BoardTexture.loadFromFile("./Textures/board.png")) {
		std::cout << "Error loading board..." << std::endl;
	}
	for (int i = 0; i < 8; i++)
	{
		tiletexturepath[15] = i + 1 + 48;
		if (!Tiletextures[i].loadFromFile(tiletexturepath)) {
			std::cout << "Error loading TileTexture..." << std::endl;
		}
		Tiles[i] = sf::Sprite(Tiletextures[i]);
	}

	Board = sf::Sprite(BoardTexture);
	Board.setScale(1, 1);
	Board.setPosition(20, 20);
}
Well::~Well() {
	for (int i = 0; i < 20; i++)
		delete[]board[i];
	delete[]board;
}


void Well::PrintBoard(sf::RenderWindow*& window)
{
	window->draw(Board);
	for (int i = 20, k = 0; i < 20 * 36 && k < 20; i += 36, k++)
		for (int j = 20, l = 0; j < 20 * 36 && l < 10; j += 36, l++)
		{
			Tiles[board[k][l]].setPosition(j, i);
			window->draw(Tiles[board[k][l]]);
		}
	window->draw(Tiles[0]);
}

void Well::CheckForLines(int& score,int&totalscore)
{
	bool continuos = 1;
	for (int i = 0; i < 20; i++)
	{
		continuos = 1;
		for (int j = 0; j < 10; j++)
			if (board[i][j] == 0)
				continuos = 0;
		if (continuos)
		{
			for (int j = 0; j < 10; j++)
				board[i][j] = 0;
			SwapUp(i);
			score += 100;
			totalscore += 100;
			i--;
		}
	}
}

void Well::SwapUp(int row)
{
	for (int i = row; i > 0; i--)
		for (int j = 0; j < 10; j++)
			swap(board[i][j], board[i - 1][j]);
}