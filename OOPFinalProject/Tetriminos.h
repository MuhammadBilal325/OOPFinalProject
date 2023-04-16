#include<iostream>
#include<SFML/Graphics.hpp>
class Tetrimino
{
private:
	int index;
protected:
	int shape[4][4];
	int rotation;
	int x, y;
	bool controllable;
public:
	Tetrimino() :x(0), y(0), rotation(0), controllable(1) {}
	virtual void setValues(int shape[4][4], int index, int rotation, int x, int y) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				Tetrimino::shape[i][j] = shape[i][j];
		Tetrimino::index = index;
		Tetrimino::rotation = rotation;
		Tetrimino::x = x;
		Tetrimino::y = y;
	}
	bool IsControllable() { return controllable; }
	void Fall(int board[20][10]) {
		ResetTetrimino(board);
		y++;
		if (CheckBounds(board) || Checkintersection(board))
		{
			y--;
			controllable = 0;
		}
	}
	virtual void Rotate() {}
	int GetX() { return x; }
	int GetY() { return y; }

	bool Checkintersection(int board[][10])
	{
		for (int i = y; i < y + 4 && i < 20; i++)
			for (int j = x; j < x + 4 && j < 10; j++)
				if (board[i][j] == 1 && shape[i - y][j - x] == 1)
					return true;
		return false;
	}
	bool CheckBounds(int board[][10])//Returns true if tetrimino is currently out of bounds
	{
		for (int i = y; i < y + 4; i++)
			for (int j = x; j < x + 4; j++)
				if ((i >= 20 || i < 0 || j >= 10 || j < 0) && shape[i - y][j - x] == 1)
					return true;
		return false;
	}
	void MoveX(bool i)
	{
		if (i)
			x--;
		else
			x++;
	}
	void ShiftX(bool i, int board[][10]) {
		if (controllable)
		{
			ResetTetrimino(board);
			MoveX(i);
			if (Checkintersection(board) || CheckBounds(board))
				MoveX(!i);
			SetTetrimino(board);
		}
	}
	void SetTetrimino(int board[20][10]) {
		for (int i = y; i < y + 4; i++)
			for (int j = x; j < x + 4; j++) {
				if (i < 20 && j < 10 && shape[i - y][j - x] != 0)
					board[i][j] = shape[i - y][j - x];
			}
	}
	void ResetTetrimino(int board[20][10]) {
		for (int i = y; i < y + 4; i++)
			for (int j = x; j < x + 4; j++) {
				if (i < 20 && j < 10 && shape[i - y][j - x] != 0)
					board[i][j] = 0;
			}
	}
};

class Ishape :public Tetrimino {
public:
	Ishape() {
		int shape[4][4] = {
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		};
		setValues(shape, 0, 0, 4, 0);
	}
};