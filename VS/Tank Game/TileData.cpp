#include "stdafx.h"
#include "TileData.h"

TileData::TileData()
{
	
}

TileData::~TileData()
{
}

// Loads tile 1's data and sets current tile to tile 1
void TileData::LoadTile1()
{
	Tile* tile1 = new Tile(); // Possible data leak
	CurrentTile = tile1;

	Map* map = new Map("images/grass.png");
	Tank* tank = new Tank("images/tank2.png");
	AITank* enemytank = new AITank("images/tank2.png", "images/turret2.png", 500, Entity::Enemy);
	Soldier* wingman1 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Soldier* wingman2 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Soldier* wingman3 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Soldier* wingman4 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Block* block = new Block("images/stonewall.png", 500, 100);
	Block* block2 = new Block("images/stonewall.png", 100, 500);
	Block* block3 = new Block("images/stonewall.png", 200, 200);
	Block* block4 = new Block("images/stonewall.png", 200, 200);
	Block* block5 = new Block("images/stonewall.png", 500, 100);
	Block* block6 = new Block("images/stonewall.png", 100, 500);
	Soldier* enemy1 = new Soldier("images/soldier.png", 30, Entity::Enemy);
	Spawner<Soldier>* barrack1 = new Spawner<Soldier>("images/barrack.png", enemy1, sf::Vector2f(1800, 1880));
	DisplayBox* scoreboard = new DisplayBox(sf::Vector2i(100, 50), 150, 50);

	Initialize("Grass", map, 0, 0);
	Initialize("Tank", tank, 512, 512);
	Initialize("Enemy Tank", enemytank, 1700, 1700);
	Initialize("Wingman 1", wingman1, 440, 360);
	Initialize("Wingman 2", wingman2, 440, 440);
	Initialize("Wingman 3", wingman3, 360, 360);
	Initialize("Wingman 4", wingman4, 360, 440);
	Initialize("Wall 1", block, 1000, 600);
	Initialize("Wall 2", block2, 600, 1000);
	Initialize("Wall 3", block3, 1000, 1400);
	Initialize("Wall 4", block4, 1400, 1000);
	Initialize("Wall 5", block5, 1900, 1500);
	Initialize("Wall 6", block6, 1500, 1900);
	Initialize("Guard", enemy1, 1700, 1700);
	Initialize("Barrack 1", barrack1, 1800, 1800);
	Initialize("Scoreboard", scoreboard, 100, 50);
}

void TileData::LoadTile2()
{
	Tile* tile2 = new Tile();
	CurrentTile = tile2;

	Map* map = new Map("images/grass.png");
	Tank* tank = new Tank("images/tank2.png");
	AITank* enemytank1 = new AITank("images/tank2.png", "images/turret2.png", 500, Entity::Enemy);
	AITank* enemytank2 = new AITank("images/tank2.png", "images/turret2.png", 500, Entity::Enemy);
	AITank* enemytank3 = new AITank("images/tank2.png", "images/turret2.png", 500, Entity::Enemy);
	AITank* enemytank4 = new AITank("images/tank2.png", "images/turret2.png", 500, Entity::Enemy);
	AITank* enemytank5 = new AITank("images/tank.png", "images/turret.png", 1500, Entity::Enemy);
	DisplayBox* scoreboard = new DisplayBox(sf::Vector2i(100, 50), 150, 50);

	Initialize("Grass", map, 0, 0);
	Initialize("Tank", tank, 512, 512);
	Initialize("Enemy Tank 1", enemytank1, 2000, 600);
	Initialize("Enemy Tank 2", enemytank2, 2000, 800);
	Initialize("Enemy Tank 3", enemytank3, 2000, 1200);
	Initialize("Enemy Tank 4", enemytank4, 2000, 1400);
	Initialize("Boss Tank", enemytank5, 2000, 1000);
	Initialize("Scoreboard", scoreboard, 100, 50);
}

