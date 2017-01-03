#include "stdafx.h"
#include "QuestManager.h"

QuestManager::QuestManager()
{
	ItemQuest* Q1 = new ItemQuest("Apple", 5);
	QuestList.push_back(Q1);
}

QuestManager::~QuestManager()
{
}

void QuestManager::SetQuestGiver(QuestGiver* giver)
{
	currentGiver = giver;
}

bool QuestManager::CheckQuest()
{
	ItemQuest* IQ = static_cast<ItemQuest*>(QuestList[currentGiver->questID - 1]);
	if (IQ != NULL)
	{
		if (currentGiver->GetInventory().GetCount(IQ->questItem) >= IQ->questItemNum)
		{
			return true;
		}
	}
	return false;
}