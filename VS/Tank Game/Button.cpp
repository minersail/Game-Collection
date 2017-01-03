#include "stdafx.h"
#include "Button.h"
#include "Game.h"

Button::Button(sf::Vector2i loc, float width, float height)
{
	Load("images/button.png");
	assert(IsLoaded());
	texturefile = "images/button.png";

	location = loc;
	SetBoxSize(width, height);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
}

Button::~Button()
{
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