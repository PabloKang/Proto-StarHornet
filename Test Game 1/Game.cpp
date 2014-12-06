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
	playerShip = new Ship(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	return true;
}


int Game::exec()
{
	const int TICKS_PER_SECOND = 25;
	const int SKIP_TICKS = 500 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

	int loops;
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
			update();
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

	return 0;
}


void Game::update()
{
	// Process events
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
	}

	// Update game objects
	playerShip->update(window);

	for (std::vector<Projectile>::iterator pit = bullets.begin(); pit != bullets.end(); ++pit)
	{

	}
}


void Game::draw(float interpolation)
{
	// Draw things here and display the window
	playerShip->draw(window);

}

