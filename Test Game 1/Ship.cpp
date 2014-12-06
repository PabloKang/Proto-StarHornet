#include "Ship.h"



Ship::Ship()
{
	// Initialize Textures
	if (setTexture(sprite, texture, "Sprites/hornet_body_small.gif") && setTexture(turret, trrtTxtr, "Sprites/hornet_turret_small.gif")) {
		sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width * (223 / 500.f), sprite.getLocalBounds().height / 2));
		turret.setOrigin(sf::Vector2f(turret.getLocalBounds().width * (223 / 500.f), turret.getLocalBounds().height / 2));
		
		speed = 0;
		angle = 0;
		scale = sf::Vector2f(1, 1);
		
		sprite.setPosition(sf::Vector2f(0, 0));
		turret.setPosition(sf::Vector2f(0, 0));
	}
}

Ship::Ship(sf::Vector2f position)
{
	// Initialize Textures
	if (setTexture(sprite, texture, "Sprites/hornet_body_small.gif") && setTexture(turret, trrtTxtr, "Sprites/hornet_turret_small.gif")) {
		sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width * (223 / 500.f), sprite.getLocalBounds().height / 2));
		turret.setOrigin(sf::Vector2f(turret.getLocalBounds().width * (223 / 500.f), turret.getLocalBounds().height / 2));
		
		speed = 0;
		angle = 0;
		scale = sf::Vector2f(1, 1);

		sprite.setPosition(position);
		turret.setPosition(position);
	}
}

Ship::~Ship()
{
}


void Ship::control(sf::RenderWindow& win)
{
	// Firing Mechanism
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))  firedShot = true;

	// Hull Control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && speed > -5) { speed = speed - 0.2; }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && speed < 0) { speed = speed + 0.02; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && speed < 3) { speed = speed + 0.2; }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && speed > 0) { speed = speed - 0.02; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { angle = angle - 2; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { angle = angle + 2; }

	// Turret Control
	sf::Vector2f curPos = turret.getPosition();
	sf::Vector2i position = sf::Mouse::getPosition(win);
	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;
	turretAngle = (atan2(dy, dx)) * 180 / PI;
}


void Ship::update(sf::RenderWindow& win)
{
	control(win);

	float angleRad = PI * (angle / 180);
	double move_x = speed * cos(angleRad);
	double move_y = speed * sin(angleRad);

	moveSprite(sprite, move_x, move_y, angle);
	moveSprite(turret, move_x, move_y, turretAngle);
}


void Ship::draw(sf::RenderWindow& win)
{
	win.draw(sprite);
	win.draw(turret);
}


sf::Sprite& Ship::getTurret()
{
	return turret;
}