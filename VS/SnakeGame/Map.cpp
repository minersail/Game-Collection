#include "stdafx.h"
#include "Map.h"
#include "Game.h"
#include "PowerUp.h"

Map::Map(std::string filename)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;
}

Map::~Map()
{
}

void Map::Update(float deltaTime, sf::Event ev)
{
	frameCount++;
	if (Game::GetObjectManager().Get("PowerUp 1") == NULL)
	{
		if (frameCount > 240)
		{
			frameCount = 0;
		}
		else if (frameCount == 240)
		{
			PowerUp* powerup = new PowerUp("images/powerup.png");
			Game::GetObjectManager().Add("PowerUp 1", powerup);
			powerup->SetPosition((rand() % 40) * 20 + 2, (rand() % 40) * 20 + 2);
			Game::appleList.push_back(powerup);
		}
	}
}