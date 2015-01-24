#pragma once

#include "entity.h"
#include "map.h"

extern SaveSystem saveSystem;

class main_guy : public Entity
{
public:
	main_guy(sf::RenderWindow* window, EntityManager* entityManager, Map* map, float x, float y);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
private:
	Map* map;
	float speed;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	int jump, run;
	float direction;
};

