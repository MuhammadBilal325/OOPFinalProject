#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class Tetrimino
{
protected:
	int** shape;
	int rows, columns;
	int x, y;
	bool controllable;
	sf::Sprite Tile;
	sf::Texture Tiletexture;
public:
	Tetrimino() :x(0), y(0), controllable(1), rows(0), columns(0)
	{}
	~Tetrimino();
	int GetX() { return x; }
	int GetY() { return y; }
	bool IsControllable() { return controllable; }
	void Fall(int **board);
	virtual void Rotate(int **board);
	bool Checkintersection(int **board); 
	bool CheckBounds(int **board);
	void MoveX(bool i);
	void ShiftX(bool i, int **board);
	void SetTetrimino(int **board);
	void ResetTetrimino(int **board);
	void DrawTetrimino(sf::RenderWindow*& window);
};

class Ishape :public Tetrimino {

public:
	Ishape() {
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 2+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading I shape tile";
		}
		Tile=sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 4;
		columns = 1;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[4][1] = {
			{1},
			{1},
			{1},
			{1}
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}

};
class Jshape :public Tetrimino {
public:
	Jshape() {
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 3+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading J shape tile";
		}
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 3;
		columns = 2;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[3][2] = {
			{0,2},
			{0,2},
			{2,2},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}

};
class Lshape :public Tetrimino {
public:
	Lshape() {
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 4+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading L shape tile";
		}
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 3;
		columns = 2;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[3][2] = {
			{3,0},
			{3,0},
			{3,3},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};
class Oshape :public Tetrimino {
public:
	Oshape() {
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 5+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading O shape tile";
		}
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 2;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][2] = {
			{4,4},
			{4,4},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}

	void Rotate(int board[20][10]) {

	}
};
class Sshape :public Tetrimino {
public:
	Sshape() {
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 6+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading S shape tile";
		}
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 3;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][3] = {
			{0,5,5},
			{5,5,0},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};
class Tshape :public Tetrimino {
public:
	Tshape() {
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 7+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading T shape tile";
		}
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 3;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][3] = {
			{6,6,6},
			{0,6,0},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};
class Zshape :public Tetrimino {
public:
	Zshape() {
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 8+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading Z shape tile";
		}
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 3;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][3] = {
			{7,7,0},
			{0,7,7},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};