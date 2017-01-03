#include "stdafx.h"
#include "UseObject.h"
#include "Game.h"

UseObject::UseObject(float initX, float initY, std::string textureID, std::string name, UsePoint point)
	: Entity(initX, initY, textureID, name)
{
	activationLocs.push_back(point);
}

UseObject::UseObject(float initX, float initY, std::string textureID, std::string name, std::vector<UsePoint> points)
	: Entity(initX, initY, textureID, name)
{
	activationLocs = points;
}

UseObject::UseObject(float initX, float initY, std::string textureID, std::string name, sf::IntRect hitbox)
	: Entity(initX, initY, textureID, name, hitbox)
{
}

UseObject::~UseObject()
{
}

bool UseObject::CheckUsePoints(sf::Event ev)
{
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
	{
		float pX = Game::GetPlayer()->GetPosition().x; // HitBox's origin
		float pY = Game::GetPlayer()->GetPosition().y;

		std::vector<UsePoint>::iterator it = activationLocs.begin();
		while (it != activationLocs.end())
		{
			sf::RectangleShape unit;
			unit.setSize(sf::Vector2f(16, 16));
			unit.setPosition(it->x * 16, it->y * 16 - 8); // Adjust UsePoints by half a unit

			// Debug for UsePoints--KEEP
			/*unit.setFillColor(sf::Color::Red);
			Game::GetWindow().draw(unit);
			Game::GetWindow().display();*/

			if (unit.getGlobalBounds().contains(pX, pY))
			{
				sf::IntRect joeRect = Game::GetPlayer()->GetTextureRect();
				if (joeRect.left == joeRect.width * 0 && it->dir == Up)
					return true;
				if (joeRect.left == joeRect.width * 1 && it->dir == Right)
					return true;
				if (joeRect.left == joeRect.width * 2 && it->dir == Down)
					return true;
				if (joeRect.left == joeRect.width * 3 && it->dir == Left)
					return true;
			}

			it++;
		}
	}
	return false;
}

std::vector<UseObject::UsePoint>& UseObject::GetActivationLocations()
{
	return activationLocs;
}