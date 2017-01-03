#pragma once
#include "stdafx.h"
#include "Item.h"

class Inventory : public VisibleGameObject
{
public:
	Inventory();
	~Inventory();

	void Draw(sf::RenderWindow& rw);
	void DrawItems(sf::RenderWindow& rw);
	void Add(Item* newItem);
	void Remove(Item* item);
	// Gets the number of items with the itemName provided in the inventory
	int GetCount(std::string itemName);
	// Returns the ItemList
	std::vector<Item*>& GetItems();

private:
	static const int INVENTORY_WIDTH = 8;
	static const int INVENTORY_HEIGHT = 8;
	std::vector<Item*> ItemList;
};