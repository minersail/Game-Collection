#include "stdafx.h"
#include "Game.h"
#include "Button.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	srand(time(0));
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Tic Tac Toe");
	_mainWindow.setFramerateLimit(60);

	Map* board = new Map("images/board.png"); 
	Button* b1 = new Button(150, 150, "images/button.png");
	Button* b2 = new Button(150, 150, "images/button.png");
	Button* b3 = new Button(150, 150, "images/button.png");
	Button* b4 = new Button(150, 150, "images/button.png");
	Button* b5 = new Button(150, 150, "images/button.png");
	Button* b6 = new Button(150, 150, "images/button.png");
	Button* b7 = new Button(150, 150, "images/button.png");
	Button* b8 = new Button(150, 150, "images/button.png");
	Button* b9 = new Button(150, 150, "images/button.png");
	Button* PlayAgain = new Button(512, 100, "images/button.png", "Play Again?");
	DisplayBox* messageBox = new DisplayBox(sf::Vector2i(256, 562), 512, 100, "images/displaybox.png", "Tic Tac Toe");

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
	turns = 0;
	ticks = 0;
	player = 1;
	_gameState = Paused;
	singleplayer = true;

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
			_pauseScreen.SelectScreen(currentEvent, _mainWindow);
			_mainWindow.display();
			break;
		}
		case AITurn:
		{
			DisplayBox* messageBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));
			messageBox->SetMessage("AI thinking...");
			ticks += 1;
			
			if (ticks == 60) // Make it look like the AI is taking time to think (it's not)
			{
				if (!WinMove())
				{
					if (!BlockMove())
					{
						RandomMove();
					}
				}
				messageBox->SetMessage("Tic Tac Toe");

				turns += 1;
				if (CheckForWin() == false) // Checks for win
				{
					Game::_gameState = Playing;
				}
				ticks = 0;
			}

			_mainWindow.clear();
			_gameObjectManager.DrawAll(_mainWindow);
			_mainWindow.display();
			break;
		}
		case GameOver:
		{
			Button* PlayAgain = dynamic_cast<Button*>(_gameObjectManager.Get("Play Again"));
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

bool Game::CheckForWin()
{
	bool winner = false;
	DisplayBox* messageBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));

	Button::ButtonState state;
	if (GetEqual(1, 2, 3, state) || GetEqual(4, 5, 6, state) || GetEqual(7, 8, 9, state) // Rows
		|| GetEqual(1, 4, 7, state) || GetEqual(2, 5, 8, state) || GetEqual(3, 6, 9, state) // Columns
		|| GetEqual(1, 5, 9, state) || GetEqual(3, 5, 7, state)) // Diagonals
	{
		winner = true;
	}

	if (winner)
	{
		if (state == Button::Circle)
		{
			messageBox->SetMessage("Circle Wins!");
			_gameState = GameOver;
			turns = 0;
		}
		else if (state == Button::X)
		{
			messageBox->SetMessage("X Wins!");
			_gameState = GameOver;
			turns = 0;
		}
		return true;
	}
	if (turns == 9)
	{
		messageBox->SetMessage("Tie!");
		_gameState = GameOver;
		turns = 0;
		return true;
	}
	return false;
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

bool Game::CheckRow(int b1, int b2, int b3, Button::ButtonState& state, int& blank)
{
	if (GetEqual(b1, b2, b3, state)) // If all three in the row are equal, then none or all are blank
	{
		return false;
	}
	Button* button1 = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(b1)));
	Button* button2 = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(b2)));
	Button* button3 = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(b3)));

	if (button1->currentState == button2->currentState && button3->currentState == Button::Blank)
	{
		state = button1->currentState;
		blank = b3;
		return true;
	}
	else if (button2->currentState == button3->currentState && button1->currentState == Button::Blank)
	{
		state = button2->currentState;
		blank = b1;
		return true;
	}
	else if (button1->currentState == button3->currentState && button2->currentState == Button::Blank)
	{
		state = button1->currentState;
		blank = b2;
		return true;
	}
	return false;
}

void Game::ResetBoard()
{
	for (int i = 1; i <= 9; i++)
	{
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(i)));
		button->currentState = Button::Blank;
	}

	DisplayBox* messageBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));
	messageBox->SetMessage("Tic Tac Toe");
}

bool Game::WinMove()
{
	Button::ButtonState state;
	int move = 0;
	if (CheckRow(1, 2, 3, state, move) && state == Button::X)
	{
		std::cout << "win1" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(4, 5, 6, state, move) && state == Button::X)
	{
		std::cout << "win2" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(7, 8, 9, state, move) && state == Button::X)
	{
		std::cout << "win3" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(1, 4, 7, state, move) && state == Button::X)
	{
		std::cout << "win4" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(2, 5, 8, state, move) && state == Button::X)
	{
		std::cout << "win5" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(3, 6, 9, state, move) && state == Button::X)
	{
		std::cout << "win6" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(1, 5, 9, state, move) && state == Button::X)
	{
		std::cout << "win7" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(3, 5, 7, state, move) && state == Button::X)
	{
		std::cout << "win8" << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	return false;
}

bool Game::BlockMove()
{
	Button::ButtonState state;
	int move = 0;
	if (CheckRow(1, 2, 3, state, move) && state == Button::Circle)
	{
		std::cout << 1 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(4, 5, 6, state, move) && state == Button::Circle)
	{
		std::cout << 2 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(7, 8, 9, state, move) && state == Button::Circle)
	{
		std::cout << 3 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(1, 4, 7, state, move) && state == Button::Circle)
	{
		std::cout << 4 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(2, 5, 8, state, move) && state == Button::Circle)
	{
		std::cout << 5 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(3, 6, 9, state, move) && state == Button::Circle)
	{
		std::cout << 6 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(1, 5, 9, state, move) && state == Button::Circle)
	{
		std::cout << 7 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	else if (CheckRow(3, 5, 7, state, move) && state == Button::Circle)
	{
		std::cout << 8 << std::endl;
		Button* button = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(move)));
		button->currentState = Button::X;
		return true;
	}
	return false;
}

void Game::RandomMove()
{
	int x = rand() % 9 + 1;

	Button* randomButton = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(x)));

	while (true)
	{
		if (randomButton->currentState == Button::Blank)
		{
			randomButton->currentState = Button::X;
			break;
		}
		else 
		{
			int x = rand() % 9 + 1;
			randomButton = dynamic_cast<Button*>(_gameObjectManager.Get("Button " + std::to_string(x)));
		}
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
PauseScreen Game::_pauseScreen;

int Game::score;
int Game::turns;
int Game::ticks;
int Game::player;
bool Game::singleplayer;
sf::Texture Game::text1;
sf::Texture Game::text2;