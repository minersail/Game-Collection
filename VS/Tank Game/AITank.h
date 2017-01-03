#pragma once
#include "stdafx.h"
#include "Soldier.h"
#include "AITurret.h"

class AITank : public Soldier
{
public:
	AITank(std::string basefile, std::string turretfile, float life, Faction fac);
	~AITank();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	AITurret MainTurret;
};