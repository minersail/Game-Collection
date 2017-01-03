#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Entity.h"
#include "Turret.h"
#include "LifeBar.h"

class Tank : public Entity
{
public:
	Tank(std::string filename);
	~Tank();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);
	void Damage(float damage);
	Turret MainTurret;

	int speed;
};
