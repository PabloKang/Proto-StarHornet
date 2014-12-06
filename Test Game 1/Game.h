#include "stdafx.h"
#include "AssetHeader.h"

class Game
{
public:
	sf::RenderWindow& window;

	// Game State Data
	sf::Event event;
	Ship* playerShip;
	std::vector<Projectile> bullets;

	// Game Constructors
	Game(sf::RenderWindow& win);
	~Game();

	// Game Functions
	bool	init();
	int		exec();
	void	update();
	void	draw(float interpolation);
};

