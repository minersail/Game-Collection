#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Soldier.h"
#include "Player.h"
#include "DisplayBox.h"
#include "Boss.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Shooter Game");
	_mainWindow.setFramerateLimit(60);

	viewX = 400;
	viewY = 400;
	viewH = SCREEN_HEIGHT;
	viewW = SCREEN_WIDTH;

	_view.setCenter(sf::Vector2f(viewX, viewY));
	_view.setSize(sf::Vector2f(viewW, viewH));
	_mainWindow.setView(_view);

	_gameState = Playing;

	LoadFonts();

	Map* map = new Map("images/bg.png");
	Player* p1 = new Player();

	Initialize("Map", map, 0, -800);
	Initialize("Player", p1, 400, 400);

	map->InitializeObjects(0);
	map->InitializeObjects(1);

	DisplayBox temp(sf::Vector2i(50, 25), 100, 50);
	scoreboard = temp;

	score = 1; // Initialized at 1 instead of 0 because of modulus

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
			
			scoreboard.SetMessage(std::to_string(score));
			scoreboard.Draw(_mainWindow);
			_mainWindow.display();
			break;
		}
		case Paused:
		{
			break;
		}
		case Talking:
		{
			_gameState = Playing;
			break;
		}
		case ShowingWorld:
		{
			break;
		}
		case GameOver:
		{
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

		Entity* testE = dynamic_cast<Entity*>(i->first.second);
		Boss* testB = dynamic_cast<Boss*>(i->first.second);
		if (testE != NULL && testB == NULL) // Object is a non-boss entity
		{
			EntityList.push_back(testE);
			if (testE->faction == Entity::Enemy)
				Game::EnemyList.push_back(testE);
			else if (testE->faction == Entity::Ally)
				Game::AllyList.push_back(testE);
		}

		i = _objectQueue._queue.erase(i);
	}
}

void Game::Initialize(std::string name, VisibleGameObject* object, float x, float y)
{
	_gameObjectManager.Add(name, object);
	object->SetPosition(x, y);

	Entity* testE = dynamic_cast<Entity*>(object);
	if (testE != 0)
	{
		EntityList.push_back(testE);
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
DisplayBox Game::scoreboard;
std::vector<Entity*> Game::EntityList;
std::vector<Entity*> Game::EnemyList;
std::vector<Entity*> Game::AllyList;
sf::Font Game::regular;

float Game::viewX;
float Game::viewY;
float Game::viewH;
float Game::viewW;

int Game::score;
bool Game::bossMode;