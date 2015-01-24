#pragma once

#include "base_npc.h"

class Npc2 : public base_npc
{
public:
	Npc2(Speech* speech, Map* map, float x, float y) : base_npc(speech, map, x, y)
	{
		this->text = "Welcome to the game!";
		this->setColor(sf::Color::Magenta);
	}
};