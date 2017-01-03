#include "stdafx.h"
#include "HomingBullet.h"
#include "Game.h"
#include "Block.h"
#include "RayCast.h"
#include "Player.h"

HomingBullet::HomingBullet(std::string filename, float angleI, int speed, Faction fac, float damage, bool animated)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	angle = angleI;
	velocity = speed;
	projectileDamage = damage;
	faction = fac;
	projType = Homing;
	animation = animated;

	if (animated)
	{
		SetTextureRect(0, 0, GetSpriteRect().width, GetSpriteRect().height / 2);
	}
}

HomingBullet::~HomingBullet()
{
}

void HomingBullet::Update(float deltaTime, sf::Event ev)
{
	frameCount += 1;
	float PI = 3.141592f;
	if (fmod(frameCount, 10) == 0) // Every half-second recalculate angle
	{		
		Player* player = dynamic_cast<Player*>(Game::GetObjectManager().Get("Player"));
		float dx = player->GetPosition().x - GetPosition().x;
		float dy = player->GetPosition().y - GetPosition().y;

		if (dx == 0)
		{
			dx = 0.00001f;
		}
		float playerAngle = atan(dy / dx); // Angle in the direction of the player

		if (dx < 0)
			playerAngle += PI;

		if (abs(angle - playerAngle) > PI) // If the angles are 180 degrees apart from one another
		{								   // e.g. 45 and 315 which would return 180 degrees
			angle = (angle + playerAngle) / 2 + PI; // Add 180 degrees
		}
		else
		{
			angle = (angle + playerAngle) / 2; // Halfway between current angle and angle to player
		}

		if (animation)
		{
			int newTop = (GetTextureRect().top == 0) ? GetTextureRect().height : 0;
			SetTextureRect(0, newTop, GetTextureRect().width, GetTextureRect().height);
		}
	}
	SetRotation(angle * 180 / PI);
	SetPosition(GetPosition().x + velocity * cos(angle), GetPosition().y + velocity * sin(angle));
	totalDist += sqrt(pow(velocity * cos(angle), 2) + pow(velocity * sin(angle), 2));
	
	DamageEntities(projectileDamage);
}