#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "entity_manager.h"
#include "speech.h"

typedef enum
{
	NONE = -1,
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	TOP_LEFT = 4,
	TOP_RIGHT = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_RIGHT = 7
}Direction;

class Map
{
public:
	Map(EntityManager* entityManager);

	void Load(std::string filename, std::string backgroundFile, Speech* speech);

	virtual void Update(sf::RenderWindow* window);

	int CheckCollision(Entity* entity, Direction direction);

	void Render(sf::RenderWindow* window);

	void move(float x, float y);
	void move(sf::Vector2f amount);

	sf::FloatRect getGlobalBounds();

	std::string topArea, bottomArea, leftArea, rightArea;

	~Map();
protected:
	std::string tileSet;
	int width = 0;
	int height = 0;
	int tileWidth = 0;
	int tileHeight = 0;
	int* data;
private:
	sf::Texture* texture;
	sf::Texture* backgroundTexture;
	sf::Image* tileSetTexture;
	EntityManager* entityManager;
	sf::Sprite* tiles;
	sf::Sprite* background;
};

