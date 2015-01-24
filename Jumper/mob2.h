#pragma once

#include "enemy.h"

class Mob2 : public enemy
{
public:
	Mob2(Map* map, float x, float y) : enemy(map, x, y)
	{
		this->health = 3;
		this->setColor(sf::Color::Yellow);
	}
};