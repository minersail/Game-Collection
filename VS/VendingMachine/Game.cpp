#include "stdafx.h"
#include "Game.h"
#include "Button.h"
#include "Background.h"
#include "Wallet.h"
#include "Keypad.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Vending Machine Simulator");
	_mainWindow.setFramerateLimit(60);

	srand(time(0));

	Background* board = new Background("images/machine.png");
	Initialize("Background", board, 0, 0);

	std::vector<std::string> chipList;
	chipList.push_back("images/cheetos.png");
	chipList.push_back("images/cheetosflaming.png");
	chipList.push_back("images/fritos.png");
	chipList.push_back("images/laysclassic.png");
	chipList.push_back("images/laysSC&O.png");
	chipList.push_back("images/laysbbq.png");
	chipList.push_back("images/laysbaked.png");
	chipList.push_back("images/sunchipscheddar.png");
	chipList.push_back("images/doritosnacho.png");
	chipList.push_back("images/doritoscoolranch.png");
	chipList.push_back("images/popchips.png");
	
	const int COLUMN[5] = {400, 325, 250, 175, 100}; // X values
	const int ROW[5] = {335, 270, 185, 105, 22}; // Y values

	for (int i = 0; i < 25; i++)
	{
		Button* chip = new Button(chipList[rand() % chipList.size()], 70, 70);
		Initialize("Chip " + std::to_string(25 - i), chip, COLUMN[i % 5], ROW[i / 5]);
	}

	DisplayBox* moneyBox = new DisplayBox("images/displaymoney.png", sf::Vector2i(286, 562), 572, 100);
	DisplayBox* numBox = new DisplayBox("images/displaydigital.png", sf::Vector2i(520, 63), 75, 30);
	Wallet* wallet1 = new Wallet();
	Keypad* keypad = new Keypad();

	numBox->SetSize(20);

	const int ROW1 = 22;
	const int ROW2 = 105;
	const int ROW3 = 190;
	const int ROW4 = 270;
	const int ROW5 = 335;

	Initialize("Message Box", moneyBox, 0, 0);
	Initialize("Number Box", numBox, 0, 0);
	Initialize("Wallet", wallet1, 520, 433);
	Initialize("Keypad", keypad, 0, 0);

	LoadFonts();

	score = 0;
	keypadNum = "";
	balance = 0;
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
			
			DisplayBox* scoreboard = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));
			std::string balanceMessage = "Money: $" + std::to_string(balance / 100) + "." + std::to_string(balance % 100);
			if (balance % 100 < 10)
			{
				balanceMessage.insert(balanceMessage.length() - 1, "0");
			}
			scoreboard->SetMessage(balanceMessage);

			DisplayBox* numBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Number Box"));
			numBox->SetMessage(keypadNum);

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
std::string Game::keypadNum;
int Game::balance;