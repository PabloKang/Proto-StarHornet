#include "Ship.h"

const int spriteSize = 128;
const float rotationRatio = (57.5 / 128.f);


Ship::Ship()
{
	// Initialize Textures
	if (setSpriteTexture(sprite, texture, "Sprites/hornet_body_small.gif") && setSpriteTexture(turret, trrtTxtr, "Sprites/hornet_turret_small.gif")) {
		sprite.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));
		turret.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));
		
		setAnimationTexture(thrust_MainFW, thrustTxtr, "Sprites/hornet_thrust_spritesheet.gif");
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 0, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 1, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 2, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 3, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 4, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 5, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 6, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 7, spriteSize * 0, spriteSize, spriteSize));

		currentThrust = &thrust_MainFW;

		// Set up AnimatedSprite
		thrustSprite = AnimatedSprite(sf::seconds(0.2f), true, false);
		
		// Set positions
		thrustSprite.setPosition(sf::Vector2f(0, 0));
		turret.setPosition(sf::Vector2f(0, 0));
		sprite.setPosition(sf::Vector2f(0, 0));

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
	}
}

Ship::Ship(sf::Vector2f position)
{
	// Initialize Textures
	if (setSpriteTexture(sprite, texture, "Sprites/hornet_body_small.gif") && setSpriteTexture(turret, trrtTxtr, "Sprites/hornet_turret_small.gif")) {
		sprite.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));
		turret.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));
		
		setAnimationTexture(thrust_MainFW, thrustTxtr, "Sprites/hornet_thrust_spritesheet.gif");
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 0, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 1, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 2, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 3, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 4, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 5, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 6, spriteSize * 0, spriteSize, spriteSize));
		thrust_MainFW.addFrame(sf::IntRect(spriteSize * 7, spriteSize * 0, spriteSize, spriteSize));

		currentThrust = &thrust_MainFW;

		// Set up thrustSprite
		thrustSprite = AnimatedSprite(sf::seconds(0.2f), true, false);
		thrustSprite.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));

		// Set positions
		thrustSprite.setPosition(position);
		turret.setPosition(position);
		sprite.setPosition(position);
		
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
	}
}

Ship::~Ship()
{
}


void Ship::control(sf::RenderWindow& win, Entities& entities)
{
	// Turret Firing Mechanism
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !firedShot) {
		Projectile* b = new Projectile("Sprites/turret_bullet.gif", sprite.getPosition(), shotSpeed, turret.getRotation());
		entities.playerBullets.push_back(b);
		lastShot = shipClock.getElapsedTime().asMilliseconds();
		firedShot = true;
	}
	else if (firedShot && shipClock.getElapsedTime().asMilliseconds() - lastShot >= shotDelay) { firedShot = false; }

	// Forward and Reverse
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && speed > -7) { speed = speed - 0.2f; }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && speed < 0) { speed = speed + 0.05f; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && speed < 3) { speed = speed + 0.2f; }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && speed > 0) { speed = speed - 0.05f; }
	if (speed <= 0.1 && speed >= -0.1) speed = 0;

	// Rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { angle = angle - 2; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { angle = angle + 2; }

	// Strafe Boost
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && boost >= 50 && boostSpeed > -8) {
		boostSpeed = boostSpeed - 8; 
		boost -= 55;
	}
	else if (boostSpeed < 0) { boostSpeed = boostSpeed + 0.25f; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && boost >= 50 && boostSpeed < 8) {
		boostSpeed = boostSpeed + 8; 
		boost -= 55;
	}
	else if (boostSpeed > 0) { boostSpeed = boostSpeed - 0.25f; }
	if (boost < boostMax) boost += 0.2f;

	// Turret Control
	sf::Vector2f curPos = turret.getPosition();
	sf::Vector2i position = sf::Mouse::getPosition(win);
	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;
	turretAngle = (atan2(dy, dx)) * 180 / PI;
}


void Ship::update(sf::RenderWindow& win, Entities& entities, sf::Time frameTime)
{
	control(win, entities);

	float angleRad = PI * (angle / 180);
	float move_x = speed * cos(angleRad);
	float move_y = speed * sin(angleRad);

	float strafeRad = PI * ((angle - 90) / 180);
	float strafe_x = boostSpeed * cos(strafeRad);
	float strafe_y = boostSpeed * sin(strafeRad);

	// Thrust level ifs
	if (speed > -0.5) { thrustSprite.setFrame(0, true); }
	else if (speed > -1.5) { thrustSprite.setFrame(1, true); }
	else if (speed > -2.5) { thrustSprite.setFrame(2, true); }
	else if (speed > -3.5) { thrustSprite.setFrame(3, true); }
	else if (speed > -4.5) { thrustSprite.setFrame(4, true); }
	else if (speed > -5.5) { thrustSprite.setFrame(5, true); }
	else if (speed > -6.5) { thrustSprite.setFrame(6, true); }
	else if (speed > -7.5) { thrustSprite.setFrame(7, true); }
	
	moveSprite(move_x, move_y);
	moveSprite(strafe_x, strafe_y);
}


void Ship::draw(sf::RenderWindow& win)
{
	thrustSprite.play(*currentThrust);
	win.draw(thrustSprite);
	win.draw(sprite);
	win.draw(turret);
}


void Ship::moveSprite(float dx, float dy)
{
	thrustSprite.move(dx, dy);
	thrustSprite.setRotation(angle);

	sprite.move(dx, dy);
	sprite.setRotation(angle);

	turret.move(dx, dy);
	turret.setRotation(turretAngle);
}


sf::Sprite& Ship::getTurret()
{
	return turret;
}