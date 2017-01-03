#include "stdafx.h"
#include "Button.h"
#include "Game.h"

Button::Button(float width, float height, std::string filename, bool tiled)
{
	Load(filename, tiled);
	assert(IsLoaded());
	texturefile = filename;

	SetBoxSize(width, height);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	currentState = Blank;
}

Button::Button(float width, float height, std::string filename, std::string message, bool tiled)
{
	Load(filename, tiled);
	assert(IsLoaded());
	texturefile = filename;

	SetBoxSize(width, height, tiled);
	SetMessage(message);
	SetColor(sf::Color(40, 0, 0));
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	currentState = Message;
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	if (currentState == Circle)
	{
	}
	else if (currentState == X)
	{
	}
	else if (currentState == Message)
	{
		text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
		text.setPosition(GetPosition().x, GetPosition().y);
		rw.draw(text);
	}
}

void Button::Update(float deltaTime, sf::Event ev)
{
	if (Clicked(ev) && currentState == Blank)
	{
		
	}
}

bool Button::Clicked(sf::Event ev)
{
	if (ev.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
		sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);
		if (GetBoundingRect().contains(mouseCoords.x, mouseCoords.y))
		{
			return true;
		}
	}
	return false;
}

void Button::SetActive(bool makeActive)
{
	if (makeActive)
		_sprite.setColor(sf::Color(255, 255, 255));
	else
		_sprite.setColor(sf::Color(128, 128, 128));
}