#pragma once
#include "stdafx.h"
#include "GameObjectManager.h"
#include "Button.h"
#include "MiniBoard.h"

class Game {
public:
	static void Start();
	static sf::RenderWindow& GetWindow(); // Returns game window
	static GameObjectManager& GetObjectManager(); // Returns _gameObjectManager
	// Enter an object into the gameobjectmanager and set its position
	static void Initialize(std::string name, VisibleGameObject* obj, float x, float y);
	// After a button is clicked, check if three buttons in a row have the same buttonstate
	static void CheckBoardWin();
	// After a board is won, check if three boards in a row have the same boardstate
	static void CheckGameWin();
	// Return true or false if three buttons' buttonstates are equal and store the state if they are equal in state
	// b1, b2, b3 are the numbers corresponding to specific tiles
	// state is to return the buttonstate by reference
	// Is overloaded to accept MiniBoard states as well
	static bool GetEqual(int b1, int b2, int b3, Button::ButtonState& state);
	static bool GetEqual(int b1, int b2, int b3, MiniBoard::BoardState& state);
	// Sets all buttonstates to blank
	static void ResetBoard();
	static void MoveToBoard(std::string newBoard);
	
	const static int SCREEN_HEIGHT = 900; // Screen dimensions
	const static int SCREEN_WIDTH = 1200; // Screen dimensions

	const static int BOARD_HEIGHT = 1525; // Game dimensions
	const static int BOARD_WIDTH = 1420; // Game dimensions

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

	static int score;
	static int player;
	// Boolean for whether or not all boards can be clicked, e.g. at beginning
	static bool allValid;

	static MiniBoard* currentBoard;

private:
	static bool IsExiting(); // Checks if exit event has been called
	static void GameLoop(); // Main game function
	static void LoadFonts(); // Load font(s)
	static void MoveView();

	static sf::RenderWindow _mainWindow; // main window. duh
	static sf::View _view; // the viewport
	static GameObjectManager _gameObjectManager; // GameObjectManager of current tile
};