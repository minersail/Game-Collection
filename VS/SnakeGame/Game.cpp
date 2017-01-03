#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Snake.h"
#include "Apple.h"
#include "Snake.h"
#include "PowerUp.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Snake");
	_mainWindow.setFramerateLimit(60);

	srand(time(0));

	Map* map = new Map("images/gridBG.png");
	Snake* snake = new Snake("images/snakeblue.png");
	Snake* snake2 = new Snake("images/snakeorange.png");
	Apple* apple = new Apple("images/apple.png", true);
	PowerUp* powerup = new PowerUp("images/powerup.png");

	Initialize("Map", map, 0, 0);
	Initialize("Player 1", snake, 42, 42);
	Initialize("Player 2", snake2, 762, 762);
	Initialize("Apple 1", apple, (rand() % 40) * 20 + 2, (rand() % 40) * 20 + 2);
	Initialize("PowerUp 1", powerup, (rand() % 40) * 20 + 2, (rand() % 40) * 20 + 2);

	snake2->currentDir = Snake::Left;

	LoadFonts();

	score = 0;
	player = 1;
	clicks = 0;

	singlePlayer = true;
	selfDeath = true;
	wallDeath = true;
	otherDeath = true;
	transparent = false;
	extraLength = 0;

	_gameState = Paused;

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
			
			TransferQueue();

			_mainWindow.display();
			break;
		}
		case Paused:
		{
			_pauseScreen.SelectScreen(currentEvent, _mainWindow);
			_mainWindow.display();
			break;
		}
		case GameOver:
		{
			DisplayBox GameOverBox(sf::Vector2i(400, 400), 400, 100, "images/displaybox.png", gameOverMessage, false);

			_gameObjectManager.DrawAll(_mainWindow);			
			GameOverBox.Draw(_mainWindow);

			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Space)
			{
				Snake* p1 = dynamic_cast<Snake*>(_gameObjectManager.Get("Player 1"));
				Snake* p2 = dynamic_cast<Snake*>(_gameObjectManager.Get("Player 2"));

				p1->Reset();
				p2->Reset();

				_gameState = Paused;
			}

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

		Apple* testA = dynamic_cast<Apple*>(i->first.second);
		if (testA != NULL)
		{
			appleList.push_back(testA);
		}

		i = _objectQueue._queue.erase(i);
	}
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

ObjectQueue& Game::GetObjectQueue()
{
	return _objectQueue;
}

void Game::Initialize(std::string name, VisibleGameObject* obj, float x, float y)
{
	_gameObjectManager.Add(name, obj);
	obj->SetPosition(x, y);

	Apple* testA = dynamic_cast<Apple*>(obj);
	if (testA != NULL)
	{
		appleList.push_back(testA);
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
ObjectQueue Game::_objectQueue;
PauseScreen Game::_pauseScreen;
sf::Font Game::regular;
sf::Texture Game::texture1;
sf::Texture Game::texture2;

int Game::score;
int Game::player;
int Game::clicks;

bool Game::singlePlayer;
bool Game::selfDeath;
bool Game::wallDeath;
bool Game::otherDeath;
bool Game::transparent;
int Game::extraLength;
std::string Game::gameOverMessage;

std::vector<Apple*> Game::appleList;