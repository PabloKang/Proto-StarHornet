#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"

class Ship :
	public Entity
{
public:
	// Property Variables
	sf::Sprite turret;
	sf::Texture trrtTxtr;

	// Status Variables
	int shield;
	int health;
	int maxShield = 100;
	int maxHealth = 100;
	bool firedShot = false;
	float turretAngle = 0.0;

	// Constructors
	Ship();
	Ship(sf::Vector2f position);
	~Ship();

	// Primary Functions
	void control(sf::RenderWindow& win);
	void update(sf::RenderWindow& win);
	void draw(sf::RenderWindow& win);

	// Gets & Sets
	sf::Sprite& getTurret();

private:

};

#endif // Ship_H