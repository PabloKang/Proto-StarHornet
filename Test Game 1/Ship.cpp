#include "Ship.h"



Ship::Ship()
{
	// Initialize Textures
	if (setTexture(sprite, texture, "Sprites/hornet_body_small.gif") && setTexture(turret, trrtTxtr, "Sprites/hornet_turret_small.gif")) {
		sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width * (223 / 500.f), sprite.getLocalBounds().height / 2));
		turret.setOrigin(sf::Vector2f(turret.getLocalBounds().width * (223 / 500.f), turret.getLocalBounds().height / 2));
		
		shield		= 100;
		health		= 100;
		maxShield	= 100;
		maxHealth	= 100;
		boost		= 100;
		boostMax	= 100;
		boostSpeed	= 0;
		speed		= 0;
		boostSpeed	= 0;
		angle		= 0;
		scale		= sf::Vector2f(1, 1);
		
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
		
		shield		= 100;
		health		= 100;
		maxShield	= 100;
		maxHealth	= 100;
		boost		= 100;
		boostMax	= 100;
		boostSpeed	= 0;
		speed		= 0;
		boostSpeed	= 0;
		angle		= 0;
		scale		= sf::Vector2f(1, 1);

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

	// Forward and Reverse
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && speed > -5) { speed = speed - 0.2; }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && speed < 0) { speed = speed + 0.02; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && speed < 3) { speed = speed + 0.2; }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && speed > 0) { speed = speed - 0.02; }

	// Rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { angle = angle - 2; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { angle = angle + 2; }

	// Strafe Boost
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && boost >= 50 && boostSpeed > -8) {
		boostSpeed = boostSpeed - 8; 
		boost -= 55;
	}
	else if (boostSpeed < 0) { boostSpeed = boostSpeed + 0.25; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && boost >= 50 && boostSpeed < 8) {
		boostSpeed = boostSpeed + 8; 
		boost -= 55;
	}
	else if (boostSpeed > 0) { boostSpeed = boostSpeed - 0.25; }
	if (boost < 100) boost += 0.2;

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

	float strafeRad = PI * ((angle - 90) / 180);
	double strafe_x = boostSpeed * cos(strafeRad);
	double strafe_y = boostSpeed * sin(strafeRad);

	moveSprite(move_x, move_y);
	moveSprite(strafe_x, strafe_y);
}


void Ship::draw(sf::RenderWindow& win)
{
	win.draw(sprite);
	win.draw(turret);
}


void Ship::moveSprite(double dx, double dy)
{
	sprite.move(dx, dy);
	sprite.setRotation(angle);

	turret.move(dx, dy);
	turret.setRotation(turretAngle);
}


sf::Sprite& Ship::getTurret()
{
	return turret;
}