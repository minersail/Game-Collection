#include "stdafx.h"
#include "RayCast.h"
#include "Game.h"

RayCast::RayCast(sf::Vector2i size, sf::Vector2f loc, float angleI, float dist)
{
	Load("images/bullet.png");
	_sprite.setTextureRect(sf::Rect<int>(0, 0, size.x, size.y)); // This will create a sprite with no image but still collision
	_sprite.setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 2);

	angle = angleI;
	testDist = dist;
	SetPosition(loc);
	velocity = 15;
	totalDist = 0;
}

RayCast::~RayCast()
{
}

float RayCast::Cast(Entity& obstruction, Faction testFac)
{
	while (totalDist < testDist) // Ray cast works by checking points in a straight line in intervals. Total dist is the endpoint of that line.
	{
		SetPosition(GetPosition().x + velocity * cos(angle), GetPosition().y + velocity * sin(angle));
		totalDist += sqrt(pow(velocity * cos(angle), 2) + pow(velocity * sin(angle), 2));

		std::vector<Entity*>::iterator iterE = Game::EntityList.begin();
		while (iterE != Game::EntityList.end())
		{
			if ((*iterE)->faction == testFac && GetBoundingRect().intersects((*iterE)->GetBoundingRect())) // Perform initial bounding rect test; Only test against entities with faction testFac
			{
				obstruction = **iterE;
				return totalDist;
			}
			iterE++;
		}
	}
	
	return 0; // Can also be interpreted as false
}

float RayCast::Cast(Entity& obstruction, Faction testFac1, Faction testFac2)
{
	while (totalDist < testDist)
	{
		SetPosition(GetPosition().x + velocity * cos(angle), GetPosition().y + velocity * sin(angle));
		totalDist += sqrt(pow(velocity * cos(angle), 2) + pow(velocity * sin(angle), 2));

		std::vector<Entity*>::iterator iterE = Game::EntityList.begin();
		while (iterE != Game::EntityList.end())
		{
			if (((*iterE)->faction == testFac1 || (*iterE)->faction == testFac2) && GetBoundingRect().intersects((*iterE)->GetBoundingRect())) // Perform initial bounding rect test;
			{																																   // Tests against the two given testFacs
				obstruction = **iterE;
				return totalDist;
			}
			iterE++;
		}
	}
	return 0; // Can also be interpreted as false
}