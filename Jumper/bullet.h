#pragma once

#include "entity.h"
#include "map.h"

class Bullet : public Entity
{
public:
	Bullet(Map* map, float x, float y, float direction, float distance);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
private:
	Map* map;
	float distance;
};