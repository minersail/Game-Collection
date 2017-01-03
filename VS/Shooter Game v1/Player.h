#pragma once
#include "stdafx.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update(float deltaTime, sf::Event ev);

	int moveSpeed; // Speed, in pixels per second
	int rotateSpeed; // Rotate speed, in degrees per second

	/* Keeps track of highest Y-coord (actually lowest because of inverse Cartesian) */
	float highscore;

	void Damage(float damage);
};