#pragma once
#include "stdafx.h"
#include "Soldier.h"

class AITurret : public Soldier
{
public:
	AITurret(std::string filename, Entity::Faction fac);
	~AITurret();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	Faction faction;
};