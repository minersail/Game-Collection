#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Turret.h"

class Boss : public Entity
{
public:
	Boss(std::string filename);
	~Boss();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);
	void Destroy();

	Turret LTurret;
	Turret RTurret;

	float targetLocation;
};