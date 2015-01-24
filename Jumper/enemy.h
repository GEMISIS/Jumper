#pragma once

#include "entity.h"
#include "map.h"

class enemy : public Entity
{
public:
	enemy(Map* map, float x, float y);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
protected:
	Map* map;
	int health;
private:
	sf::Vector2f position;
};

