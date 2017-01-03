#pragma once
#include "stdafx.h"
#include "GameObjectManager.h"
#include "Entity.h"

// Class that holds all the current items on screen
class Tile
{
public:
	Tile();
	~Tile();

	std::vector<Entity*> AllyList; // List of all allies in this tile only; different from the global ally list
	std::vector<Entity*> EnemyList; // List of all enemies in this tile only; different from the global ally list
	std::vector<Entity*> EntityList; // List of all entities in this tile only; different from the global ally list
	GameObjectManager TileObjects; // GameObjectManager for this tile only, not to be confused with Game::_gameObjectManager
};