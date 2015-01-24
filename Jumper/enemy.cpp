#include "main_game.h"
#include "enemy.h"

enemy::enemy(Map* map, float x, float y)
{
	this->position = sf::Vector2f(x, y);
	this->Load("ship.png");
	this->setPosition(x, y);
	this->setColor(sf::Color::Red);
	this->map = map;
	this->groupId = 5;
	this->health = 1;
}

bool enemy::Update(sf::RenderWindow* window)
{
	this->setPosition(this->position.x - Entity::scroll.x, this->position.y - Entity::scroll.y);
	if (this->health <= 0)
	{
		this->Destroy();
	}
	Entity::Update(window);
	return true;
}

void enemy::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 4:
		entity->Destroy();
		this->health -= 1;
		break;
	}
}

