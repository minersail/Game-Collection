#pragma once
#include "stdafx.h"
#include "GameObjectManager.h"
#include "Button.h"

class Game {
public:
	static void Start();
	static sf::RenderWindow& GetWindow(); // Returns game window
	static GameObjectManager& GetObjectManager(); // Returns _gameObjectManager
	// Enter an object into the gameobjectmanager and set its position
	static void Initialize(std::string name, VisibleGameObject* obj, float x, float y);
	// After a button is clicked, check if three in a row have the same buttonstate
	static void CheckForWin();
	// Return true or false if three buttons' buttonstates are equal and store the state if they are equal in state
	// b1, b2, b3 are the numbers corresponding to specific tiles
	// state is to return the buttonstate by reference
	static bool GetEqual(int b1, int b2, int b3, Button::ButtonState& state);
	// Sets all buttonstates to blank
	static void ResetBoard();

	const static int SCREEN_HEIGHT = 712;
	const static int SCREEN_WIDTH = 512;

	static sf::Font regular;

	enum GameState {
		Uninitialized, Paused, Talking,
		ShowingWorld, Playing, Exiting, GameOver
	};

	static GameState _gameState; // Current GameState

	static int score;
	static int player;
	static int clicks;

private:
	static bool IsExiting(); // Checks if exit event has been called
	static void GameLoop(); // Main game function
	static void LoadFonts(); // Load font(s)

	static sf::RenderWindow _mainWindow; // main window. duh
	static GameObjectManager _gameObjectManager; // GameObjectManager of current tile
};