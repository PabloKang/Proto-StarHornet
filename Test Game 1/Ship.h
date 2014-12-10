#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
#include "Projectile.h"

class Ship :
	public Entity
{
public:
	// Property Variables
	sf::Sprite turret;
	sf::Texture trrtTxtr;
	sf::Texture thrustTxtr;

	sf::Clock shipClock;
	sf::Int32 lastShot;

	// Status Variables
	int shield;
	int health;
	int maxShield = 100;
	int maxHealth = 100;
	float boost;
	float boostMax = 100;
	float boostSpeed;
	float turretAngle = 0.0;
	bool firedShot = false;
	float shotSpeed = 30.0f;
	int shotDelay = 150;

	bool frntThrusting = false;
	bool rearThrusting = false;

	// Animations
	Animation rearThrust_anim;
	Animation frntThrust_anim;

	// AnimatedSprites
	AnimatedSprite rearThrust_sprite;
	AnimatedSprite frntThrust_sprite;

	// Constructors
	Ship();
	Ship(sf::Vector2f position);
	~Ship();

	// Primary Functions
	void control();
	void update(sf::RenderWindow& win, sf::View& view, Entities& entities, sf::Time frameTime);
	void draw(sf::RenderWindow& win);
	void Ship::moveSprite(float dx, float dy);

	// Gets & Sets
	sf::Sprite& getTurret();

private:

};

#endif // Ship_H