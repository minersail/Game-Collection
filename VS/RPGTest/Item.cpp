#include "stdafx.h"
#include "Item.h"
#include "Game.h"

Item::Item(float initX, float initY, std::string textureID, std::string name)
	: VisibleGameObject(initX, initY, textureID, name), inInventory(false), selected(false)
{
}

Item::~Item()
{
}

void Item::Update(float deltaTime, sf::Event ev)
{
	if (!inInventory)
	{
		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
		{
			if (GetBoundingRect().intersects(sf::FloatRect(Game::GetPlayer()->GetBoundingRect())))
			{
				inInventory = true;
				GetSprite().setScale(2, 2);
				Game::GetPlayer()->GetInventory().Add(this);
			}
		}
	}
}

bool Item::CheckForClick(sf::Event ev)
{
	if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (GetBoundingRect().contains(Game::GetMousePos(true)))
		{
			return true;
		}
	}
	return false;
}

void Item::Draw(sf::RenderWindow& rw)
{
	if (!inInventory)
	{
		rw.draw(GetSprite());
	}
}