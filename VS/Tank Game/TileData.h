#pragma once
#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Tile.h"
#include "Tank.h"
#include "AITank.h"
#include "Spawner.h"
#include "Spawner.cpp"

class TileData {
public:
	TileData();
	~TileData();

	const static int SCREEN_HEIGHT = 1024;
	const static int SCREEN_WIDTH = 1024;
	static Tile* CurrentTile; // The tile that currently has all the objects on screen

	static void TileData::Initialize(std::string name, VisibleGameObject* object, float x, float y);

	static void LoadTile(int tile); // Function taking in tile num and loading that tile
	
	static void LoadTile1(); // Load Tile 1
	static void LoadTile2(); // Load Tile 2
	static void LoadTile3(); // Summon Magic Unicorns -_-  What do you think this does
	static void LoadTile4(); // Load Tile 4
};