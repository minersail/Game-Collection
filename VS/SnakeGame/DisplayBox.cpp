#include "stdafx.h"
#include "DisplayBox.h"
#include "Game.h"

DisplayBox::DisplayBox()
{
	SetColor(sf::Color(0, 0, 255));
	SetSize(40);
	SetFont(Game::regular);
}

DisplayBox::DisplayBox(sf::Vector2i loc, float width, float height, std::string filename, bool tiled)
{
	Load(filename, tiled);
	assert(IsLoaded());
	texturefile = filename;

	location = loc;
	SetBoxSize(width, height, tiled);
	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	SetColor(sf::Color(0, 0, 255));
	SetSize(40);
	SetFont(Game::regular);
	SetPosition(static_cast<sf::Vector2f>(loc));
}

DisplayBox::DisplayBox(sf::Vector2i loc, float width, float height, std::string filename, std::string message, bool tiled)
{
	Load(filename, tiled);
	assert(IsLoaded());
	texturefile = filename;

	location = loc;
	SetBoxSize(width, height, tiled);
	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	SetColor(sf::Color(0, 0, 255));
	SetSize(40);
	SetFont(Game::regular);
	SetMessage(message);
	SetPosition(static_cast<sf::Vector2f>(loc));
}

DisplayBox::~DisplayBox()
{
}

void DisplayBox::SetBoxSize(float newW, float newH, bool tiled)
{
	if (tiled) // Note: this may only be called if Load() was called with 2nd parameter true
	{
		sf::IntRect newRect(0, 0, newW, newH);
		GetSprite().setTextureRect(newRect);
	}
	else // Scale the box instead of tiling it
	{
		float currW = GetTextureRect().width;
		float currH = GetTextureRect().height;

		float scaleX = newW / currW;
		float scaleY = newH / currH;

		GetSprite().setScale(scaleX, scaleY); 
	}
}

void DisplayBox::Update(float deltaTime, sf::Event ev)
{
}

void DisplayBox::Draw(sf::RenderWindow& rw)
{
	if (IsLoaded())
	{
		sf::Vector2f adjustedPos = Game::GetWindow().mapPixelToCoords(location); // Transfer the world coordinates to screen coordinates
		SetPosition(adjustedPos);

		text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);

		rw.draw(_sprite);
		rw.draw(text);
	}
}

void DisplayBox::SetColor(sf::Color color)
{
	text.setColor(color);
}

void DisplayBox::SetSize(int size)
{
	text.setCharacterSize(size);
}

void DisplayBox::SetMessage(std::string mess)
{
	text.setString(mess);
}

void DisplayBox::SetFont(sf::Font& font)
{
	text.setFont(font);
}

void DisplayBox::SetPosition(float x, float y)
{
	_sprite.setPosition(x, y);
	text.setPosition(x, y);
}

void DisplayBox::SetPosition(sf::Vector2f newPos)
{
	_sprite.setPosition(newPos);
	text.setPosition(newPos);
}

std::string DisplayBox::GetMessage()
{
	return text.getString();
}