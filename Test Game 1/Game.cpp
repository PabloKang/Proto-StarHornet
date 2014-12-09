#include "Game.h"


Game::Game(sf::RenderWindow& win) : window(win)
{
}

Game::~Game()
{
}


bool Game::init()
{
	// Initialize Player
	playerShip = new Ship(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	return true;
}


int Game::exec()
{
	const int TICKS_PER_SECOND = 25;
	const int SKIP_TICKS = 500 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

	int loops;
	bool pause = false;
	float interpolation;

	sf::Clock clock;
	sf::Int32 next_tick = clock.getElapsedTime().asMilliseconds();

	// Create the window
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);


	// MAIN GAME LOOP :-------------------------------------------------------------------------------
	while (window.isOpen()) {
		loops = 0;

		// Update the window
		while (clock.getElapsedTime().asMilliseconds() > next_tick && loops < MAX_FRAMESKIP) {
			update(clock);
			next_tick += SKIP_TICKS;
			++loops;
		}

		// Calculate the interpolation
		interpolation = static_cast <float> (clock.getElapsedTime().asMilliseconds() + SKIP_TICKS - next_tick) / static_cast <float> (SKIP_TICKS);

		// Clear the window
		window.clear();

		// Draw with interpolation
		draw(interpolation);

		// Display the window
		window.display();
	}

	// Cleanup
	for (int i = 0; i < entities.playerBullets.size(); i++) { delete entities.playerBullets[i]; }
	for (int i = 0; i < entities.enemyBullets.size(); i++) { delete entities.enemyBullets[i]; }
	delete playerShip;

	return 0;
}


void Game::update(sf::Clock clock)
{
	// Process events
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
	}

	sf::Time frameTime = clock.restart();

	// Update game objects
	playerShip->update(window, entities, frameTime);

	for (std::vector<Projectile*>::iterator pit = entities.playerBullets.begin(); pit != entities.playerBullets.end(); ++pit)
	{
		(*pit)->update();
	}
}


void Game::draw(float interpolation)
{
	// Draw things here and display the window
	playerShip->draw(window);

	for (std::vector<Projectile*>::iterator pit = entities.playerBullets.begin(); pit != entities.playerBullets.end(); ++pit)
	{
		(*pit)->draw(window);
	}
}

