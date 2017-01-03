#pragma once
#include "stdafx.h"
#include "CollisionManager.h"
#include "Game.h"

CollisionManager::CollisionManager()
{
	for (int i = 0; i < 9; i++)
	{
		ChunkList.push_back(i);
	}

	for (int i = 0; i < Game::XCHUNKS * Game::YCHUNKS; i++) // One sub-vector for every chunk
	{
		std::vector<Entity*> li;
		EntityList.push_back(li);
	}
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	std::vector<int>::iterator it = ChunkList.begin();
	while (it != ChunkList.end())
	{
		CheckChunkCollisions(*it);
		it++;
	}
}

void CollisionManager::CheckChunkCollisions(int chunk)
{
	if (chunk == -1)
	{
		std::vector<Entity*>::iterator it = BuildingList.begin();
		std::vector<Entity*>::iterator it2 = BuildingList.begin();
		while (it != BuildingList.end())
		{
			it2 = it + 1; // Check an entity against all entities after it
			while (it2 != BuildingList.end())
			{
				if (!((*it)->immovable == true && (*it2)->immovable == true)) // Don't bother if checking if both entities are immovable
				{
					if ((*it)->CheckForCollision(*it2))
					{
						(*it)->collided = true;
						(*it2)->collided = true;
					}
				}
				it2++;
			}
			it++; // Repeat for every entity
		}
	}
	else
	{
		std::vector<Entity*>::iterator it = EntityList[chunk].begin();
		std::vector<Entity*>::iterator it2 = EntityList[chunk].begin();
		while (it != EntityList[chunk].end())
		{
			it2 = it + 1; // Check an entity against all entities after it
			while (it2 != EntityList[chunk].end())
			{
				if (!((*it)->immovable == true && (*it2)->immovable == true)) // Don't bother if checking if both entities are immovable
				{
					if ((*it)->CheckForCollision(*it2))
					{
						(*it)->collided = true;
						(*it2)->collided = true;
					}
				}
				it2++;
			}
			it++; // Repeat for every entity
		}
	}
}

void CollisionManager::Add(int chunk, Entity* ent)
{
	if (chunk == -1)
	{
		BuildingList.push_back(ent);
	}
	else if (chunk > 8 || chunk < 0)
	{
		std::cout << ent->name << ", Chunk: " << chunk << std::endl;
		assert(false);
	}
	else
	{
		EntityList[chunk].push_back(ent);
	}
}

void CollisionManager::Remove(int chunk, Entity* ent)
{
	if (chunk == -1)
	{
		std::vector<Entity*>::iterator it = BuildingList.begin();
		while (it != BuildingList.end())
		{
			if (*it == ent)
			{
				BuildingList.erase(it);
				return;
			}
			else
			{
				it++;
			}
		}
	}
	else
	{
		// Iterating from the reverse will be faster since entities switching chunks will most likely be at the end
		std::vector<Entity*>::reverse_iterator it = EntityList[chunk].rbegin();
		std::vector<Entity*>::reverse_iterator end = EntityList[chunk].rend();
		while (it != end)
		{
			if (*it == ent)
			{
				EntityList[chunk].erase(--(it.base()));
				return;
			}
			else
			{
				it++;
			}
		}
	}
}

void CollisionManager::SwitchBuildingList(std::vector<Entity*>& newList)
{
	BuildingList.clear();
	std::vector<Entity*>::iterator it = newList.begin();
	while (it != newList.end())
	{
		BuildingList.push_back(*it);
		it++;
	}
}

std::vector<Entity*>& CollisionManager::GetBuildingList()
{
	return BuildingList;
}