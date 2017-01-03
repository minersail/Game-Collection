#include "stdafx.h"
#include "Projectile.h"
#include "Game.h"
#include "Block.h"
#include "Item.h"

Projectile::Projectile()
{
	angle = 0;
	velocity = 0;
	totalDist = 0;
	hitWall = false;
}

Projectile::Projectile(std::string filename, float angleI, int speed, Faction fac, float damage)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 2);
	angle = angleI;
	velocity = speed;
	faction = fac;
	totalDist = 0;
	projectileDamage = damage;
	wallLoc = sf::Vector2f(0, 0);
}

Projectile::~Projectile()
{ 
	// Spawn crack marks on walls
	if (hitWall == true)
	{
		Item* crack = new Item("images/crack.png", 10);
		Game::GetObjectQueue().Add("crack", crack, "back");
		crack->SetPosition(GetPosition());
		crack->GetSprite().setColor(sf::Color(255, 255, 255, 150));

		sf::IntRect rect = crack->GetSprite().getTextureRect();
		if (crack->GetPosition().x > wallLoc.x + wallSize.x / 2 - 5) // Bullet hit right part of wall
		{
			crack->SetTextureRect(0, 0, rect.width / 2, rect.height);
			crack->SetPosition(wallLoc.x + wallSize.x / 2, GetPosition().y);
			rect.width /= 2;
		}
		else if (crack->GetPosition().x < wallLoc.x - wallSize.x / 2 + 5) // Bullet hit left part of wall
		{
			crack->SetTextureRect(rect.width / 2, 0, rect.width / 2, rect.height);
			crack->SetPosition(wallLoc.x - wallSize.x / 2 + rect.width / 2 + 2, GetPosition().y);
			rect.width /= 2;
		}
		if (crack->GetPosition().y > wallLoc.y + wallSize.y / 2 - 5) // Bullet hit bottom part of wall
		{
			crack->SetTextureRect(0, 0, rect.width, rect.width / 2);
			crack->SetPosition(GetPosition().x, wallLoc.y + wallSize.y / 2);
		}
		else if (crack->GetPosition().y < wallLoc.y - wallSize.y / 2 + 5) // Bullet hit top part of wall
		{
			crack->SetTextureRect(0, rect.width / 2, rect.width, rect.height / 2);
			crack->SetPosition(GetPosition().x, wallLoc.y - wallSize.y / 2 + rect.height / 2 + 2);
		}
	}
}

void Projectile::Destroy()
{
	// Spawn crack marks on walls
	if (hitWall == true)
	{
		Item* crack = new Item("images/crack.png", 10);
		Game::GetObjectQueue().Add("crack", crack, "back");
		crack->SetPosition(GetPosition());
		crack->GetSprite().setColor(sf::Color(255, 255, 255, 150));

		sf::IntRect rect = crack->GetSprite().getTextureRect();
		if (crack->GetPosition().x > wallLoc.x + wallSize.x / 2 - 5) // Bullet hit right part of wall
		{
			crack->SetTextureRect(0, 0, rect.width / 2, rect.height);
			crack->SetPosition(wallLoc.x + wallSize.x / 2, GetPosition().y);
			rect.width /= 2;
		}
		else if (crack->GetPosition().x < wallLoc.x - wallSize.x / 2 + 5) // Bullet hit left part of wall
		{
			crack->SetTextureRect(rect.width / 2, 0, rect.width / 2, rect.height);
			crack->SetPosition(wallLoc.x - wallSize.x / 2 + rect.width / 2 + 2, GetPosition().y);
			rect.width /= 2;
		}
		if (crack->GetPosition().y > wallLoc.y + wallSize.y / 2 - 5) // Bullet hit bottom part of wall
		{
			crack->SetTextureRect(0, 0, rect.width, rect.width / 2);
			crack->SetPosition(GetPosition().x, wallLoc.y + wallSize.y / 2);
		}
		else if (crack->GetPosition().y < wallLoc.y - wallSize.y / 2 + 5) // Bullet hit top part of wall
		{
			crack->SetTextureRect(0, rect.width / 2, rect.width, rect.height / 2);
			crack->SetPosition(GetPosition().x, wallLoc.y - wallSize.y / 2 + rect.height / 2 + 2);
		}
	}
}

void Projectile::Update(float deltaTime, sf::Event ev)
{
	SetPosition(GetPosition().x + velocity * cos(angle), GetPosition().y + velocity * sin(angle));
	totalDist += sqrt(pow(velocity * cos(angle), 2) + pow(velocity * sin(angle), 2));

	DamageEntities(projectileDamage);

	if (GetPosition().y < -800)
	{
		pendingDestruction = true;
	}
}

void Projectile::DamageEntities(float damage)
{
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
				}

				(*iterE)->Damage(damage);
				pendingDestruction = true;
				break; // Only one thing damaged at a time;
			}
		}
		iterE++;
	}
}