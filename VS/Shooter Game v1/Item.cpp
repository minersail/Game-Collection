#include "stdafx.h"
#include "Item.h"

Item::Item(std::string filename, float time)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 2);
	totalTime = time;
}

Item::~Item()
{
}

void Item::Update(float deltaTime, sf::Event ev)
{
	totalTime -= deltaTime;
	if (totalTime <= 0)
	{
		pendingDestruction = true;
	}
}