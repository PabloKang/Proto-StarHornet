#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"

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
	void moveSprite(sf::Sprite& sprite, double move_x, double move_y, float angle);

	// Gets & Sets
	bool setTexture(sf::Sprite& sprite, sf::Texture& texture, std::string filePath);
	sf::Sprite& getSprite();
};

#endif // ENTITY_H