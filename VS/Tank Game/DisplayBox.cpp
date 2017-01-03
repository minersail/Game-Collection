#include "stdafx.h"
#include "DisplayBox.h"
#include "Game.h"

DisplayBox::DisplayBox()
{
	SetColor(sf::Color(0, 0, 255));
	SetSize(40);
	SetFont(Game::GetFont("regular"));
}

DisplayBox::DisplayBox(sf::Vector2i loc, float width, float height)
{
	Load("images/displaybox.png");
	assert(IsLoaded());
	texturefile = "images/displaybox.png";

	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	location = loc;
	SetBoxSize(width, height);

	SetColor(sf::Color(0, 0, 255));
	SetSize(40);
	SetFont(Game::GetFont("regular"));
	SetMessage("Sample text");
	SetPosition(static_cast<sf::Vector2f>(loc));
}

DisplayBox::~DisplayBox()
{
}

void DisplayBox::SetBoxSize(float newW, float newH)
{
	float currW = GetTextureRect().width;
	float currH = GetTextureRect().height;

	float scaleX = newW / currW;
	float scaleY = newH / currH;

	GetSprite().scale(scaleX, scaleY);
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