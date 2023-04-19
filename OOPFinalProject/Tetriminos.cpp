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
/*
* We make the block fall by one y, if its intesecting with anything we undo the fall
* and make it uncontrollable so it gets destroyed next time the update loop runs.
* If it doesnt intersect then we put it down another time and check again to see if it intersects
* If it does we make it uncontrollable
*
* The logic is simple,
* 1. Block falls
* 2. if block intersects block goes back up
* 3. if block does not intersect block takes new position
* 4. We check if block can go any further in its current position
* 5. If block can no longer go down anymore we make it uncontrollable
*
* By checking with another incrementation on the y axis we allow the block to become uncontrollable
* on the exact frame it sits on top of another block instead of the user having to wait for it to fall again
* before getting another block
*/
void Tetrimino::Fall(int** board)
{
	y++;
	if (Checkintersection(board) || CheckBounds(board))
	{
		y--;
		controllable = 0;
	}
	else {
		y++;
		if (Checkintersection(board) || CheckBounds(board)) {
			controllable = 0;
		}
		y--;
	}
}
/*
This function takes the board of 20x10 cells as an input and rotates the tetrimino accordingly. The tetrimino is rotated using a general formula for most tetrominos but a customized one for I shape and O shape
First we take a new array and in that array we store a transpose of the current array
Then we reverse every row of the new transposed array, this completes the first part of the rotation
In the second part, we check if rotating the piece put it out of bounds.
If it did, we check if its "poking" into another piece or out of the bounds.
We count the amount of blocks it is poking out by and then move it that amount on the x axis
in order to "kick" it back into the box.

*/
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
	int oldx = x;
	int pokingout = 0;
	bool intersect = 0;
	if (Checkintersection(board) || CheckBounds(board)) {
		for (int j = x; j < x + columns; j++)
		{
			if ((board[y][j] != 0 && intersect == 0) || j >= 10)
				intersect = 1;
			if (intersect)
				pokingout++;
		}
		x -= pokingout;
		if (Checkintersection(board) || CheckBounds(board)) {
			//Undo move
			x += pokingout;
			shape = temp;
			swap(rows, columns);
			for (int i = 0; i < columns; i++)
				delete[]newarr[i];
			delete[]newarr;
		}
		else {//Keep move
			for (int i = 0; i < columns; i++)
				delete[]temp[i];
			delete[]temp;
		}
	}
	else {//Keep move
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

void Tetrimino::DrawTetrimino(sf::RenderWindow*& window) {
	for (int i = y; i < y + rows; i++)
		for (int j = x; j < x + columns; j++)
		{
			if (shape[i - y][j - x] != 0) {
				Tile.setPosition(((36 * (j + 1)) - 16), ((36 * (i + 1)) - 16));
				window->draw(Tile);
			}
		}
}

void Tetrimino::DrawTetriminoatCoordinates(sf::RenderWindow*& window, int xcoord, int ycoord)
{
	for (int i = ycoord; i < ycoord + rows; i++)
		for (int j = xcoord; j < xcoord + columns; j++)
		{
			if (shape[i - ycoord][j - xcoord] != 0) {
				Tile.setPosition(((36 * (j + 1)) - 16), ((36 * (i + 1)) - 16));
				window->draw(Tile);
			}
		}
}

