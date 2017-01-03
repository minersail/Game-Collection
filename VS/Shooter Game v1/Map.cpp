#include "stdafx.h"
#include "Map.h"
#include "Block.h"
#include "Game.h"
#include "Turret.h"
#include "Boss.h"

Map::Map(std::string filename)
{
	srand(time(0));
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;
}

Map::~Map()
{
}

void Map::Update(float deltaTime, sf::Event ev)
{
	if (Game::score % 1000 == 0)
	{
		Game::bossMode = true;
	}
}

void Map::InitializeObjects(int half)
{
	if (!Game::bossMode)
	{
		for (int i = 1; i <= 5; i++) // Random Walls
		{
			float rWidth = (rand() % 4 + 1) * 50.0f;
			float rHeight = (rand() % 2 + 1) * 50.0f;
			float rX = rand() % 700 + 50;
			float rY = rand() % 800 - half * 800;

			Block* wall1 = new Block("images/stonewall.png", rWidth, rHeight);
			Game::GetObjectQueue().Add("Block " + std::to_string(i), wall1, "back");
			wall1->SetPosition(rX, rY);
		}

		int rX = rand() % 700 + 50; // Random Turrets
		int rY = rand() % 800 - half * 800;
		Turret* turret1 = new Turret("images/turret1.png", Entity::Enemy, Projectile::ProjectileType(rand() % 3));
		Game::GetObjectQueue().Add("Enemy Turret", turret1, "back");
		turret1->SetPosition(rX, rY);
	}
	else
	{
		Boss* boss = new Boss("images/boss1.png");
		Game::GetObjectQueue().Add("Boss", boss, "back");
	}

	// Create walls at edge
	Block* wall1 = new Block("images/stonewall.png", 50, 800);
	Block* wall2 = new Block("images/stonewall.png", 50, 800);
	Block* backwall = new Block("images/stonewall.png", 800, 50);

	Game::GetObjectQueue().Add("Left Wall 1", wall1, "back");
	Game::GetObjectQueue().Add("Right Wall 1", wall2, "back");
	Game::GetObjectQueue().Add("Back Wall", backwall, "back");

	wall1->SetPosition(25, pow(-1, half) * 400);
	wall2->SetPosition(775, pow(-1, half) * 400);
	backwall->SetPosition(400, 825);
}