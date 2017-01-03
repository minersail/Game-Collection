#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(std::string filename, float angle, int speed, Faction fac);
	virtual ~Projectile();

	virtual void Update(float deltaTime, sf::Event ev);

	// Angle of the projectile in radians
	float angle;
	int velocity;
	float totalDist;
};