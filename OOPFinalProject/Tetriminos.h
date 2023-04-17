#include<iostream>
#include<SFML/Graphics.hpp>
class Tetrimino
{
protected:
	int shape[4][4][4];
	int rotation;
	int x, y;
	bool controllable;
public:
	Tetrimino() :x(0), y(0), rotation(0), controllable(1)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					shape[i][j][k] = 0;
	}
	int GetX() { return x; }
	int GetY() { return y; }
	bool IsControllable() { return controllable; }
	virtual void setValues(int shape[][4][4], int rotation, int x, int y) {
		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					Tetrimino::shape[k][i][j] = shape[k][i][j];
		Tetrimino::rotation = rotation;
		Tetrimino::x = x;
		Tetrimino::y = y;
	}
	void Fall(int board[20][10]) {
		y++;
		if (CheckBounds(board) || Checkintersection(board))
		{
			y--;
			controllable = 0;
		}
	}
	void Rotate(int board[20][10]) {
		bool flag = 0;
		int oldx = x;
		rotation++;
		rotation = rotation % 4;
		if (Checkintersection(board) || CheckBounds(board)) {
			for (; x > oldx - 4 && flag == 0; --x) {
				if (Checkintersection(board) || CheckBounds(board));
				else {
					flag = 1;
					++x;
				}
			}
			if (!flag) {
				x += 4;
				for (; x < oldx + 4 && flag == 0; ++x) {
					if (Checkintersection(board) || CheckBounds(board));
					else {
						flag = 1;
						--x;
					}
				}
			}
			if (!flag) {
				rotation--;
				rotation = rotation % 4;
			}
		}
	}
	bool Checkintersection(int board[][10]) //Returns true if tetrimino is intersecting. False if not intersecting
	{
		for (int i = y; i < y + 4 && i < 20; i++)
			for (int j = x; j < x + 4 && j < 10; j++)
				if (i < 20 || i >= 0 || j < 10 || j >= 0)
					if (board[i][j] != 0 && shape[rotation][i - y][j - x] != 0)
						return true;
		return false;
	}
	bool CheckBounds(int board[][10])//Returns true if tetrimino is currently out of bounds
	{
		for (int i = y; i < y + 4; i++)
			for (int j = x; j < x + 4; j++)
				if ((i >= 20 || i < 0 || j >= 10 || j < 0) && shape[rotation][i - y][j - x] != 0)
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
			MoveX(i);
			if (Checkintersection(board) || CheckBounds(board))
				MoveX(!i);
		}
	}
	void SetTetrimino(int board[20][10]) {
		for (int i = y; i < y + 4; i++)
			for (int j = x; j < x + 4; j++) {
				if (i < 20 && j < 10 && shape[rotation][i - y][j - x] != 0)
					board[i][j] = shape[rotation][i - y][j - x];
			}
	}
	void ResetTetrimino(int board[20][10]) {
		for (int i = y; i < y + 4; i++)
			for (int j = x; j < x + 4; j++) {
				if (i < 20 && j < 10 && shape[rotation][i - y][j - x] != 0)
					board[i][j] = 0;
			}
	}
};

