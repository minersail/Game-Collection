#include "stdafx.h"
#include "Game.h"
#include "Button.h"
#include "Map.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Tic Tac Toe");
	_mainWindow.setFramerateLimit(60);

	Map* board = new Map("images/board.png"); 
	Button* b1 = new Button(150, 150);
	Button* b2 = new Button(150, 150);
	Button* b3 = new Button(150, 150);
	Button* b4 = new Button(150, 150);
	Button* b5 = new Button(150, 150);
	Button* b6 = new Button(150, 150);
	Button* b7 = new Button(150, 150);
	Button* b8 = new Button(150, 150);
	Button* b9 = new Button(150, 150);
	Button* PlayAgain = new Button(512, 100);
	DisplayBox* messageBox = new DisplayBox(sf::Vector2i(256, 562), 512, 100);

	messageBox->SetMessage("Tic Tac Toe");
	PlayAgain->SetMessage("Play Again?");
	PlayAgain->currentState = Button::Message;
	PlayAgain->SetActive(false);

	Initialize("Background", board, 0, 0);
	Initialize("Button 1", b1, 100, 100);
	Initialize("Button 2", b2, 250, 100);
	Initialize("Button 3", b3, 400, 100);
	Initialize("Button 4", b4, 100, 250);
	Initialize("Button 5", b5, 250, 250);
	Initialize("Button 6", b6, 400, 250);
	Initialize("Button 7", b7, 100, 400);
	Initialize("Button 8", b8, 250, 400);
	Initialize("Button 9", b9, 400, 400);
	Initialize("Play Again", PlayAgain, 256, 662);
	Initialize("Message Box", messageBox, 0, 0);

	LoadFonts();

	score = 0;
	player = 1;
	clicks = 0;
	_gameState = Playing;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch (_gameState)
	{
		case Playing:
		{
			_mainWindow.clear();
			_gameObjectManager.UpdateAll(currentEvent); // Most important lines of code:
			_gameObjectManager.DrawAll(_mainWindow);    // They update and draw all sprites
			
			_mainWindow.display();
			break;
		}
		case Paused:
		{
			_gameState = Playing;
			break;
		}
		case GameOver:
		{
			Button* PlayAgain = static_cast<Button*>(_gameObjectManager.Get("Play Again"));
			PlayAgain->SetActive(true);

			if (PlayAgain->Clicked(currentEvent))
			{
				ResetBoard();
				PlayAgain->SetActive(false);

				_gameState = Playing;
			}

			_gameObjectManager.DrawAll(_mainWindow);
			_mainWindow.display();
			break;
		}
	}

	if (currentEvent.type == sf::Event::Closed)
		_gameState = Exiting;
	if (currentEvent.type == sf::Event::KeyPressed)
	{
		if (currentEvent.key.code == sf::Keyboard::Escape)
			_gameState = Paused;
	}
}

void Game::CheckForWin()
{
	bool winner = false;
	DisplayBox* messageBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));

	Button::ButtonState state;
	if (GetEqual(1, 2, 3, state))
	{
		winner = true;
	}
	else if (GetEqual(4, 5, 6, state))
	{
		winner = true;
	}
	else if (GetEqual(7, 8, 9, state))
	{
		winner = true;
	}
	else if (GetEqual(1, 4, 7, state))
	{
		winner = true;
	}
	else if (GetEqual(2, 5, 8, state))
	{
		winner = true;
	}
	else if (GetEqual(3, 6, 9, state))
	{
		winner = true;
	}
	else if (GetEqual(1, 5, 9, state))
	{
		winner = true;
	}
	else if (GetEqual(3, 5, 7, state))
	{
		winner = true;
	}
	if (winner)
	{
		if (state == Button::Circle)
		{
			messageBox->SetMessage("Circle Wins!");
			_gameState = GameOver;
			clicks = 0;
		}
		else if (state == Button::X)
		{
			messageBox->SetMessage("X Wins!");
			_gameState = GameOver;
			clicks = 0;
		}
	}
	if (clicks == 9)
	{
		messageBox->SetMessage("Tie!");
		_gameState = GameOver;
		clicks = 0;
	}
}

bool Game::GetEqual(int b1, int b2, int b3, Button::ButtonState& state)
{
	Button* button1 = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(b1)));
	Button* button2 = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(b2)));
	Button* button3 = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(b3)));

	if (button1->currentState == button2->currentState && button2->currentState == button3->currentState)
	{
		if (button1->currentState != Button::Blank)
		{
			state = button1->currentState;
			return true;
		}
	}
	state = Button::Blank;
	return false;
}

void Game::ResetBoard()
{
	for (int i = 1; i <= 9; i++)
	{
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(i)));
		button->currentState = Button::Blank;
	}
	player = 1;
	DisplayBox* messageBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));
	messageBox->SetMessage("Tic Tac Toe");
}

void Game::LoadFonts()
{
	regular.loadFromFile("fonts/regular.ttf");
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

GameObjectManager& Game::GetObjectManager()
{
	return _gameObjectManager;
}

void Game::Initialize(std::string name, VisibleGameObject* obj, float x, float y)
{
	_gameObjectManager.Add(name, obj);
	obj->SetPosition(x, y);
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::Font Game::regular;

int Game::score;
int Game::player;
int Game::clicks;