#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Inventory.h"

class Player : public Character
{
public:
	Player(float initX, float initY, std::string textureID, std::string name);
	~Player();

	void Update(float deltaTime, sf::Event ev);
	Inventory& GetInventory();

	Direction keyPressed;

private:
	static const int JOE_HEIGHT = 26;
	static const int JOE_WIDTH = 17;

	Inventory PlayerInventory;
};
