#pragma once
#include "stdafx.h"
#include "UseObject.h"
#include "GameObjectManager.h"

class Building : public UseObject
{
public:
	// exit is the UsePoint for exiting the building
	Building(float initX, float initY, std::string textureID, std::string name, UsePoint entrance, UsePoint exit, sf::IntRect hitBox = sf::IntRect(0, 0, 0, 0));
	~Building();

	void Update(float deltaTime, sf::Event ev);
	void SetFloorManager(GameObjectManager& objMnger);
	GameObjectManager& GetFloorManager();
	std::vector<Entity*>& GetCollisionList();

	UsePoint exitPoint;

private:
	GameObjectManager floorManager;
	std::vector<Entity*> collisionList;
};