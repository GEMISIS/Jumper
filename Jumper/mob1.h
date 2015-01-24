#pragma once

#include "enemy.h"

class Mob1 : public enemy
{
public:
	Mob1(Map* map, float x, float y) : enemy(map, x, y)
	{
	}
};