void TileData::LoadTile3()
{
	Tile* tile3 = new Tile();
	CurrentTile = tile3;

	Map* map = new Map("images/grass.png");
	Tank* tank = new Tank("images/tank2.png");
	Soldier* guard1 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Soldier* guard2 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Soldier* guard3 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Soldier* guard4 = new Soldier("images/allysoldier.png", 100, Entity::Ally);
	Block* block1 = new Block("images/stonewall.png", 500, 100);
	Block* block2 = new Block("images/stonewall.png", 500, 100);
	Block* block3 = new Block("images/stonewall.png", 100, 500);
	Block* block4 = new Block("images/stonewall.png", 100, 500);
	Soldier* enemy1 = new Soldier("images/soldier.png", 30, Entity::Enemy);
	Spawner<Soldier>* barrack1 = new Spawner<Soldier>("images/barrack.png", guard1, sf::Vector2f(1000, 1080));
	Spawner<Soldier>* barrack2 = new Spawner<Soldier>("images/barrack.png", enemy1, sf::Vector2f(200, 280));
	Spawner<Soldier>* barrack3 = new Spawner<Soldier>("images/barrack.png", enemy1, sf::Vector2f(200, 1880)); // Finish
	Spawner<Soldier>* barrack4 = new Spawner<Soldier>("images/barrack.png", enemy1, sf::Vector2f(1800, 280));
	Spawner<Soldier>* barrack5 = new Spawner<Soldier>("images/barrack.png", enemy1, sf::Vector2f(1800, 1880));
	DisplayBox* scoreboard = new DisplayBox(sf::Vector2i(100, 50), 150, 50);

	Initialize("Grass", map, 0, 0);
	Initialize("Tank", tank, 1024, 800);
	Initialize("Wingman 1", guard1, 1100, 1100);
	Initialize("Wingman 2", guard2, 1100, 900);
	Initialize("Wingman 3", guard3, 900, 1100);
	Initialize("Wingman 4", guard4, 900, 900);
	Initialize("Wall 1", block1, 1000, 600);
	Initialize("Wall 2", block2, 1000, 1400);
	Initialize("Wall 3", block3, 600, 1000);
	Initialize("Wall 4", block4, 1400, 1000);
	Initialize("Enemy", enemy1, 1000, 0);
	Initialize("Home Base", barrack1, 1000, 1000);
	Initialize("Home Base", barrack2, 200, 200);
	Initialize("Home Base", barrack3, 200, 1800);
	Initialize("Home Base", barrack4, 1800, 200);
	Initialize("Home Base", barrack5, 1800, 1800);
	Initialize("Scoreboard", scoreboard, 100, 50);
}

void TileData::LoadTile4()
{
	Tile* tile4 = new Tile();
	CurrentTile = tile4;

	Map* map = new Map("images/grass.png");
	Tank* tank = new Tank("images/tank2.png");
	DisplayBox* scoreboard = new DisplayBox(sf::Vector2i(100, 50), 150, 50);

	Initialize("Grass", map, 0, 0);
	Initialize("Tank", tank, 512, 512);
	Initialize("Scoreboard", scoreboard, 100, 50);
}

void TileData::LoadTile(int tile)
{
	switch (tile)
	{
		case 1:
		{
			LoadTile1();
			break;
		}
		case 2:
		{
			LoadTile2();
			break;
		}
		case 3:
		{
			LoadTile3();
			break;
		}
		case 4:
		{
			LoadTile4();
			break;
		}
	}
}

void TileData::Initialize(std::string name, VisibleGameObject* object, float x, float y)
{
	CurrentTile->TileObjects.Add(name, object);
	object->SetPosition(x, y);

	Entity* testE = dynamic_cast<Entity*>(object);
	if (testE != 0)
	{
		CurrentTile->EntityList.push_back(testE);
	}
}

Tile* TileData::CurrentTile;