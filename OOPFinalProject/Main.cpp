#include<SFML/Graphics.hpp>
#include"Game.h"
#include<iostream>
using namespace std;
int main()
{
	srand(time(0));
	Game game;
	while (game.getWindowState())
	{
		game.Update();
 		game.Render();
	}
}