class Ishape :public Tetrimino {
public:
	Ishape() {
		int shape[4][4][4] = { {
			  {0,1,0,0},
			  {0,1,0,0},
			  {0,1,0,0},
			  {0,1,0,0}},
			{ {1,1,1,1},
			  {0,0,0,0},
			  {0,0,0,0},
			  {0,0,0,0}  },
			{ {0,1,0,0},
			  {0,1,0,0},
			  {0,1,0,0},
			  {0,1,0,0}  },
			{ {1,1,1,1},
			  {0,0,0,0},
			  {0,0,0,0},
			  {0,0,0,0}  },
		};
		setValues(shape, 0, 4, 0);
	}
};
class Jshape :public Tetrimino {
public:
	Jshape() {
		int shape[4][4][4] = { {
			  {0,2,0,0},
			  {0,2,0,0},
			  {2,2,0,0},
			  {0,0,0,0}},
			{ {0,2,0,0},
			  {0,2,2,2},
			  {0,0,0,0},
			  {0,0,0,0}  },
			{ {0,2,2,0},
			  {0,2,0,0},
			  {0,2,0,0},
			  {0,0,0,0}  },
			{ {2,2,2,0},
			  {0,0,2,0},
			  {0,0,0,0},
			  {0,0,0,0}  },
		};
		setValues(shape, 0, 4, 0);
	}
};
class Lshape :public Tetrimino {
public:
	Lshape() {
		int shape[4][4][4] = { {
			  {0,3,0,0},
			  {0,3,0,0},
			  {0,3,3,0},
			  {0,0,0,0}},
			{ {0,3,3,3},
			  {0,3,0,0},
			  {0,0,0,0},
			  {0,0,0,0}  },
			{ {3,3,0,0},
			  {0,3,0,0},
			  {0,3,0,0},
			  {0,0,0,0}  },
			{ {0,0,3,0},
			  {3,3,3,0},
			  {0,0,0,0},
			  {0,0,0,0}  },
		};
		setValues(shape, 0, 4, 0);
	}
};
class Oshape :public Tetrimino {
public:
	Oshape() {
		int shape[4][4][4] = { {
			  {0,0,0,0},
			  {0,4,4,0},
			  {0,4,4,0},
			  {0,0,0,0}},
			{ {0,0,0,0},
			  {0,4,4,0},
			  {0,4,4,0},
			  {0,0,0,0}  },
			{ {0,0,0,0},
			  {0,4,4,0},
			  {0,4,4,0},
			  {0,0,0,0}  },
			{ {0,0,0,0},
			  {0,4,4,0},
			  {0,4,4,0},
			  {0,0,0,0}  },
		};
		setValues(shape, 0, 4, 0);
	}
};
class Sshape :public Tetrimino {
public:
	Sshape() {
		int shape[4][4][4] = { {
			  {0,5,5,0},
			  {5,5,0,0},
			  {0,0,0,0},
			  {0,0,0,0}},
			{ {5,0,0,0},
			  {5,5,0,0},
			  {0,5,0,0},
			  {0,0,0,0}  },
			{ {0,0,0,0},
			  {0,5,5,0},
			  {5,5,0,0},
			  {0,0,0,0}  },
			{ {5,0,0,0},
			  {5,5,0,0},
			  {0,5,0,0},
			  {0,0,0,0}  },
		};
		setValues(shape, 0, 4, 0);
	}
};
class Tshape :public Tetrimino {
public:
	Tshape() {
		int shape[4][4][4] = { {
			  {6,6,6,0},
			  {0,6,0,0},
			  {0,0,0,0},
			  {0,0,0,0}},
			{ {0,6,0,0},
			  {6,6,0,0},
			  {0,6,0,0},
			  {0,0,0,0}  },
			{ {0,0,0,0},
			  {0,6,0,0},
			  {6,6,6,0},
			  {0,0,0,0}  },
			{ {6,0,0,0},
			  {6,6,0,0},
			  {6,0,0,0},
			  {0,0,0,0}  },
		};
		setValues(shape, 0, 4, 0);
	}
};
class Zshape :public Tetrimino {
public:
	Zshape() {
		int shape[4][4][4] = { {
			  {7,7,0,0},
			  {0,7,7,0},
			  {0,0,0,0},
			  {0,0,0,0}},
			{ {0,7,0,0},
			  {7,7,0,0},
			  {7,0,0,0},
			  {0,0,0,0}  },
			{ {0,0,0,0},
			  {0,7,7,0},
			  {0,0,7,7},
			  {0,0,0,0}  },
			{ {0,0,0,0},
			  {0,0,7,0},
			  {0,7,7,0},
			  {0,7,0,0}  },
		};
		setValues(shape, 0, 4, 0);
	}
};