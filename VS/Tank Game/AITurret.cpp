#include "stdafx.h"
#include "AITurret.h"
#include "Projectile.h"
#include "Game.h"

AITurret::AITurret(std::string filename, Entity::Faction fac)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetTextureRect().width * 3 / 8, GetTextureRect().height / 2);
	faction = fac;
	frameCount = 0;
}

AITurret::~AITurret()
{
}

void AITurret::Update(float deltaTime, sf::Event ev)
{
	frameCount += 1;

	GetTarget(faction);
	if (target == NULL)
	{
		return;
	}

	float dx = target->GetPosition().x - GetPosition().x;
	float dy = target->GetPosition().y - GetPosition().y;

	if (dx == 0)
		dx = 0.0001f;

	float angle = atan(dy / dx) * 180 / 3.1415926f;

	if (dx < 0)
	{
		angle += 180;
	}
	SetRotation(angle);

	if (fmod(frameCount, 20) == 0)
	{
		Projectile* shell = new Projectile("images/chris2.png", angle / 180 * 3.141592f, 6, faction);
		Game::GetObjectQueue().Add("chris", shell, "back");

		float rotRad = GetRotation() / 180 * 3.141592f;
		shell->SetPosition(GetPosition().x + 50 * cos(rotRad), GetPosition().y + 50 * sin(rotRad));
	}
}

void AITurret::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
}