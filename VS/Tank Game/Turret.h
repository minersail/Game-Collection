#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Turret : public VisibleGameObject
{
public:
	Turret(std::string filename);
	~Turret();

	virtual void Update(float deltaTime, sf::Event ev);
};
