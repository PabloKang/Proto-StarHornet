#include "stdafx.h"
#include "AssetHeader.h"

class Game
{
public:
	sf::RenderWindow& window;

	// Game State Data
	sf::Event event;
	Ship* playerShip;
	Entities entities;

	// Game Constructors
	Game(sf::RenderWindow& win);
	~Game();

	// Game Functions
	bool	init();
	int		exec();
	void	update(sf::Clock clock);
	void	draw(float interpolation);
};

