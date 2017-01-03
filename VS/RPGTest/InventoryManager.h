#pragma once
#include "stdafx.h"
#include "QuestGiver.h"

class InventoryManager
{
public:
	InventoryManager();
	~InventoryManager();
	
	void Manage(sf::Event ev, sf::RenderWindow& rw);
	void SetQuestGiver(QuestGiver* giver);

	// Handles what happens when items are clicked
	// Returns true if an item was moved from one inventory to another
	bool UpdateItems(sf::Event ev, Inventory* inv1, Inventory* inv2 = NULL);
	void ExitInventory();

private:
	QuestGiver* currentQuestGiver;
};