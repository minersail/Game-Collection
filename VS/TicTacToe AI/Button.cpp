#include "stdafx.h"
#include "Button.h"
#include "Game.h"

Button::Button(float width, float height)
	:circle(40), x1(sf::Vector2f(30, 150)), x2(sf::Vector2f(30, 150))
{
	Load("images/button.png");
	assert(IsLoaded());
	texturefile = "images/button.png";

	SetBoxSize(width, height);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	circle.setOrigin(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2);
	x1.setOrigin(x1.getLocalBounds().width / 2, x1.getLocalBounds().height / 2);
	x2.setOrigin(x2.getLocalBounds().width / 2, x2.getLocalBounds().height / 2);
	
	x1.rotate(45);
	x2.rotate(-45);

	currentState = Blank;
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	if (currentState == Circle)
	{
		circle.setPosition(GetPosition());
		circle.setOutlineColor(sf::Color::Blue);
		circle.setFillColor(sf::Color(239, 228, 176));
		circle.setOutlineThickness(25);
		rw.draw(circle);
	}
	else if (currentState == X)
	{
		x1.setPosition(GetPosition());
		x2.setPosition(GetPosition());

		x1.setFillColor(sf::Color::Red);
		x2.setFillColor(sf::Color::Red);

		rw.draw(x1);
		rw.draw(x2);
	}
	else if (currentState == Message)
	{
		text.setPosition(GetPosition().x - 100, GetPosition().y - 25);
		rw.draw(text);
	}
}

void Button::Update(float deltaTime, sf::Event ev)
{
	if (Clicked(ev) && currentState == Blank)
	{
		currentState = Circle;
		Game::turns += 1;
		
		if (!Game::CheckForWin())
			Game::_gameState = Game::AITurn;
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