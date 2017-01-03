#include "stdafx.h"
#include "InventoryManager.h"
#include "Game.h"

InventoryManager::InventoryManager()
	: currentQuestGiver(NULL)
{
}

InventoryManager::~InventoryManager()
{
}

void InventoryManager::Manage(sf::Event ev, sf::RenderWindow& rw)
{
	if (currentQuestGiver == NULL) // Player is accessing inventory through escape button
	{
		Inventory* PI = &Game::GetPlayer()->GetInventory();
		PI->SetPosition(450, 200, true);
		PI->Draw(rw);
		PI->DrawItems(rw);

		UpdateItems(ev, PI);
	}
	else // Player is accessing inventory through dialogue with a QuestGiver
	{
		Inventory* PI = &Game::GetPlayer()->GetInventory(); // Must be passed through pointer so that items
		Inventory* QI = &currentQuestGiver->GetInventory(); // are deleted from the inventory, not a copy
		PI->SetPosition(450, 200, true);
		QI->SetPosition(50, 200, true);
		PI->Draw(rw);
		QI->Draw(rw);
		PI->DrawItems(rw);
		QI->DrawItems(rw);

		// Update both inventories to place items in the other
		if (!UpdateItems(ev, PI, QI))
			UpdateItems(ev, QI, PI); // Stagger them so that they don't remark themselves as clicked and unclicked

		Game::GetQuestManager().SetQuestGiver(currentQuestGiver);
		if (Game::GetQuestManager().CheckQuest())
		{
			Game::GetDialogueManager().AdvanceDialogue();
		}
	}


	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
	{
		ExitInventory();
	}
}

bool InventoryManager::UpdateItems(sf::Event ev, Inventory* inv1, Inventory* inv2)
{
	bool inventorySwitch = false;

	// During Game::Inventory, InventoryManager handles items
	std::vector<Item*>::iterator it = inv1->GetItems().begin();
	while (it != inv1->GetItems().end())
	{
		bool itemMoved = false;

		if ((*it)->CheckForClick(ev))
		{
			if ((*it)->selected)
			{
				(*it)->selected = false;
				if (inv2 != NULL) // Only one inventory was given
				{
					if (inv2->GetBoundingRect().contains(Game::GetMousePos(true))) // Player clicked inside other inventory
					{
						inv2->Add(*it);
						it = inv1->GetItems().erase(it);

						itemMoved = true;
						inventorySwitch = true;
					}
					else if (!inv1->GetBoundingRect().contains(Game::GetMousePos(true))) // Player clicked outside both inventories
					{ // Drop the item					
						(*it)->inInventory = false;
						(*it)->GetSprite().setScale(1, 1);
						(*it)->SetPosition(Game::GetPlayer()->GetPosition().x - (*it)->GetTextureRect().width / 2,
							Game::GetPlayer()->GetPosition().y - (*it)->GetTextureRect().height / 2);

						it = inv1->GetItems().erase(it);

						itemMoved = true;
					}
				}
				else if (!inv1->GetBoundingRect().contains(Game::GetMousePos(true))) // Player clicked outside inventory
				{ // Drop the item					
					(*it)->inInventory = false;
					(*it)->GetSprite().setScale(1, 1);
					(*it)->SetPosition(Game::GetPlayer()->GetPosition().x - (*it)->GetTextureRect().width / 2,
						Game::GetPlayer()->GetPosition().y - (*it)->GetTextureRect().height / 2);

					it = inv1->GetItems().erase(it);

					itemMoved = true;
				}
			}
			else
			{
				(*it)->selected = true;
			}
		}

		if (!itemMoved)
			it++;
	}
	return inventorySwitch;
}

void InventoryManager::ExitInventory()
{
	if (Game::GetPlayer()->GetPosition().x > 0) // If player is in the building chunk
	{
		Game::_gameState = Game::Playing;
	}
	else
	{
		Game::_gameState = Game::InBuilding;
	}
}

void InventoryManager::SetQuestGiver(QuestGiver* giver)
{
	currentQuestGiver = giver;
}