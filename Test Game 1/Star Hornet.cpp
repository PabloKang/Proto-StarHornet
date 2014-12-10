#include "stdafx.h"
#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Star Hornet"/*, sf::Style::Fullscreen */);
	Game game(window);
	
	if (!game.init()) { return EXIT_FAILURE; }

	return game.exec();
}
