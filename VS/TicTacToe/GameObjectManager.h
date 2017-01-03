#pragma once
#include "VisibleGameObject.h"

/* Class that has methods to store and retrieve VisibleGameObjects */
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void AddF(std::string name, VisibleGameObject* gameObject);
	int GetObjectCount() const;
	void PrintObjects();
	VisibleGameObject* Get(std::string name) const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void GameObjectManager::UpdateAll(sf::Event ev);

private:
	std::vector<std::pair<std::string, VisibleGameObject*>> _gameObjects;

	sf::Clock clock;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};