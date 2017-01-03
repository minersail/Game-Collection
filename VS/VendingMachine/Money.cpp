#include "stdafx.h"
#include "Money.h"
#include "Game.h"

Money::Money(std::string filename, int val)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	hovered = false;
	value = val;
}

Money::~Money()
{
}

void Money::Update(float deltaTime, sf::Event ev)
{
	sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
	sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);
	if (GetBoundingRect().contains(mouseCoords.x, mouseCoords.y)) // If hovered over
	{
		hovered = true;
		if (ev.type == sf::Event::MouseButtonReleased)
		{
			Game::balance += value;
		}
	}
	else
	{
		hovered = false;
	}
}

void Money::Draw(sf::RenderWindow& rw)
{
	if (hovered)
	{
		_sprite.setColor(sf::Color(200, 200, 200));
	}
	else
	{
		_sprite.setColor(sf::Color(255, 255, 255));
	}
	rw.draw(_sprite);
}