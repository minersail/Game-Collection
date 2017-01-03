#include "stdafx.h"
#include "Projectile.h"

/*
Invisible projectile ~size big starting from ~loc at the angle ~angleI (RADIANS) for a ~dist amount.
Has a Cast() function to return true if the cast hit anything.
*/
class RayCast : public Projectile
{
public:
	RayCast(sf::Vector2i size, sf::Vector2f loc, float angleI, float dist);
	virtual ~RayCast();

	/* Returns length of cast if the cast hit something, 0 if it traveled testDist unobstructed (This can be used as a boolean for hit / no hit).
	Also stores first hit entity in parameter given.
	*/
	float Cast(Entity& obstruction, Faction testFac);
	// Cast overload that takes in two factions to test
	float Cast(Entity& obstruction, Faction testFac1, Faction testFac2);

	float testDist;
};