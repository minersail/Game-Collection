#include "stdafx.h"
#include "Button.h"
#include "Game.h"

Button::Button(float width, float height, std::string filename)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	SetBoxSize(width, height);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	currentState = Blank;

	Player1.setOrigin(Player1.getLocalBounds().width / 2, Player1.getLocalBounds().height / 2);
	Player2.setOrigin(Player2.getLocalBounds().width / 2, Player2.getLocalBounds().height / 2);
}

Button::Button(float width, float height, std::string filename, std::string message)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	SetBoxSize(width, height);
	SetMessage(message);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	currentState = Message;

	Player1.setOrigin(Player1.getLocalBounds().width / 2, Player1.getLocalBounds().height / 2);
	Player2.setOrigin(Player2.getLocalBounds().width / 2, Player2.getLocalBounds().height / 2);
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	if (currentState == Circle)
	{
		Player1.setPosition(GetPosition());
		rw.draw(Player1);
	}
	else if (currentState == X)
	{
		Player2.setPosition(GetPosition());
		rw.draw(Player2);
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
		if (Game::singleplayer)
		{
			currentState = Circle;
			Game::turns += 1;
		
			if (!Game::CheckForWin())
				Game::_gameState = Game::AITurn;
		}
		else 
		{
			if (Game::player == 1)
			{
				currentState = Circle;
				Game::player = 2;
				Game::turns += 1;
			}
			else if (Game::player == 2)
			{
				currentState = X;
				Game::player = 1;
				Game::turns += 1;
			}
			Game::CheckForWin();
		}
	}
	Player1.setTexture(Game::text1);
	Player2.setTexture(Game::text2);
	Player1.setOrigin(Player1.getLocalBounds().width / 2, Player1.getLocalBounds().height / 2);
	Player2.setOrigin(Player2.getLocalBounds().width / 2, Player2.getLocalBounds().height / 2);
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