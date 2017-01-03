#include "stdafx.h"
#include "QuestGiver.h"
#include "Game.h"

QuestGiver::QuestGiver(float initX, float initY, std::string textureID, std::string name, int talkID, int questId)
	: Messenger(initX, initY, textureID, name, talkID), questID(questId)
{
}

QuestGiver::~QuestGiver()
{
}

void QuestGiver::Update(float deltaTime, sf::Event ev)
{
	if (CheckUsePoints(ev))
	{
		sf::IntRect joeRect = Game::GetPlayer()->GetTextureRect();
		// Have the Messenger face Joe after talking
		if (joeRect.left == joeRect.width * 0)
			SetTextureRect(GetTextureRect().width * 2, 0, GetTextureRect().width, GetTextureRect().height);
		if (joeRect.left == joeRect.width * 1)
			SetTextureRect(GetTextureRect().width * 3, 0, GetTextureRect().width, GetTextureRect().height);
		if (joeRect.left == joeRect.width * 2)
			SetTextureRect(GetTextureRect().width * 0, 0, GetTextureRect().width, GetTextureRect().height);
		if (joeRect.left == joeRect.width * 3)
			SetTextureRect(GetTextureRect().width * 1, 0, GetTextureRect().width, GetTextureRect().height);

		Game::GetDialogueManager().SetNPC(this);
		Game::GetInventoryManager().SetQuestGiver(this);
		Game::_gameState = Game::Talking;
	}
}

Inventory& QuestGiver::GetInventory()
{
	return QuestInventory;
}