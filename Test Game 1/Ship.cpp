#include "Ship.h"

const int spriteSize = 128;
const float rotationRatio = (57.5 / 128.f);


Ship::Ship()
{
	Ship(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f));
}

Ship::Ship(sf::Vector2f position)
{
	// Initialize Textures
	if (setSpriteTexture(sprite, texture, "Sprites/hornet_body_small.gif") && setSpriteTexture(turret, trrtTxtr, "Sprites/hornet_turret_small.gif")) {
		sprite.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));
		turret.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));
		
		// Set frames for rear thruster animation
		setAnimationTexture(rearThrust_anim, thrustTxtr, "Sprites/hornet_thrust_spritesheet.gif");
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 0, spriteSize * 0, spriteSize, spriteSize));
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 1, spriteSize * 0, spriteSize, spriteSize));
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 2, spriteSize * 0, spriteSize, spriteSize));
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 3, spriteSize * 0, spriteSize, spriteSize));
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 4, spriteSize * 0, spriteSize, spriteSize));
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 5, spriteSize * 0, spriteSize, spriteSize));
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 6, spriteSize * 0, spriteSize, spriteSize));
		rearThrust_anim.addFrame(sf::IntRect(spriteSize * 7, spriteSize * 0, spriteSize, spriteSize));

		// Set frames for front thruster animation
		setAnimationTexture(frntThrust_anim, thrustTxtr, "Sprites/hornet_thrust_spritesheet.gif");
		frntThrust_anim.addFrame(sf::IntRect(spriteSize * 0, spriteSize * 0, spriteSize, spriteSize));
		frntThrust_anim.addFrame(sf::IntRect(spriteSize * 0, spriteSize * 1, spriteSize, spriteSize));
		frntThrust_anim.addFrame(sf::IntRect(spriteSize * 1, spriteSize * 1, spriteSize, spriteSize));
		frntThrust_anim.addFrame(sf::IntRect(spriteSize * 2, spriteSize * 1, spriteSize, spriteSize));
		frntThrust_anim.addFrame(sf::IntRect(spriteSize * 3, spriteSize * 1, spriteSize, spriteSize));

		// Set up rearThrust_sprite
		rearThrust_sprite = AnimatedSprite(sf::seconds(0.2f), true, false);
		rearThrust_sprite.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));

		// Set up frntThrust_sprite
		frntThrust_sprite = AnimatedSprite(sf::seconds(0.2f), true, false);
		frntThrust_sprite.setOrigin(sf::Vector2f(spriteSize * rotationRatio, spriteSize / 2));

		// Set positions
		sprite.setPosition(position);
		turret.setPosition(position);
		rearThrust_sprite.setPosition(position);
		frntThrust_sprite.setPosition(position);

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


void Ship::control()
{
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
}


void Ship::update(sf::RenderWindow& win, sf::View& view, Entities& entities, sf::Time frameTime)
{
	// Get movement input
	control();

	// Turret Firing Mechanism
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !firedShot) {
		Projectile* b = new Projectile("Sprites/turret_bullet.gif", sprite.getPosition(), this->shotSpeed, turret.getRotation());
		entities.playerBullets.push_back(b);
		lastShot = shipClock.getElapsedTime().asMilliseconds();
		firedShot = true;
	}
	else if (firedShot && shipClock.getElapsedTime().asMilliseconds() - lastShot >= shotDelay) { firedShot = false; }

	// Turret Control
	sf::Vector2f curPos = turret.getPosition();
	sf::Vector2i pixel_pos = sf::Mouse::getPosition(win);
	sf::Vector2f coord_pos = win.mapPixelToCoords(pixel_pos);
	float dx = curPos.x - coord_pos.x;
	float dy = curPos.y - coord_pos.y;
	turretAngle = (atan2(dy, dx)) * 180 / PI;

	// Movement variables
	float angleRad = PI * (angle / 180);
	float move_x = speed * cos(angleRad);
	float move_y = speed * sin(angleRad);
	float strafeRad = PI * ((angle - 90) / 180);
	float strafe_x = boostSpeed * cos(strafeRad);
	float strafe_y = boostSpeed * sin(strafeRad);

	// Move all sprites
	moveSprite(move_x, move_y);
	moveSprite(strafe_x, strafe_y);

	// Keep view centered on player's ship
	view.move(move_x, move_y);
	view.move(strafe_x, strafe_y);

	// SHIP ANIMATION UPDATE:
	// Fire rear thruster
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (speed > -1.5) { rearThrust_sprite.setFrame(1, true); }
		else if (speed > -2.5) { rearThrust_sprite.setFrame(2, true); }
		else if (speed > -3.5) { rearThrust_sprite.setFrame(3, true); }
		else if (speed > -4.5) { rearThrust_sprite.setFrame(4, true); }
		else if (speed > -5.5) { rearThrust_sprite.setFrame(5, true); }
		else if (speed > -6.5) { rearThrust_sprite.setFrame(6, true); }
		else if (speed > -7.5) { rearThrust_sprite.setFrame(7, true); }
		rearThrusting = true;
	}
	// Stop firing rear thruster
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !rearThrusting) { rearThrust_sprite.setFrame(0, true); }
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && rearThrusting) {
		rearThrust_sprite.setFrame(4, true);
		rearThrusting = false;
	}

	// Fire front thrusters
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !frntThrusting) { 
		frntThrust_sprite.setFrame(1, true); 
		frntThrusting = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && frntThrusting) { frntThrust_sprite.setFrame(2, true); }
	// Stop firing front thrusters
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && frntThrusting) {
		frntThrust_sprite.setFrame(3, true);
		frntThrusting = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !frntThrusting) { frntThrust_sprite.setFrame(0, true); }
}


void Ship::draw(sf::RenderWindow& win)
{
	// Play animations
	frntThrust_sprite.play(frntThrust_anim);
	rearThrust_sprite.play(rearThrust_anim);

	// Draw sprites
	win.draw(rearThrust_sprite);
	win.draw(sprite);
	win.draw(frntThrust_sprite);
	win.draw(turret);
}


void Ship::moveSprite(float dx, float dy)
{
	sprite.move(dx, dy);
	sprite.setRotation(angle);

	turret.move(dx, dy);
	turret.setRotation(turretAngle);

	rearThrust_sprite.move(dx, dy);
	rearThrust_sprite.setRotation(angle);

	frntThrust_sprite.move(dx, dy);
	frntThrust_sprite.setRotation(angle);
}


sf::Sprite& Ship::getTurret()
{
	return turret;
}