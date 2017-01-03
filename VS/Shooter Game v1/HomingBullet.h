#pragma once
#include "stdafx.h"
#include "Projectile.h"

class HomingBullet : public Projectile
{
public:
	HomingBullet(std::string filename, float angle, int speed, Faction fac, float damage, bool animated = false);
	~HomingBullet();

	void Update(float deltaTime, sf::Event ev);
};