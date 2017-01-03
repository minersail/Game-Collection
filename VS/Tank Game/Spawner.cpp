#include "stdafx.h"
#include "Spawner.h"
#include "Game.h"

/*
Template for spawning entities---NOTE: On MSVS 2013 you must rebuild to see changes in this file
*/
template<class T>
Spawner<T>::Spawner(std::string filename, T* spawn, sf::Vector2f spawnLoc)
	: frameCount(0)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	SpawnTemplate = new T(*spawn); // Critical that you write a proper copy constructor for any class you wish to template

	std::vector<Entity*>::iterator iter = Game::EnemyList.begin();
	while (iter != Game::EnemyList.end())
	{
		if (*iter == SpawnTemplate)
		{
			Game::EnemyList.erase(iter); // Remove this template from the list of enemies, as it will not be visible or interactible
			break;
		}
		iter++;
	}

	if (spawn->faction == Entity::Ally)
	{
		TileData::CurrentTile->AllyList.push_back(this);
	}
	else if (spawn->faction == Entity::Enemy)
	{
		TileData::CurrentTile->EnemyList.push_back(this);
	}

	SpawnLoc = spawnLoc;
	LifeBar.SetScale(2.5);
	health = healthMax = 500;
	faction = SpawnTemplate->faction;
}

template<class T>
Spawner<T>::~Spawner()
{
	if (Game::_gameState != Game::Exiting)
	{
		RemoveFromList(this, Game::EntityList);
		if (SpawnTemplate->faction == Enemy)
		{
			RemoveFromList(this, Game::EnemyList);
		}
		else if (SpawnTemplate->faction == Ally)
		{
			RemoveFromList(this, Game::AllyList);
		}
	}
}

template<class T>
void Spawner<T>::Update(float deltaTime, sf::Event ev)
{
	frameCount += 1;
	Block::Update(deltaTime, ev);

	if (fmod(frameCount, 180) == 0)
	{
		T* newSpawn1 = new T(*SpawnTemplate);
		Game::GetObjectQueue().Add("Spawn - " + name, newSpawn1, "back");
		Game::EntityList.push_back(newSpawn1);
		newSpawn1->SetPosition(SpawnLoc.x - 30, SpawnLoc.y);

		T* newSpawn2 = new T(*SpawnTemplate);
		Game::GetObjectQueue().Add("Spawn - " + name, newSpawn2, "back");
		Game::EntityList.push_back(newSpawn2);
		newSpawn2->SetPosition(SpawnLoc.x + 30, SpawnLoc.y);
	}
	LifeBar.SetPosition(GetPosition().x - GetBoundingRect().width / 2, GetPosition().y - 100);
	LifeBar.SetHealth(health, healthMax);
}

template<class T>
void Spawner<T>::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	LifeBar.Draw(rw);
}

template<class T>
void Spawner<T>::Damage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		pendingDestruction = true;
	}
}