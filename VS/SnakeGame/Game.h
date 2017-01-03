#pragma once
#include "stdafx.h"
#include "GameObjectManager.h"
#include "ObjectQueue.h"
#include "Apple.h"
#include "PauseScreen.h"

class Game {
public:
	static void Start();
	static sf::RenderWindow& GetWindow(); // Returns game window
	static GameObjectManager& GetObjectManager(); // Returns _gameObjectManager
	static ObjectQueue& GetObjectQueue(); // Returns _gameObjectManager
	// Enter an object into the gameobjectmanager and set its position
	static void Initialize(std::string name, VisibleGameObject* obj, float x, float y);
	static void TransferQueue();

	const static int SCREEN_HEIGHT = 800;
	const static int SCREEN_WIDTH = 800;

	static sf::Font regular;

	enum GameState {
		Uninitialized, Paused, Talking,
		ShowingWorld, Playing, Exiting, GameOver
	};

	static GameState _gameState; // Current GameState

	static int score;
	static int player;
	static int clicks;

	static std::vector<Apple*> appleList;

	static sf::Texture texture1;
	static sf::Texture texture2;

	static bool singlePlayer;
	static bool selfDeath;
	static bool wallDeath;
	static bool otherDeath;
	static bool transparent;
	static int extraLength;
	static std::string gameOverMessage;

private:
	static bool IsExiting(); // Checks if exit event has been called
	static void GameLoop(); // Main game function
	static void LoadFonts(); // Load font(s)

	static sf::RenderWindow _mainWindow; // main window. duh
	static GameObjectManager _gameObjectManager; // GameObjectManager of current tile
	static ObjectQueue _objectQueue; // ObjectQueue of current tile
	static PauseScreen _pauseScreen; // Pause screen
};