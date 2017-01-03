#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Item : public VisibleGameObject
{
public:
	Item(float initX, float initY, std::string textureID, std::string name);
	~Item();
	
	virtual void Update(float deltaTime, sf::Event ev);
	virtual void Draw(sf::RenderWindow& rw);

	virtual bool CheckForClick(sf::Event ev);

	// Whether or not the item is selected by the mouse
	bool selected;
	// Whether or not the item is in an inventory
	bool inInventory;
};