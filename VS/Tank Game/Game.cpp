#include "stdafx.h"
#include "Game.h"
#include "Tank.h"
#include "DisplayBox.h"
#include "LoseScreen.h"
#include "PauseScreen.h"
#include "TileData.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Tank Game");
	_mainWindow.setFramerateLimit(60);

	viewX = 512;
	viewY = 512;
	viewH = SCREEN_HEIGHT;
	viewW = SCREEN_WIDTH;

	_view.setCenter(sf::Vector2f(viewX, viewY));
	_view.setSize(sf::Vector2f(viewW, viewH));
	_mainWindow.setView(_view);

	_gameState = ShowingWorld;

	LoadFonts();

	/*_tileData.LoadTile1(); // Initial loading of data

	_gameObjectManager = TileData::CurrentTile->TileObjects;
	EntityList = TileData::CurrentTile->EntityList;
	EnemyList = TileData::CurrentTile->EnemyList;
	AllyList = TileData::CurrentTile->AllyList;*/

	score = 0;

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
			_gameObjectManager.UpdateAll(currentEvent); // Most important lines of code:
			_gameObjectManager.DrawAll(_mainWindow);    // They update and draw all sprites

			TransferQueue(); // Moves all items from the object queue to the object manager

			DisplayBox* scoreboard = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Scoreboard"));
			scoreboard->SetMessage(std::to_string(score));
			
			_mainWindow.display();
			break;
		}
		case Paused:
		{
			_pauseScreen.Show(_mainWindow, currentEvent);
			break;
		}
		case Talking:
		{
			_gameState = Playing;
			break;
		}
		case ShowingWorld:
		{
			viewX = 512;
			viewY = 512;
			_worldScreen.Show(_mainWindow, currentEvent);
			break;
		}
		case GameOver:
		{
			LoseScreen screen;
			screen.ShowScreen(_mainWindow, currentEvent);
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
	if (currentEvent.type == sf::Event::Resized)
    {
        // update the view to the new size of the window
       viewW = (float)currentEvent.size.width;
	   viewH = (float)currentEvent.size.height;
	   _view.setSize(viewW, viewH);
    }

	_view.setCenter(viewX, viewY); // Adjusts the center of the view
	_mainWindow.setView(_view); // Applies view
}

void Game::SwitchTile()
{
	_gameObjectManager = TileData::CurrentTile->TileObjects;
	EntityList = TileData::CurrentTile->EntityList;
	EnemyList = TileData::CurrentTile->EnemyList;
	AllyList = TileData::CurrentTile->AllyList;
}

void Game::TransferQueue()
{
	std::vector<std::pair<std::pair<std::string, VisibleGameObject*>, std::string>>::iterator i = _objectQueue._queue.begin();
	while (i != _objectQueue._queue.end())
	{
		if (i->second == "front")
			_gameObjectManager.AddF(i->first.first, i->first.second);
		else if (i->second == "back")
			_gameObjectManager.Add(i->first.first, i->first.second);
		else
			std::cout << "Error transferring objects from queue to manager" << std::endl;

		i = _objectQueue._queue.erase(i);
	}
}

void Game::LoadFonts()
{
	regular.loadFromFile("fonts/regular.ttf");
}

sf::Font& Game::GetFont(std::string fontname)
{
	if (fontname == "regular")
		return regular;
	else
		return regular;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

GameObjectManager& Game::GetObjectManager()
{
	return _gameObjectManager;
}

ObjectQueue& Game::GetObjectQueue()
{
	return _objectQueue;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
sf::View Game::_view;
GameObjectManager Game::_gameObjectManager;
ObjectQueue Game::_objectQueue;
PauseScreen Game::_pauseScreen;
WorldScreen Game::_worldScreen;
TileData Game::_tileData;
std::vector<Entity*> Game::EntityList;
std::vector<Entity*> Game::EnemyList;
std::vector<Entity*> Game::AllyList;
sf::Font Game::regular;

float Game::viewX;
float Game::viewY;
float Game::viewH;
float Game::viewW;

int Game::score;