#pragma once

#include<iostream>
#include"Well.h"
#include<SFML/Graphics.hpp>
class Tetrimino
{
protected:
	int** shape; //Dynamic 2d Array used to store the actual shape of the tetromino
	int rows, columns; //integers used to store the rows and columns of the dynamic array
	int x, y; //The actual positions of the tetromino relative to the board, 0,0 at top left.
	int index;//The value of the blocks of the tetromino, 1 for the first, 3 for the second etc. Used to check for the pivot block
	bool controllable,abouttoset;
	sf::Sprite Tile,TileOutline;
	sf::Texture Tiletexture, TileOutlineTexture;
public:
	Tetrimino() :x(0), y(0), controllable(1), rows(0), columns(0)
	{};
	~Tetrimino();
	int GetX() { return x; }
	int GetY() { return y; }
	void SetControllable(bool i) { controllable = i; }
	bool IsControllable() { return controllable; }
	void Fall(Well&well);
	virtual void Rotate(Well&well);
	void RotateUnbounded();
	bool Checkintersection(Well&well); 
	bool CheckBounds(Well&well);
	void MoveX(bool i);
	void ShiftX(bool i, Well&well);
	void SetTetrimino(Well&well);
	void DrawTetrimino(sf::RenderWindow*& window);
	void DrawTetriminoatCoordinates(sf::RenderWindow*& window, float xcoord, float ycoord);
};

class Ishape :public Tetrimino {

public:
	Ishape() {
		abouttoset = 0;
		controllable = 1;
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 2+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading I shape tile";
		}
		char tilepath2[27] = "./Textures/TileOutline.png";
		if (!TileOutlineTexture.loadFromFile(tilepath2)) {
			std::cout << "Error loading Tile Outline";
		}
		Tile=sf::Sprite(Tiletexture);
		TileOutline = sf::Sprite(TileOutlineTexture);
		x = 4;
		y = 0;
		rows = 4;
		columns = 1;
		shape = new int* [rows];
		index = 1;
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[4][1] = {
			{1},
			{2},
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
		abouttoset = 0;
		controllable = 1;
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 3+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading J shape tile";
		}
		char tilepath2[27] = "./Textures/TileOutline.png";
		if (!TileOutlineTexture.loadFromFile(tilepath2)) {
			std::cout << "Error loading Tile Outline";
		}
		Tile = sf::Sprite(Tiletexture);
		TileOutline = sf::Sprite(TileOutlineTexture);
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 3;
		columns = 2;
		index = 3;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[3][2] = {
			{0,3},
			{0,4},
			{3,3},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}

};
class Lshape :public Tetrimino {
public:
	Lshape() {
		abouttoset = 0;
		controllable = 1;
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 4+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading L shape tile";
		}
		char tilepath2[27] = "./Textures/TileOutline.png";
		if (!TileOutlineTexture.loadFromFile(tilepath2)) {
			std::cout << "Error loading Tile Outline";
		}
		Tile = sf::Sprite(Tiletexture);
		TileOutline = sf::Sprite(TileOutlineTexture);
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 3;
		columns = 2;
		index = 5;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[3][2] = {
			{5,0},
			{6,0},
			{5,5},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};
class Oshape :public Tetrimino {
public:
	Oshape() {
		abouttoset = 0;
		controllable = 1;
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 5+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading O shape tile";
		}
		char tilepath2[27] = "./Textures/TileOutline.png";
		if (!TileOutlineTexture.loadFromFile(tilepath2)) {
			std::cout << "Error loading Tile Outline";
		}
		Tile = sf::Sprite(Tiletexture);
		TileOutline = sf::Sprite(TileOutlineTexture);
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 2;
		index = 7;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][2] = {
			{7,7},
			{7,7},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}

	void Rotate(int**board) {

	}
};
class Sshape :public Tetrimino {
public:
	Sshape() {
		abouttoset = 0;
		controllable = 1;
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 6+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading S shape tile";
		}
		char tilepath2[27] = "./Textures/TileOutline.png";
		if (!TileOutlineTexture.loadFromFile(tilepath2)) {
			std::cout << "Error loading Tile Outline";
		}
		Tile = sf::Sprite(Tiletexture);
		TileOutline = sf::Sprite(TileOutlineTexture);
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 3;
		index = 9;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][3] = {
			{0,9 ,9},
			{9,10,0},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};
class Tshape :public Tetrimino {
public:
	Tshape() {
		abouttoset = 0;
		controllable = 1;
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 7+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading T shape tile";
		}
		char tilepath2[27] = "./Textures/TileOutline.png";
		if (!TileOutlineTexture.loadFromFile(tilepath2)) {
			std::cout << "Error loading Tile Outline";
		}
		Tile = sf::Sprite(Tiletexture);
		TileOutline = sf::Sprite(TileOutlineTexture);
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 3;
		index = 11;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][3] = {
			{0,11,0},
			{11,12,11},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};
class Zshape :public Tetrimino {
public:
	Zshape() {
		abouttoset = 0;
		controllable = 1;
		char tilepath[21] = "./Textures/Tile1.png";
		tilepath[15] = 8+48;
		if (!Tiletexture.loadFromFile(tilepath)) {
			std::cout << "Error loading Z shape tile";
		}
		char tilepath2[27] = "./Textures/TileOutline.png";
		if (!TileOutlineTexture.loadFromFile(tilepath2)) {
			std::cout << "Error loading Tile Outline";
		}
		Tile = sf::Sprite(Tiletexture);
		TileOutline = sf::Sprite(TileOutlineTexture);
		Tile = sf::Sprite(Tiletexture);
		x = 4;
		y = 0;
		rows = 2;
		columns = 3;
		index = 13;
		shape = new int* [rows];
		for (int i = 0; i < rows; i++)
			shape[i] = new int[columns];
		int shape2[2][3] = {
			{13,13,0},
			{0,14,13},
		};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				shape[i][j] = shape2[i][j];
	}
};
