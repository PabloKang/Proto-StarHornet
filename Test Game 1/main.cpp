#include "stdafx.h"
#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test Game");
	Game game(window);
	
	if (!game.init()) { return EXIT_FAILURE; }

	return game.exec();
}
