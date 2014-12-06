#pragma once

#include "Entity.h"

class Projectile :
	public Entity
{
public:	
	// Status Variables
	int lifespan;
	float angleRad;

	// Constructors
	Projectile();
	Projectile(std::string filePath, sf::Vector2f position, float velocity, float trajectory);
	~Projectile();

	// Primary Functions
	void update();
	void draw(sf::RenderWindow& win);
};

