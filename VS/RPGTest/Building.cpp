#include "stdafx.h"
#include "Building.h"
#include "Game.h"

Building::Building(float initX, float initY, std::string textureID, std::string name, UsePoint entrance, UsePoint exit, sf::IntRect hitBox)
	: UseObject(initX, initY, textureID, name, entrance), exitPoint(exit)
{
	if (hitBox != sf::IntRect(0, 0, 0, 0)) // A hitBox was given
	{
		SetHitBox(hitBox);
	}
	// else the constructor for Entity will automatically create a hitBox

	immovable = true;
}

Building::~Building()
{
}

void Building::Update(float deltaTime, sf::Event ev)
{
	if (CheckUsePoints(ev))
	{
		// As of right now, buildings are placed at chunk -1, coordinates (-800, 0)
		Game::SetView(-400, 400);
		Game::LockView(true);
		floorManager.Add("Joe", Game::GetPlayer());
		Game::GetPlayer()->SetPosition(exitPoint.x * 16, exitPoint.y * 16);

		Game::StartBuildingMode(this);
	}
}

void Building::SetFloorManager(GameObjectManager& objMnger)
{
	floorManager = objMnger;
}

GameObjectManager& Building::GetFloorManager()
{
	return floorManager;
}

std::vector<Entity*>& Building::GetCollisionList()
{
	return collisionList;
}