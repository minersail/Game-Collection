#pragma once
#include "stdafx.h"
#include "Projectile.h"

class RicochetBullet : public Projectile
{
public:
	RicochetBullet(std::string filename, float angleI, int speed, Faction fac, float damage);
	~RicochetBullet();

	void Update(float deltaTime, sf::Event ev);
	void DamageEntities(float damage);

	int bounceCount;
};