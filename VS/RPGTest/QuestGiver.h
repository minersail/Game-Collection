#pragma once
#include "stdafx.h"
#include "Messenger.h"
#include "Inventory.h"

class QuestGiver : public Messenger
{
public:
	QuestGiver(float initX, float initY, std::string textureID, std::string name, int talkID, int questId);
	~QuestGiver();

	void Update(float deltaTime, sf::Event ev);
	Inventory& GetInventory();

	// Quest ID
	int questID;

private:
	Inventory QuestInventory;
};