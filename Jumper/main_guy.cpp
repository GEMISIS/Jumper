#include "main_game.h"
#include "main_guy.h"
#include "bullet.h"
#include "player_bullet.h"

main_guy::main_guy(sf::RenderWindow* window, EntityManager* entityManager, Map* map, float x, float y)
{
	this->Load("ship.png");
	this->setPosition(x, y);
	this->map = map;
	this->speed = 2.0f;
	this->jump = 0;
	this->run = 0;
	this->groupId = 1;
	this->entityManager = entityManager;
	Entity::scroll = sf::Vector2f(0, 0);

	while (this->getPosition().x + this->getGlobalBounds().width + 512 > window->getSize().x && Entity::scroll.x < this->map->getGlobalBounds().width - window->getSize().x)
	{
		this->map->move(-abs(this->speed), 0);
		this->move(-abs(this->speed), 0);
		Entity::scroll.x += abs(this->speed);
	}
	while (this->getPosition().x - 512 < 0 && Entity::scroll.x > 0)
	{
		this->map->move(abs(this->speed), 0);
		this->move(abs(this->speed), 0);
		Entity::scroll.x -= abs(this->speed);
	}
	while (this->getPosition().y + this->getGlobalBounds().height + 256 > window->getSize().y && Entity::scroll.y < this->map->getGlobalBounds().height - window->getSize().y)
	{
		this->map->move(0, -abs(this->speed));
		this->move(0, -abs(this->speed));
		Entity::scroll.y += abs(this->speed);
	}
	while (this->getPosition().y - 256 < 0 && Entity::scroll.y > 0)
	{
		this->map->move(0, abs(this->speed));
		this->move(0, abs(this->speed));
		Entity::scroll.y -= abs(this->speed);
	}
}

bool main_guy::Update(sf::RenderWindow* window)
{
	this->velocity.x = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) * this->speed;

	if (this->velocity.y < 3.0f)
	{
		this->velocity.y += 0.1f;
	}

	if (this->map->CheckCollision(this, LEFT) == 1)
	{
		this->move(-abs(this->speed), 0);
	}
	if (this->map->CheckCollision(this, RIGHT) == 1)
	{
		this->move(abs(this->speed), 0);
	}
	if (this->map->CheckCollision(this, UP) == 1)
	{
		this->move(0, abs(this->speed));
		this->velocity.y = 0.0f;
	}
	if (this->map->CheckCollision(this, DOWN) == 1 || this->map->CheckCollision(this, DOWN) == 4)
	{
		this->velocity.y = 0.0f;
		this->jump = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->jump == 0)
	{
		this->velocity.y = -3.0f;
		this->jump = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->jump == 1 && this->velocity.y > -5.0f)
	{
		this->velocity.y -= 0.25f;
	}
	else if (this->velocity.y <= -5.0f)
	{
		this->jump = 2;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) && (this->run == 0 && this->speed < 4.0f))
	{
		this->speed += 0.01f;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) && (this->run == 0 && this->speed >= 4.0f))
	{
		this->run = 1;
	}
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) && this->speed > 2.0f)
	{
		this->speed -= 0.02f;
		this->run = 0;
	}

	if (this->velocity.x > 0)
	{
		this->direction = 0.0f;
	}
	else if (this->velocity.x < 0)
	{
		this->direction = 180.0f;
	}

	if (this->getPosition().x + this->getGlobalBounds().width + 512 > window->getSize().x && Entity::scroll.x < this->map->getGlobalBounds().width - window->getSize().x)
	{
		this->map->move(-abs(this->speed), 0);
		this->move(-abs(this->speed), 0);
		Entity::scroll.x += abs(this->speed);
	}
	if (this->getPosition().x - 512 < 0 && Entity::scroll.x > 0)
	{
		this->map->move(abs(this->speed), 0);
		this->move(abs(this->speed), 0);
		Entity::scroll.x -= abs(this->speed);
	}
	if (this->getPosition().y + this->getGlobalBounds().height + 256 > window->getSize().y && Entity::scroll.y < this->map->getGlobalBounds().height - window->getSize().y)
	{
		this->map->move(0, -abs(this->speed + this->velocity.y));
		this->move(0, -abs(this->speed + this->velocity.y));
		Entity::scroll.y += abs(this->speed + this->velocity.y);
	}
	if (this->getPosition().y - 256 < 0 && Entity::scroll.y > 0)
	{
		this->map->move(0, abs(this->speed));
		this->move(0, abs(this->speed));
		Entity::scroll.y -= abs(this->speed);
	}

	if (this->getPosition().x <= 0)
	{
		saveSystem.currentMap = map->leftArea;
		saveSystem.x = window->getSize().x - this->getGlobalBounds().width - 32;
		saveSystem.y = this->getPosition().y;
		coreState.SetState(new main_game());
		return false;
	}
	if (this->getPosition().x + this->getGlobalBounds().width >= window->getSize().x)
	{
		saveSystem.currentMap = map->rightArea;
		saveSystem.x = 32;
		saveSystem.y = this->getPosition().y;
		coreState.SetState(new main_game());
		return false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !this->spaceKey)
	{
		this->entityManager->Add("bullet", new Bullet(this->map, this->getPosition().x, this->getPosition().y, direction, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && !this->xKey)
	{
		this->entityManager->Add("pBullet", new PlayerBullet(this->map, this->getPosition().x, this->getPosition().y, direction, 800));
	}

	switch (this->map->CheckCollision(this, NONE))
	{
	case 0:
		break;
	case 1:
		this->speed = 1.0f;
		this->setColor(sf::Color::White);
		break;
	case 2:
		this->speed = 0.5f;
		this->setColor(sf::Color::Blue);
		break;
	}

	this->spaceKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
	this->xKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X);

	Entity::Update(window);
	return true;
}

void main_guy::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 3:
		this->move(-this->velocity.x, -this->velocity.y);
		this->velocity.y = 0.0f;
		this->jump = 0;
		break;
	}
}

