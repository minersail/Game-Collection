#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.push_back(std::pair<std::string, VisibleGameObject*>(name, gameObject));
	gameObject->name = name;
}

void GameObjectManager::AddF(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(_gameObjects.begin() + 1, std::pair<std::string, VisibleGameObject*>(name, gameObject));
	gameObject->name = name;
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::vector<std::pair<std::string, VisibleGameObject*>>::const_iterator results = _gameObjects.begin();
	while (results != _gameObjects.end())
	{
		if (results->first == name)
		{
			return results->second;
		}
		results++;
	}
	return NULL;
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}

void GameObjectManager::PrintObjects()
{
	std::vector<std::pair<std::string, VisibleGameObject*>>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		std::cout << itr->first << std::endl;
		itr++;
	}
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::vector<std::pair<std::string, VisibleGameObject*>>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::UpdateAll(sf::Event ev)
{
	std::vector<std::pair<std::string, VisibleGameObject*>>::const_iterator itr = _gameObjects.begin();
	float timeDelta = clock.restart().asSeconds();

	while (itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta, ev);

		if (itr->second->pendingDestruction == true)
		{
			delete itr->second;
			itr = _gameObjects.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

