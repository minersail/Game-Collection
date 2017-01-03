#include "stdafx.h"
#include "Apple.h"
#include "Game.h"

Apple::Apple(std::string filename, bool perm)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	permanent = perm;
}

Apple::~Apple()
{
	std::vector<Apple*>::iterator iter = Game::appleList.begin();
	while (iter != Game::appleList.end())
	{
		if (*iter == this)
		{
			Game::appleList.erase(iter);
			return;
		}
		iter++;
	}
}

void Apple::Update(float deltaTime, sf::Event ev)
{
}

void Apple::Move()
{
	if (permanent)
	{
		SetPosition((rand() % 40) * 20 + 2, (rand() % 40) * 20 + 2);
	}
	else
	{
		pendingDestruction = true;
	}
}