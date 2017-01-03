#pragma once
#include "VisibleGameObject.h"

/* Class that has methods to store and retrieve VisibleGameObjects */
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	// Adds the new object-string pair to the back of the vector, meaning it will be last in draw order
	void Add(std::string name, VisibleGameObject* gameObject);
	// Adds the new object-string pair to the back of the vector, meaning it will be first in draw order
	void AddF(std::string name, VisibleGameObject* gameObject);
	int GetObjectCount() const;
	void PrintObjects();
	VisibleGameObject* Get(std::string name) const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void GameObjectManager::UpdateAll(sf::Event ev);
	
	/*Moves all objects except the map and walls back;*/
	void Shift();

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