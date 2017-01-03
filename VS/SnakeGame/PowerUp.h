#pragma once
#include "stdafx.h"
#include "Apple.h"

class PowerUp : public Apple
{
public:
	PowerUp(std::string filename);
	~PowerUp();

	void Update(float deltaTime, sf::Event ev);
};