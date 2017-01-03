#pragma once
#include "stdafx.h"
#include "Entity.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	// All collisions are checked for before the game loop happens
	void Update();
	// Checks all entities in a chunk against all other entities in that chunk
	void CheckChunkCollisions(int chunk);
	void Add(int chunk, Entity* ent);
	void Remove(int chunk, Entity* ent);
	void SwitchBuildingList(std::vector<Entity*>& newList);
	std::vector<Entity*>& GetBuildingList();

private:
	// Master list of lists; Each sub-list contains all entities in a chunk
	std::vector<std::vector<Entity*>> EntityList;
	// List of chunks currently loaded
	std::vector<int> ChunkList;
	// Vector to hold all the entities for the current building
	std::vector<Entity*> BuildingList;
};