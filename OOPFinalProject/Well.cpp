#include"Well.h"
Well::Well() {
	rows = 20;
	columns = 10;
	board = new int* [rows];
	for (int i = 0; i < rows; i++)
		board[i] = new int[columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			board[i][j] = 0;
	char tiletexturepath[21] = "./Textures/Tile1.png";
	for (int i = 0; i < 8; i++)
	{
		tiletexturepath[15] = i + 1 + 48;
		if (!Tiletextures[i].loadFromFile(tiletexturepath)) {
			std::cout << "Error loading TileTexture..." << std::endl;
		}
		Tiles[i] = sf::Sprite(Tiletextures[i]);
	}

	BoardShape.setPosition(20, 20);
	BoardShape.setSize(sf::Vector2f(36*columns,36*rows));
	BoardShape.setFillColor(sf::Color(255,162,0,255));
}
Well::Well(Well& copy) {
	rows = copy.rows;
	columns = copy.columns;
	board = new int* [rows];
	for (int i = 0; i < rows; i++)
		board[i] = new int[columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			board[i][j] = copy.board[i][j];
	for (int i = 0; i < 8; i++)
	{
		Tiletextures[i] = copy.Tiletextures[i];
		Tiles[i] = sf::Sprite(Tiletextures[i]);
	}
	BoardShape = copy.BoardShape;
}
Well::~Well() {
	for (int i = 0; i < rows; i++)
		delete[]board[i];
	delete[]board;
}


void Well::PrintBoard(sf::RenderWindow*& window)
{
	int tilenum = 0;
	window->draw(BoardShape);
	for (int i = 20, k = 0; i < 20 * 36 && k < rows; i += 36, k++)
		for (int j = 20, l = 0; j < 20 * 36 && l < columns; j += 36, l++)
		{
			if (board[k][l] % 2 == 0)
				tilenum = (board[k][l] / 2);
			else
				tilenum = ((board[k][l] - 1) / 2) + 1;
			Tiles[tilenum].setPosition(j, i);
			window->draw(Tiles[tilenum]);
		}
}

void Well::CheckForLines(int& score, int& totalscore)
{
	bool continuos = 1;
	for (int i = 0; i < rows; i++)
	{
		continuos = 1;
		for (int j = 0; j < columns; j++)
			if (board[i][j] == 0)
				continuos = 0;
		if (continuos)
		{
			for (int j = 0; j < columns; j++)
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
		for (int j = 0; j < columns; j++)
			swap(board[i][j], board[i - 1][j]);
}