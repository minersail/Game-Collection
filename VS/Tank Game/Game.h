#pragma once
#include "stdafx.h"
#include "GameObjectManager.h"
#include "ObjectQueue.h"
#include "Entity.h"
#include "Block.h"
#include "PauseScreen.h"
#include "WorldScreen.h"

class TileData;

class Game {
public:
	static void Start();
	static sf::RenderWindow& GetWindow(); // Returns game window
	static GameObjectManager& GetObjectManager(); // Returns _gameObjectManager
	static ObjectQueue& GetObjectQueue(); // Returns object queue
	static sf::Font& GetFont(std::string fontname);
	// Takes data out of the currently loaded tile and puts it into the game loop
	static void SwitchTile();
	static void TransferQueue();

	const static int SCREEN_HEIGHT = 1024;
	const static int SCREEN_WIDTH = 1024;

	static float viewX;
	static float viewY;
	static float viewH;
	static float viewW;

	static sf::Font regular;

	enum GameState {
		Uninitialized, Paused, Talking,
		ShowingWorld, Playing, Exiting, GameOver
	};

	static GameState _gameState; // Current GameState
	static std::vector<Entity*> EntityList; // Holds all entities
	static std::vector<Entity*> EnemyList; // Holds list of all enemies
	static std::vector<Entity*> AllyList; // Holds list of all allies

	static TileData _tileData;

	static int score;

private:
	static bool IsExiting(); // Checks if exit event has been called
	static void GameLoop(); // Main game function
	static void LoadFonts();

	static sf::RenderWindow _mainWindow; // main window. duh
	static sf::View _view;
	static GameObjectManager _gameObjectManager; // GameObjectManager of current tile
	static ObjectQueue _objectQueue;
	static PauseScreen _pauseScreen;
	static WorldScreen _worldScreen;
};