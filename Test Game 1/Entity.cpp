#include "Entity.h"


Entity::Entity()
{
	speed = 0;
	angle = 0;
	scale = sf::Vector2f(1, 1);
	sprite.setPosition(sf::Vector2f(0, 0));
}

Entity::Entity(std::string filePath, sf::Vector2f position)
{
	speed = 0;
	angle = 0;

	scale = sf::Vector2f(1, 1);
	setTexture(sprite, texture, filePath);
	sprite.setPosition(position);
}

Entity::~Entity()
{
}


void Entity::update()
{
	float angleRad = PI * (angle / 180);
	double move_x = speed * cos(angleRad);
	double move_y = speed * sin(angleRad);

	moveSprite(sprite, move_x, move_y, angle);
}


void Entity::draw(sf::RenderWindow& win)
{
	win.draw(sprite);
}


void Entity::moveSprite(sf::Sprite& sprite, double move_x, double move_y, float angle)
{
	sprite.move(move_x, move_y);
	sprite.setRotation(angle);
}


bool Entity::setTexture(sf::Sprite& sprite, sf::Texture& texture, std::string filePath)
{
	if (!texture.loadFromFile(filePath)) {
		std::cout << "ERROR :: Unable to load texture '" << filePath << "'\n";
		return false;
	}
	texture.setSmooth(true);
	sprite = sf::Sprite(texture);
	sprite.setScale(scale);
	return true;
}


sf::Sprite& Entity::getSprite()
{
	return sprite;
}