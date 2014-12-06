#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(std::string filePath, sf::Vector2f position, float velocity, float trajectory)
{
	speed = velocity;
	angle = trajectory;
	scale = sf::Vector2f(1, 1);
	angleRad = PI * (angle / 180);
	setTexture(sprite, texture, filePath);
	sprite.setPosition(position);
}

Projectile::~Projectile()
{
}


void Projectile::update()
{
	double move_x = speed * cos(angleRad);
	double move_y = speed * sin(angleRad);

	moveSprite(sprite, move_x, move_y, angle);
}
