#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Projectile.h"

/*
Basic two-barreled turret
*/
class Turret : public Entity
{
public:
	Turret(std::string filename, Faction fac, Projectile::ProjectileType type);
	~Turret();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	void Damage(float damage);
	void Destroy();

	Projectile::ProjectileType bulletType;
};