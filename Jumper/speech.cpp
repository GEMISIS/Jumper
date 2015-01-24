#include "speech.h"

Speech::Speech(sf::Font &font, unsigned int size, sf::RenderWindow* window) : sf::Text("", font, size)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile("Graphics/dialog_box.png");
	this->setTexture(*this->texture);
	sf::Sprite::setPosition(0, window->getSize().y - sf::Text::getGlobalBounds().height);
	sf::Text::setPosition(5.0f, window->getSize().y - sf::Text::getGlobalBounds().height);
	this->window = window;
	this->speaking = false;
}

void Speech::SetText(std::string text)
{
	this->speaking = true;
	this->setString(text);
	float scaleWidth = sf::Text::getGlobalBounds().width / sf::Sprite::getTextureRect().width + 0.2f;
	float scaleHeight = sf::Text::getGlobalBounds().height / sf::Sprite::getTextureRect().height + 0.2f;

	sf::Sprite::setScale(scaleWidth, scaleHeight);

	sf::Sprite::setPosition(this->window->getSize().x / 2 - sf::Text::getGlobalBounds().width / 2, this->window->getSize().y - sf::Text::getGlobalBounds().height - 64);
	sf::Text::setPosition(this->window->getSize().x / 2 - sf::Text::getGlobalBounds().width / 2 + 5.0f, this->window->getSize().y - sf::Text::getGlobalBounds().height - 64);
}

void Speech::Render()
{
	if (this->speaking)
	{
		this->window->draw((sf::Sprite)*this);
		this->window->draw((sf::Text)*this);
	}
}