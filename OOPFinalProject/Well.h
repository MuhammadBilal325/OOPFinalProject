#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
template<typename T>
void swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}
class Well {
private:
	int rows, columns;
	int** board;
	sf::RectangleShape BoardShape;
	sf::Sprite Tiles[8];
	sf::Texture Tiletextures[8];
public:
	Well();
	Well(Well&);
	~Well();
	void ResetBoard();
	int** GetBoard() { return board; }
	void CheckForLines(int& score, int& totalscore);
	void SwapUp(int row);
	void PrintBoard(sf::RenderWindow*& window);
	int GetRows() { return rows; }
	int GetColumns() { return columns; }
};