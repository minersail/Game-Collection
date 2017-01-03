#include "stdafx.h"
#include "Inventory.h"
#include "Game.h"

Inventory::Inventory()
	: VisibleGameObject(0, 0, "Inventory") // Is not put into GameObjectManager
{

}

Inventory::~Inventory()
{
	/*std::vector<Item*>::iterator it = ItemList.begin();
	while (it != ItemList.end())
	{
		delete *it;
		it = ItemList.erase(it);
	}*/
}

void Inventory::Add(Item* newItem)
{
	ItemList.push_back(newItem);
}

void Inventory::Remove(Item* item)
{
	std::vector<Item*>::iterator it = ItemList.begin();
	while (it != ItemList.end())
	{
		if (*it == item)
		{
			ItemList.erase(it);
			return;
		}
		it++;
	}
}

int Inventory::GetCount(std::string itemName)
{
	int items = 0;

	std::vector<Item*>::iterator it = ItemList.begin();
	while (it != ItemList.end())
	{
		if ((*it)->name == itemName)
		{
			items++;
		}
		it++;
	}

	return items;
}

void Inventory::Draw(sf::RenderWindow& rw)
{
	rw.draw(GetSprite());	
}

void Inventory::DrawItems(sf::RenderWindow& rw)
{
	std::vector<Item*>::iterator it = ItemList.begin();
	while (it != ItemList.end())
	{
		int index = it - ItemList.begin();
		if ((*it)->selected == false)
		{
			(*it)->SetPosition(GetPosition().x + 8 + (index % INVENTORY_WIDTH) * 36, GetPosition().y + 8 + (index / INVENTORY_WIDTH) * 36);
		}
		else
		{
			(*it)->SetPosition(sf::Vector2f(Game::GetMousePos(true).x - (*it)->GetTextureRect().width / 2,
				Game::GetMousePos(true).y - (*it)->GetTextureRect().height / 2));
		}

		rw.draw((*it)->GetSprite()); // Don't use the Item's Draw() function
		it++;
	}
}

std::vector<Item*>& Inventory::GetItems()
{
	return ItemList;
}