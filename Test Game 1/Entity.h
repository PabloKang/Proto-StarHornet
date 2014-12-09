#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"

class Projectile;

struct Entities {
	std::vector<Projectile*> playerBullets;
	std::vector<Projectile*> enemyBullets;
};


class Entity
{
public:
	// Property Variables
	sf::Sprite sprite;
	sf::Texture texture;

	// Status Variables
	float speed;
	float angle;
	sf::Vector2f scale;

	// Constructors
	Entity();
	Entity(std::string filePath, sf::Vector2f position);
	virtual ~Entity();

	// Primary Functions
	void update();
	void draw(sf::RenderWindow& win);
	void moveSprite(sf::Sprite& sprite, float move_x, float move_y, float angle);

	// Gets & Sets
	bool setTexture(sf::Texture& texture, std::string filePath);
	bool setSpriteTexture(sf::Sprite& sprite, sf::Texture& texture, std::string filePath);
	bool setAnimationTexture(Animation& anim, sf::Texture& texture, std::string filePath);
	sf::Sprite& getSprite();
};

#endif // ENTITY_H