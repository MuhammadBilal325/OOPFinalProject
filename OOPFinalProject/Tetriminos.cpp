#include<iostream>
#include"Tetriminos.h"

template<typename T>
void swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}
Tetrimino::~Tetrimino() {
	for (int i = 0; i < rows; i++)
		delete[]shape[i];
	delete[]shape;
}

void Tetrimino::Fall(int **board)
{
	y++;
	if (CheckBounds(board) || Checkintersection(board))
	{
		y--;
		controllable = 0;
	}
}

//This function takes the board of 20x10 cells as an input and rotates the tetrimino accordingly. The tetrimino is rotated using a general formula for most tetrominos but a customized one for I shape and O shape
//First we take a new array and in that array we store a transpose of the current array
// Then we reverse every row of the new transposed array, this completes the first part of the rotation
// In the second part, we check if rotating the piece put it out of bounds.
// If it did, the tetrimino is shifted "columns" amount of blocks to the right and with every shift we check if its in a valid spot,
// Similarly, the tetrimino is shifted "columns" amount of blocks to the left and we check for the spots validity.
void Tetrimino::Rotate(int** board)
{
	swap(rows, columns);
	int** newarr = new int* [rows];
	for (int i = 0; i < rows; i++)
		newarr[i] = new int[columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			newarr[i][j] = shape[j][i];
	for (int k = 0; k < rows; k++)
		for (int i = 0, j = columns - 1; i < columns / 2; i++, j--) {
			swap(newarr[k][i], newarr[k][j]);
		}
	int** temp = shape;
	shape = newarr;
	int tempx = x;
	bool flag = 0, flag2 = 0;
	int pokingout = 0;
	if (Checkintersection(board) || CheckBounds(board)) {
		for (; x > tempx - 4 && !flag && !flag2; --x) {
			if (Checkintersection(board))
				flag2 = 1;
			if (CheckBounds(board) && !flag2);
			else {
				flag = 1;
				++x;
			}
		}
		if (!flag && !flag2) {
			x += 4;
			for (; x < tempx + 4 && !flag && !flag2; ++x) {
				if (Checkintersection(board))
					flag2 = 1;
				if (CheckBounds(board) && !flag2);
				else {
					flag = 1;
					--x;
				}
			}
		}
		if (!flag)
		{
			for (int i = 0; i < rows; i++)
				delete[]shape[i];
			delete[]shape;
			shape = temp;
			x = tempx;
		}
	}
	else {
		for (int i = 0; i < columns; i++)
			delete[]temp[i];
		delete[]temp;
	}
}
//Returns true if tetrimino is intersecting. False if not intersecting
bool Tetrimino::Checkintersection(int** board)
{
	for (int i = y; i < y + rows && i < 20; i++)
		for (int j = x; j < x + columns && j < 10; j++)
			if (i < 20 || i >= 0 || j < 10 || j >= 0)
				if (board[i][j] != 0 && shape[i - y][j - x] != 0)
					return true;
	return false;
}
//Returns true if tetrimino is currently out of bounds
bool Tetrimino::CheckBounds(int** board)
{
	for (int i = y; i < y + rows; i++)
		for (int j = x; j < x + columns; j++)
			if ((i >= 20 || i < 0 || j >= 10 || j < 0) && shape[i - y][j - x] != 0)
				return true;
	return false;
}

void Tetrimino::MoveX(bool i)
{
	if (i)
		x--;
	else
		x++;
}

void Tetrimino::ShiftX(bool i, int** board)
{
	if (controllable)
	{
		MoveX(i);
		if (Checkintersection(board) || CheckBounds(board))
			MoveX(!i);
	}
}

void Tetrimino::SetTetrimino(int** board)
{
	for (int i = y; i < y + rows; i++)
		for (int j = x; j < x + columns; j++) {
			if (i < 20 && j < 10 && shape[i - y][j - x] != 0)
				board[i][j] = shape[i - y][j - x];
		}
}

void Tetrimino::ResetTetrimino(int** board)
{
	for (int i = y; i < y + rows; i++)
		for (int j = x; j < x + columns; j++) {
			if (i < 20 && j < 10 && shape[i - y][j - x] != 0)
				board[i][j] = 0;
		}
}

void Tetrimino::DrawTetrimino(sf::RenderWindow*&window) {
	for(int i=y;i<y+rows;i++)
		for (int j = x; j < x + columns; j++)
		{
			if (shape[i-y][j-x]!=0) {
			Tile.setPosition(((36 * (j + 1)) - 16), ((36 * (i + 1)) - 16));
			window->draw(Tile);
			}
		}
}

