#pragma once
#include "stdafx.h"
#include "Item.h"
#include "QuestGiver.h"

class QuestManager
{
public:
	QuestManager();
	~QuestManager();

	enum QuestType
	{
		Null, Item
	};

	struct Quest
	{
		QuestType type;
	};

	struct ItemQuest : Quest
	{
		std::string questItem;
		int questItemNum;

		ItemQuest(std::string itemName, int amount)
		{
			questItem = itemName;
			questItemNum = amount;
			type = Item;
		}
	};

	void SetQuestGiver(QuestGiver* giver);
	bool CheckQuest();

private:
	QuestGiver* currentGiver;
	std::vector<Quest*> QuestList; // Pointers are necessary for polymorphism
};