#include "stdafx.h"
#include "Wallet.h"
#include "Game.h"

Wallet::Wallet()
	: quarter("images/quarter.png", 25), dollar("images/dollar.png", 100), fivedollar("images/fivedollar.png", 500),
	dime("images/dime.png", 10), nickel("images/nickel.png", 5), penny("images/penny.png", 1), tendollar("images/tendollar.png", 1000)
{
	Load("images/wallet1.png");
	assert(IsLoaded());
	texturefile = "images/wallet1.png";

	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	openTexture.loadFromFile("images/wallet2.png");
	open.setTexture(openTexture);
	open.setOrigin(open.getLocalBounds().width / 2, open.getLocalBounds().height / 2);

	isOpen = false;
}

Wallet::~Wallet()
{
}

void Wallet::Update(float deltaTime, sf::Event ev)
{
	open.setPosition(GetPosition().x - GetTextureRect().width / 2, GetPosition().y);

	if (ev.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
		sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);
		if (GetBoundingRect().contains(mouseCoords.x, mouseCoords.y)) // If clicked
		{
			isOpen = isOpen ? false : true;
		}
	}

	if (isOpen == true)
	{
		quarter.SetPosition(GetPosition().x - 80, GetPosition().y + 20);
		dime.SetPosition(GetPosition().x - 100, GetPosition().y + 20);
		nickel.SetPosition(GetPosition().x - 120, GetPosition().y + 20);
		penny.SetPosition(GetPosition().x - 140, GetPosition().y + 20);
		dollar.SetPosition(GetPosition().x - 105, GetPosition().y - 3);
		fivedollar.SetPosition(GetPosition().x - 105, GetPosition().y - 15);
		tendollar.SetPosition(GetPosition().x - 105, GetPosition().y - 27);

		quarter.Update(deltaTime, ev);
		dime.Update(deltaTime, ev);
		nickel.Update(deltaTime, ev);
		penny.Update(deltaTime, ev);
		dollar.Update(deltaTime, ev);
		fivedollar.Update(deltaTime, ev);
		tendollar.Update(deltaTime, ev);
	}
}

void Wallet::Draw(sf::RenderWindow& rw)
{
	if (isOpen == true)
	{
		rw.draw(open);
		quarter.Draw(rw);
		dime.Draw(rw);
		nickel.Draw(rw);
		penny.Draw(rw);
		dollar.Draw(rw);
		fivedollar.Draw(rw);
		tendollar.Draw(rw);
	}
	else
	{
		rw.draw(_sprite);
	}
}