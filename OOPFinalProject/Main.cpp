#include<SFML/Graphics.hpp>
#include"Game.h"
#include<iostream>
using namespace std;
int main()
{
	Game game;
	while (game.getWindowState())
	{
		game.Update();
 		game.Render();
	}
}