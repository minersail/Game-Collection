#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Map : public VisibleGameObject
{
public:
	Map(std::string filename);
	~Map();

	void Update(float deltaTime, sf::Event ev);
};