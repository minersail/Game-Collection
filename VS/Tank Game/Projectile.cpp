#include "stdafx.h"
#include "Projectile.h"
#include "Game.h"
#include "Block.h"
#include "Tank.h"

Projectile::Projectile()
{
	Load("images/error.png");

	angle = 0;
	velocity = 0;
	totalDist = 0;
}

Projectile::Projectile(std::string filename, float angleI, int speed, Faction fac)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	angle = angleI;
	velocity = speed;
	faction = fac;
	totalDist = 0;
}

Projectile::~Projectile()
{
}

void Projectile::Update(float deltaTime, sf::Event ev)
{
	SetPosition(GetPosition().x + velocity * cos(angle), GetPosition().y + velocity * sin(angle));
	totalDist += sqrt(pow(velocity * cos(angle), 2) + pow(velocity * sin(angle), 2));

	std::vector<Entity*>::iterator iterE = Game::EntityList.begin();
	while (iterE != Game::EntityList.end())
	{	
		// Perform initial bounding rect test and make sure they are not in the same faction
		if (faction != (*iterE)->faction && GetBoundingRect().intersects((*iterE)->GetBoundingRect())) 
		{
			if (CheckForCollision(*iterE)) // More specific collision
			{
				(*iterE)->Damage(5);
				pendingDestruction = true;
				break; // Only one thing damaged at a time;
			}
		}
		iterE++;
	}

	if (GetPosition().x < -100 || GetPosition().x > 2400 || GetPosition().y < -100 || GetPosition().y > 2400)
	{
		pendingDestruction = true;
	}
	if (totalDist > 600)
	{
		pendingDestruction = true;
	}
}