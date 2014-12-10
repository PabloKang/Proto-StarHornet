#include "Game.h"


float windowWidth = sf::VideoMode::getDesktopMode().width / 2.0f;
float windowHeight = sf::VideoMode::getDesktopMode().height / 2.0f;


Game::Game(sf::RenderWindow& win) : window(win)
{
}

Game::~Game()
{
}


bool Game::init()
{
	view = sf::View(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

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
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			window.close();
	}

	sf::Time frameTime = clock.restart();

	// Update game objects
	playerShip->update(window, view, entities, frameTime);

	for (std::vector<Projectile*>::iterator pit = entities.playerBullets.begin(); pit != entities.playerBullets.end(); ++pit)
	{
		(*pit)->update();
	}
}


void Game::draw(float interpolation)
{
	// Prepare the primary view
	window.setView(view);
	// Draw things here and display the window
	playerShip->draw(window);

	for (std::vector<Projectile*>::iterator pit = entities.playerBullets.begin(); pit != entities.playerBullets.end(); ++pit)
	{
		(*pit)->draw(window);
	}
}


//void Display_Backgrounds()
//{
//
//	sf::Sprite current1;
//	sf::Sprite current2;
//	if (background_x < -2048)
//	{
//		background_x = 0;
//		part_count++;
//	}
//
//
//	background_x -= 0.2f * timescale;
//
//
//	if (starfield3_sprite_count <= 5 && bg_anim_forw == true)
//	{
//		if (frame % (6 * ts_inv) == 0)
//			starfield3_sprite_count++;
//		if (starfield3_sprite_count == 5)
//		{
//			bg_anim_forw = false;
//			starfield3_sprite_count = 4;
//		}
//	}
//	else if (starfield3_sprite_count >= 0 && bg_anim_forw == false)
//	{
//		if (frame % (6 * ts_inv) == 0)
//			starfield3_sprite_count--;
//		if (starfield3_sprite_count == 0)
//			bg_anim_forw = true;
//	}
//
//
//	current1 = starfield1[part_count % 3][starfield3_sprite_count];
//	current2 = starfield1[(part_count + 1) % 3][starfield3_sprite_count];
//	current1.SetPosition(background_x, 0 - (camera.Top * 0.1));
//	current2.SetPosition(background_x + 2048, 0 - (camera.Top * 0.1));
//	App.Draw(current1);
//	App.Draw(current2);
//	star_overlay.SetPosition(background_x * 2, 0 - (camera.Top * 0.2));
//	App.Draw(star_overlay);
//}