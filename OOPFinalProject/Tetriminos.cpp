
#include"Tetriminos.h"
 
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
void Tetrimino::Fall(Well&well)
{
	y++;
	if (Checkintersection(well) || CheckBounds(well))
	{
		y--;
		controllable = 0;
	}
	else {
		y++;
		if (Checkintersection(well) || CheckBounds(well)) {
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
void Tetrimino::Rotate(Well&well)
{
	int pivotxorig = 0, pivotyorig = 0, origx = x, origy = y;
	//Look for the x and y of the pivot block and store it
	//Also store original x and y before the rotation
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			if (shape[i][j] == index + 1) {
				pivotyorig = i;
				pivotxorig = j;
			}
		}
	//Perform the rotation
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
	//Move the piece so that the pivotx and pivoty and on the same place as before
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (newarr[i][j] == index + 1) {
				y += pivotyorig - i;
				x += pivotxorig - j;
			}
	//Store the unrotated version of the piece as well to reverse it later in case of collisison
	int** temp = shape;
	shape = newarr;
	int pokingout = 0;
	bool intersect = 0;
	bool keep = 0;
	//Check if newly rotated piece is intersecting, if it is we undo rotation
	if (Checkintersection(well) || CheckBounds(well)) {
		for (int j = x; j < x + columns; j++)
		{
			if ((well.GetBoard()[y][j] != 0 && intersect == 0) || j >= 10)
				intersect = 1;
			if (intersect)
				pokingout++;
		}
		x -= pokingout;
		if (Checkintersection(well) || CheckBounds(well)) {
			x += pokingout;
			x++;
			if (Checkintersection(well) || CheckBounds(well)) {
				//Undo move
				x = origx;
				y = origy;
				shape = temp;
				swap(rows, columns);
				for (int i = 0; i < columns; i++)
					delete[]newarr[i];
				delete[]newarr;
			}
			else
				keep = 1;
		}
		else
			keep = 1;
	}
	else
		keep = 1;
	if(keep) {
		//Keep move
		for (int i = 0; i < columns; i++)
			delete[]temp[i];
		delete[]temp;
	}
}
void Tetrimino::RotateUnbounded()
{
	int pivotxorig = 0, pivotyorig = 0, origx = x, origy = y;
	//Look for the x and y of the pivot block and store it
	//Also store original x and y before the rotation
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			if (shape[i][j] == index + 1) {
				pivotyorig = i;
				pivotxorig = j;
			}
		}
	//Perform the rotation
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
	//Move the piece so that the pivotx and pivoty and on the same place as before
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (newarr[i][j] == index + 1) {
				y += pivotyorig - i;
				x += pivotxorig - j;
			}
	for (int i = 0; i < columns; i++)
		delete[]shape[i];
	delete[]shape;
	shape = newarr;
}
//Returns true if tetrimino is intersecting. False if not intersecting
bool Tetrimino::Checkintersection(Well&well)
{
	for (int i = y; i < y + rows && i < well.GetRows(); i++)
		for (int j = x; j < x + columns && j <well.GetColumns(); j++)
			if (i < 20 || i >= 0 || j < 10 || j >= 0)
				if (well.GetBoard()[i][j] != 0 && shape[i - y][j - x] != 0)
					return true;
	return false;
}
//Returns true if tetrimino is currently out of bounds
bool Tetrimino::CheckBounds(Well&well)
{
	for (int i = y; i < y + rows; i++)
		for (int j = x; j < x + columns; j++)
			if ((i >= well.GetRows() || i < 0 || j >= well.GetColumns() || j < 0) && shape[i - y][j - x] != 0)
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

void Tetrimino::ShiftX(bool i,Well&well)
{
	if (controllable)
	{
		MoveX(i);
		if (Checkintersection(well) || CheckBounds(well))
			MoveX(!i);
	}
}

void Tetrimino::SetTetrimino(Well&well)
{
	for (int i = y; i < y + rows; i++)
		for (int j = x; j < x + columns; j++) {
			if (i < well.GetRows() && j < well.GetColumns() && shape[i - y][j - x] != 0)
				well.GetBoard()[i][j] = shape[i - y][j - x];
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

void Tetrimino::DrawTetriminoatCoordinates(sf::RenderWindow*& window, float xcoord, float ycoord)
{
	float pivotx = 0.5, pivoty = 0.5;
	for(int i=0;i<rows;i++)
		for(int j=0;j<columns;j++)
			if (shape[i][j] == index + 1) {
				pivotx = j;
				pivoty = i;
			}
	xcoord -= pivotx;
	ycoord -= pivoty;
	for (float i = ycoord; i < ycoord + rows;i++)
		for (float j = xcoord; j < xcoord + columns; j++)
		{
			if (shape[int(i-ycoord)][int(j-xcoord)] != 0) {
				Tile.setPosition(((36 * (j + 1)) - 16), ((36 * (i + 1)) - 16));
				window->draw(Tile);
			}
		}
}

