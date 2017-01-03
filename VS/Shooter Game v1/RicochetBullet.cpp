#include "stdafx.h"
#include "RicochetBullet.h"
#include "Game.h"
#include "Block.h"

RicochetBullet::RicochetBullet(std::string filename, float angleI, int speed, Faction fac, float damage)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 2);
	angle = angleI;
	velocity = speed;
	faction = fac;
	projectileDamage = damage;
	totalDist = 0;
	bounceCount = 0;
	wallLoc = sf::Vector2f(0, 0);
}

RicochetBullet::~RicochetBullet()
{
}

void RicochetBullet::Update(float deltaTime, sf::Event ev)
{
	SetPosition(GetPosition().x + velocity * cos(angle), GetPosition().y + velocity * sin(angle));
	totalDist += sqrt(pow(velocity * cos(angle), 2) + pow(velocity * sin(angle), 2));

	DamageEntities(projectileDamage);

	if (GetPosition().y < -800)
	{
		pendingDestruction = true;
	}
}

void RicochetBullet::DamageEntities(float damage)
{
	float PI = 3.141592f;
	std::vector<Entity*>::iterator iterE = Game::EntityList.begin();
	while (iterE != Game::EntityList.end())
	{
		// Perform initial bounding rect test and make sure they are not in the same faction
		if (faction != (*iterE)->faction && GetBoundingRect().intersects((*iterE)->GetBoundingRect()))
		{
			if (CheckForCollision(*iterE)) // More specific collision
			{
				Block* test = dynamic_cast<Block*>(*iterE);
				if (test != NULL)
				{
					hitWall = true;
					wallLoc = test->GetPosition();
					wallSize = sf::Vector2f(test->GetWidth(), test->GetHeight());

					if (bounceCount < 3)
					{
						bounceCount++;
						if (GetPosition().x > wallLoc.x + wallSize.x / 2 - 5) // Bullet hit right part of wall
						{
							angle = PI - angle;
						}
						else if (GetPosition().x < wallLoc.x - wallSize.x / 2 + 5) // Bullet hit left part of wall
						{
							angle = PI - angle;
						}
						if (GetPosition().y > wallLoc.y + wallSize.y / 2 - 5) // Bullet hit bottom part of wall
						{
							angle = PI * 2 - angle;
						}
						else if (GetPosition().y < wallLoc.y - wallSize.y / 2 + 5) // Bullet hit top part of wall
						{
							angle = PI * 2 - angle;
						}
						SetRotation(angle / PI * 180);
						return; // If you hit a wall don't trigger pendingDestruction or Damage();
					}
				}

				(*iterE)->Damage(damage);
				pendingDestruction = true;
				break; // Only one thing damaged at a time;
			}
		}
		iterE++;
	}
}