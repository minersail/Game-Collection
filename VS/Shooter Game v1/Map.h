#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Map : public VisibleGameObject
{
public:
	Map(std::string filename);
	~Map();

	void Update(float deltaTime, sf::Event ev);
	/* Creates objects in either the first or second half of the map; 0 for first and 1 for second */
	void InitializeObjects(int half);
};