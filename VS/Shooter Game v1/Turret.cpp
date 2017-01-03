#pragma once
#include "stdafx.h"
#include "Turret.h"
#include "Player.h"
#include "Game.h"
#include "HomingBullet.h"
#include "RicochetBullet.h"
#include "Item.h"

Turret::Turret(std::string filename, Faction fac, Projectile::ProjectileType type)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 8);
	faction = fac;
	SetTextureRect(0, 0, GetSpriteRect().width, GetSpriteRect().height / 4);
	bulletType = type;
}

Turret::~Turret()
{
	Item* destroyedturret = new Item(texturefile.erase(texturefile.length() - 4, texturefile.length()) + "destroyed.png", 10);
	Game::GetObjectQueue().Add("Destroyed Turret", destroyedturret, "front");
	destroyedturret->SetPosition(GetPosition());
	destroyedturret->SetRotation(GetRotation());
}

void Turret::Destroy()
{
	Item* destroyedturret = new Item(texturefile.erase(texturefile.length() - 4, texturefile.length()) + "destroyed.png", 10);
	Game::GetObjectQueue().Add("Destroyed Turret", destroyedturret, "front");
	destroyedturret->SetPosition(GetPosition());
	destroyedturret->SetRotation(GetRotation());
}

void Turret::Update(float deltaTime, sf::Event ev)
{
	frameCount++;
	Player* player = dynamic_cast<Player*>(Game::GetObjectManager().Get("Player"));

	float PI = 3.141592f;
	float dx = player->GetPosition().x - GetPosition().x;
	float dy = player->GetPosition().y - GetPosition().y;

	float angleRad = atan(dy / dx); // Angle in the direction of the target, based on locations and trigonometry

	if (dx < 0)
		angleRad += PI;

	float angleDeg = angleRad * 180 / PI;
	SetRotation(angleDeg);
	
	if (bulletType == Projectile::Straight)
	{
		if (fmod(frameCount, 30) == 0)
		{
			Projectile* bullet1 = new Projectile("images/turretbullet.png", GetRotation(false), 10, Enemy, 3);
			Projectile* bullet2 = new Projectile("images/turretbullet.png", GetRotation(false), 10, Enemy, 3);
			Game::GetObjectQueue().Add("bullet", bullet1, "back");
			Game::GetObjectQueue().Add("bullet", bullet2, "back");
			bullet1->SetPosition(GetPosition().x + 35 * cos(angleRad) + 8 * cos(angleRad + PI / 2),
				GetPosition().y + 35 * sin(angleRad) + 8 * sin(angleRad + PI / 2));
			bullet2->SetPosition(GetPosition().x + 35 * cos(angleRad) - 8 * cos(angleRad + PI / 2),
				GetPosition().y + 35 * sin(angleRad) - 8 * sin(angleRad + PI / 2));
			bullet1->SetRotation(GetRotation());
			bullet2->SetRotation(GetRotation());
		}
	}
	else if (bulletType == Projectile::Homing)
	{
		if (fmod(frameCount, 50) == 0)
		{
			HomingBullet* bullet1 = new HomingBullet("images/homingbullet.png", GetRotation(false), 5, Enemy, 3, true);
			HomingBullet* bullet2 = new HomingBullet("images/homingbullet.png", GetRotation(false), 5, Enemy, 3, true);
			Game::GetObjectQueue().Add("bullet", bullet1, "back");
			Game::GetObjectQueue().Add("bullet", bullet2, "back");
			bullet1->SetPosition(GetPosition().x + 35 * cos(angleRad) + 8 * cos(angleRad + PI / 2),
				GetPosition().y + 35 * sin(angleRad) + 8 * sin(angleRad + PI / 2));
			bullet2->SetPosition(GetPosition().x + 35 * cos(angleRad) - 8 * cos(angleRad + PI / 2),
				GetPosition().y + 35 * sin(angleRad) - 8 * sin(angleRad + PI / 2));
			bullet1->SetRotation(GetRotation());
			bullet2->SetRotation(GetRotation());
		}
	}
	else if (bulletType == Projectile::Ricochet)
	{
		if (fmod(frameCount, 10) == 0)
		{
			RicochetBullet* bullet1 = new RicochetBullet("images/bullet.png", GetRotation(false), 15, Enemy, 3);
			RicochetBullet* bullet2 = new RicochetBullet("images/bullet.png", GetRotation(false), 15, Enemy, 3);
			Game::GetObjectQueue().Add("bullet", bullet1, "back");
			Game::GetObjectQueue().Add("bullet", bullet2, "back");

			float angleOffset = rand() % 11 - 5;
			angleOffset = angleOffset;

			bullet1->SetPosition(GetPosition().x + 35 * cos(angleRad) + 8 * cos(angleRad + PI / 2),
				GetPosition().y + 35 * sin(angleRad) + 8 * sin(angleRad + PI / 2));
			bullet2->SetPosition(GetPosition().x + 35 * cos(angleRad) - 8 * cos(angleRad + PI / 2),
				GetPosition().y + 35 * sin(angleRad) - 8 * sin(angleRad + PI / 2));
			bullet1->SetRotation(GetRotation() + angleOffset);
			bullet2->SetRotation(GetRotation() + angleOffset);
		}
	}

	UpdateLifeBar(20, 50);
}

void Turret::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	LifeBar.Draw(rw);
}

void Turret::Damage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		pendingDestruction = true;
	}
	else if (health <= healthMax * 1 / 4)
	{
		SetTextureRect(0, GetSpriteRect().height * 3, GetSpriteRect().width, GetSpriteRect().height);
	}
	else if (health <= healthMax * 2 / 4)
	{
		SetTextureRect(0, GetSpriteRect().height * 2, GetSpriteRect().width, GetSpriteRect().height);
	}
	else if (health <= healthMax * 3 / 4) // Switch texture rect based on health remaining
	{
		SetTextureRect(0, GetSpriteRect().height, GetSpriteRect().width, GetSpriteRect().height);
	}
}