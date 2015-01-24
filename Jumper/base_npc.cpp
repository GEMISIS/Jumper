#include "main_game.h"
#include "base_npc.h"

base_npc::base_npc(Speech* speech, Map* map, float x, float y)
{
	this->Load("ship.png");
	this->setPosition(x, y);
	this->setColor(sf::Color::Cyan);
	this->map = map;
	this->groupId = 3;
	this->speech = speech;
}

bool base_npc::Update(sf::RenderWindow* window)
{
	Entity::Update(window);
	return true;
}

void base_npc::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 2:
		speech->SetText(this->text);
		entity->Destroy();
		break;
	}
}

