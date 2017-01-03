#include "stdafx.h"
#include "PowerUp.h"
#include "Game.h"

PowerUp::PowerUp(std::string filename)
	:Apple(filename, false)
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Update(float deltaTime, sf::Event ev)
{
	if (Game::singlePlayer)
	{
		pendingDestruction = true;
	}
}