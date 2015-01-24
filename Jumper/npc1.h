#pragma once

#include "base_npc.h"

class Npc1 : public base_npc
{
public:
	Npc1(Speech* speech, Map* map, float x, float y) : base_npc(speech, map, x, y)
	{
		this->text = "Help me take these guys down!";
	}
};