#include <iostream>
#include <fstream>
#include <sstream>

#include "map.h"
#include "npc1.h"
#include "npc2.h"
#include "mob1.h"
#include "mob2.h"
#include "enemy.h"

Map::Map(EntityManager* entityManager)
{
	this->texture = new sf::Texture();
	this->tileSetTexture = new sf::Image();
	this->entityManager = entityManager;
}

void Map::Load(std::string filename, Speech* speech)
{
	std::string temp;
	std::ifstream mapFile("Graphics/maps/" + filename);

	std::getline(mapFile, this->tileSet);
	std::getline(mapFile, this->topArea);
	std::getline(mapFile, this->bottomArea);
	std::getline(mapFile, this->leftArea);
	std::getline(mapFile, this->rightArea);

	std::getline(mapFile, temp);
	this->tileWidth = std::stoi(temp, nullptr);
	std::getline(mapFile, temp);
	this->tileHeight = std::stoi(temp, nullptr);

	std::getline(mapFile, temp);
	this->width = std::stoi(temp, nullptr);
	std::getline(mapFile, temp);
	this->height = std::stoi(temp, nullptr);

	this->data = new int[this->width * this->height];
	for (int y = 0; y < this->height; y += 1)
	{
		for (int x = 0; x < this->width; x += 1)
		{
			char temp;
			mapFile >> this->data[x + y * this->width] >> temp;
		}
	}
	mapFile.close();

	this->texture->create(this->width * this->tileWidth, this->height * this->tileHeight);

	this->tileSetTexture->loadFromFile("Graphics/" + this->tileSet);
	sf::Image tile1, tile2, tile3, tile4, tile5;

	tile1.create(64, 64);
	tile2.create(64, 64);
	tile3.create(64, 64);
	tile4.create(64, 64);
	tile5.create(64, 64);

	tile1.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth, this->tileHeight), true);
	tile2.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth, 0, this->tileWidth, this->tileHeight), true);
	tile3.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, this->tileHeight, this->tileWidth, this->tileHeight), true);
	tile4.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth, this->tileHeight, this->tileWidth, this->tileHeight), true);
	tile5.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 2 * this->tileHeight, this->tileWidth, this->tileHeight), true);

	for (int y = 0; y < this->height; y += 1)
	{
		for (int x = 0; x < this->width; x += 1)
		{
			switch (this->data[x + y * this->width])
			{
			case 0:
				break;
			case 1:
				this->texture->update(tile1, x * 64, y * 64);
				break;
			case 2:
				this->texture->update(tile2, x * 64, y * 64);
				break;
			case 3:
				this->texture->update(tile3, x * 64, y * 64);
				break;
			case 4:
				this->texture->update(tile4, x * 64, y * 64);
				break;
			case 5:
				this->texture->update(tile5, x * 64, y * 64);
				break;
			case 6:
				this->texture->update(tile1, x * 64, y * 64);
				this->entityManager->Add("npc1", new Npc1(speech, this, x * 64, y * 64));
				this->data[x + y * this->width] = 1;
				break;
			case 7:
				this->texture->update(tile1, x * 64, y * 64);
				this->entityManager->Add("npc2", new Npc2(speech, this, x * 64, y * 64));
				this->data[x + y * this->width] = 1;
				break;
			case 8:
				this->texture->update(tile1, x * 64, y * 64);
				this->entityManager->Add("mob1", new Mob1(this, x * 64, y * 64));
				this->data[x + y * this->width] = 1;
				break;
			case 9:
				this->texture->update(tile1, x * 64, y * 64);
				this->entityManager->Add("mob2", new Mob2(this, x * 64, y * 64));
				this->data[x + y * this->width] = 1;
				break;
			}
		}
	}

	this->setTexture(*this->texture);
}

void Map::Update(sf::RenderWindow* window)
{
}

int Map::CheckCollision(Entity* entity, Direction direction)
{
	int x = (int)(entity->getPosition().x + entity->getGlobalBounds().width / 2) / this->tileWidth;
	int y = (int)(entity->getPosition().y + entity->getGlobalBounds().height / 2) / this->tileHeight;
	switch (direction)
	{
	case LEFT:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height / 2) / this->tileHeight;
		break;
	case RIGHT:
		x = (int)(entity->getPosition().x) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height / 2) / this->tileHeight;
		break;
	case UP:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width / 2) / this->tileWidth;
		y = (int)(entity->getPosition().y) / this->tileHeight;
		break;
	case DOWN:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width / 2) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height) / this->tileHeight;
		break;
	case TOP_LEFT:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width) / this->tileWidth;
		y = (int)(entity->getPosition().y) / this->tileHeight;
		break;
	case TOP_RIGHT:
		x = (int)(entity->getPosition().x) / this->tileWidth;
		y = (int)(entity->getPosition().y) / this->tileHeight;
		break;
	case BOTTOM_LEFT:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height) / this->tileHeight;
		break;
	case BOTTOM_RIGHT:
		x = (int)(entity->getPosition().x) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height) / this->tileHeight;
		break;
	}
	return this->data[x + y * this->width];
}


Map::~Map()
{
	delete this->texture;
	delete this->tileSetTexture;
	delete this->data;
}