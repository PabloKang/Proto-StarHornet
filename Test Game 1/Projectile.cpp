#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(std::string filePath, sf::Vector2f position, float velocity, float trajectory)
{
	speed = velocity;
	angle = trajectory + 180;
	scale = sf::Vector2f(1, 1);
	angleRad = PI * (angle / 180);
	setSpriteTexture(sprite, texture, filePath);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setPosition(position);

}

Projectile::~Projectile()
{
}


void Projectile::update()
{
	float move_x = speed * cos(angleRad);
	float move_y = speed * sin(angleRad);

	moveSprite(sprite, move_x, move_y, angle);
}
