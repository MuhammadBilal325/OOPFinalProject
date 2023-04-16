#include<SFML/Graphics.hpp>
#include"Game.h"
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	srand(time(0));
	Game game;
	//string name;
	//cout << "Enter Player Name: ";
	//cin >> name;
//	game.SetName(name);
	while (game.getWindowState())
	{
		game.Update();
 		game.Render();
	}
}