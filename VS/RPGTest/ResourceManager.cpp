#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	Load("images/tileset.png", "Tiles");
	Load("images/tileset2.png", "Building Tiles");
	Load("images/joe.png", "Joe");
	Load("images/npc1.png", "NPC 1");
	Load("images/npc2.png", "NPC 2");
	Load("images/oldman.png", "Old Man");
	Load("images/farmer.png", "Farmer");
	Load("images/sister.png", "Sister");
	Load("images/vendor.png", "Vendor");
	Load("images/will.png", "Will");
	Load("images/messagebox.png", "Message Box");
	Load("images/water.png", "Water");
	Load("images/stonehut.png", "Stone Hut");
	Load("images/bluehouse.png", "Blue House");
	Load("images/bluehouseroof.png", "Blue House Roof");
	Load("images/brownhouse.png", "Brown House");
	Load("images/grassside.png", "Grass Side");
	Load("images/grasscorner1.png", "Grass Corner 1");
	Load("images/grasscorner2.png", "Grass Corner 2");
	Load("images/fence.png", "Fence");	
	Load("images/floor.png", "Floor");
	Load("images/wall.png", "Wall");
	Load("images/wallcorner.png", "Wall Corner");
	Load("images/door.png", "Door");
	Load("images/inventory.png", "Inventory");
	Load("images/apple.png", "Apple");
}

ResourceManager::~ResourceManager()
{
	std::map<std::string, sf::Texture*>::iterator it = TextureList.begin();
	while (it != TextureList.end())
	{
		delete it->second;
		it++;
	}
}

void ResourceManager::Load(std::string filename, std::string texturename)
{
	sf::Texture* t1 = new sf::Texture();
	assert(t1->loadFromFile(filename));
	TextureList.insert(std::make_pair(texturename, t1));
}

sf::Texture& ResourceManager::Get(std::string texturename)
{
	return *(TextureList.find(texturename)->second);
}