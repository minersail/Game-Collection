#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(std::string filename, float angleI, int speed, Faction fac, float damage);
	virtual ~Projectile();

	virtual void Update(float deltaTime, sf::Event ev);
	/*
	Iterates through the entity list, damaging the first that it collides with 
	*/
	virtual void DamageEntities(float damage);
	virtual void Destroy();

	// Angle of the projectile in radians
	float angle;
	int velocity;
	float totalDist;
	float projectileDamage;
	bool animation;

	enum ProjectileType 
	{
		Straight, Homing, Ricochet, Explosive, Piercing
	};

	ProjectileType projType;

	// Boolean for whether the bullet was destroyed by hitting a wall
	bool hitWall;
	// Location of the wall that the bullet hit
	sf::Vector2f wallLoc;
	// Size of the wall that the bullet hit
	sf::Vector2f wallSize;
};