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

	viewX = SCREEN_WIDTH / 2;
	viewY = SCREEN_HEIGHT / 2;
	viewH = SCREEN_HEIGHT;
	viewW = SCREEN_WIDTH;

	_view.setCenter(sf::Vector2f(viewX, viewY));
	_view.setSize(sf::Vector2f(viewW, viewH));

	Map* board = new Map("images/board.png"); 
	MiniBoard* b1 = new MiniBoard("images/miniboard.png");
	MiniBoard* b2 = new MiniBoard("images/miniboard.png");
	MiniBoard* b3 = new MiniBoard("images/miniboard.png");
	MiniBoard* b4 = new MiniBoard("images/miniboard.png");
	MiniBoard* b5 = new MiniBoard("images/miniboard.png");
	MiniBoard* b6 = new MiniBoard("images/miniboard.png");
	MiniBoard* b7 = new MiniBoard("images/miniboard.png");
	MiniBoard* b8 = new MiniBoard("images/miniboard.png");
	MiniBoard* b9 = new MiniBoard("images/miniboard.png");
	Button* PlayAgain = new Button(512, 100);
	DisplayBox* messageBox = new DisplayBox(sf::Vector2i(100, 100), 512, 100);

	messageBox->SetMessage("Tic Tac Toe");
	PlayAgain->SetMessage("Play Again?");
	PlayAgain->currentState = Button::Message;
	PlayAgain->SetActive(false);

	float POS1 = 8;
	float POS2 = 483;
	float POS3 = 958;

	Initialize("Background", board, 0, 0);
	Initialize("Board 1", b1, POS1, POS1);
	Initialize("Board 2", b2, POS2, POS1);
	Initialize("Board 3", b3, POS3, POS1);
	Initialize("Board 4", b4, POS1, POS2);
	Initialize("Board 5", b5, POS2, POS2);
	Initialize("Board 6", b6, POS3, POS2);
	Initialize("Board 7", b7, POS1, POS3);
	Initialize("Board 8", b8, POS2, POS3);
	Initialize("Board 9", b9, POS3, POS3);
	Initialize("Play Again", PlayAgain, 1425 / 2, 1475);
	Initialize("Message Box", messageBox, 0, 0);

	currentBoard = b1;
	allValid = true;

	LoadFonts();

	score = 0;
	player = 1;
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
			_mainWindow.clear(sf::Color(119, 67, 50));
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

	MoveView();

	_view.setCenter(viewX, viewY); // Adjusts the center of the view
	_mainWindow.setView(_view); // Applies view
}

void Game::CheckBoardWin()
{
	bool winner = false;
	DisplayBox* messageBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));
	if (player == 1)
	{
		messageBox->SetMessage("O's Turn");
	}
	else
	{
		messageBox->SetMessage("X's Turn");
	}

	Button::ButtonState state;
	if (GetEqual(1, 2, 3, state) || GetEqual(4, 5, 6, state) || GetEqual(7, 8, 9, state) || // Rows
		GetEqual(1, 4, 7, state) || GetEqual(2, 5, 8, state) || GetEqual(3, 6, 9, state) || // Columns
		GetEqual(1, 5, 9, state) || GetEqual(3, 5, 7, state)) // Diagonals
	{
		winner = true;
	}
	if (winner)
	{
		if (state == Button::Circle)
		{
			currentBoard->boardState = MiniBoard::OWin;
		}
		else if (state == Button::X)
		{
			currentBoard->boardState = MiniBoard::XWin;
		}
		CheckGameWin();
	}
}

void Game::CheckGameWin()
{
	bool winner = false;
	DisplayBox* messageBox = dynamic_cast<DisplayBox*>(_gameObjectManager.Get("Message Box"));

	MiniBoard::BoardState state;
	if (GetEqual(1, 2, 3, state) || GetEqual(4, 5, 6, state) || GetEqual(7, 8, 9, state) || // Rows
		GetEqual(1, 4, 7, state) || GetEqual(2, 5, 8, state) || GetEqual(3, 6, 9, state) || // Columns
		GetEqual(1, 5, 9, state) || GetEqual(3, 5, 7, state)) // Diagonals
	{
		winner = true;
	}
	if (winner)
	{
		if (state == MiniBoard::OWin)
		{
			messageBox->SetMessage("Circle Wins!");
			_gameState = GameOver;
		}
		else if (state == MiniBoard::XWin)
		{
			messageBox->SetMessage("X Wins!");
			_gameState = GameOver;
		}
	}
}

bool Game::GetEqual(int b1, int b2, int b3, Button::ButtonState& state)
{
	Button* button1 = currentBoard->GetButton(b1);
	Button* button2 = currentBoard->GetButton(b2);
	Button* button3 = currentBoard->GetButton(b3);

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

bool Game::GetEqual(int b1, int b2, int b3, MiniBoard::BoardState& state)
{
	MiniBoard* board1 = dynamic_cast<MiniBoard*>(_gameObjectManager.Get("Board " + std::to_string(b1)));
	MiniBoard* board2 = dynamic_cast<MiniBoard*>(_gameObjectManager.Get("Board " + std::to_string(b2)));
	MiniBoard* board3 = dynamic_cast<MiniBoard*>(_gameObjectManager.Get("Board " + std::to_string(b3)));
	
	if (board1->boardState == board2->boardState && board2->boardState == board3->boardState)
	{
		if (board1->boardState != MiniBoard::Blank)
		{
			state = board1->boardState;
			return true;
		}
	}
	state = MiniBoard::Blank;
	return false;
}

void Game::ResetBoard()
{
	for (int i = 1; i <= 9; i++)
	{
		MiniBoard* board = dynamic_cast<MiniBoard*>(_gameObjectManager.Get("Board " + std::to_string(i)));
		for (int i = 1; i <= 9; i++)
		{
			Button* button = board->GetButton(i);
			button->currentState = Button::Blank;
		}
	}
	player = 1;
}

void Game::MoveToBoard(std::string newBoard)
{
	MiniBoard* board = dynamic_cast<MiniBoard*>(_gameObjectManager.Get("Board " + newBoard));
	float xPos = board->GetPosition().x + 230; // MiniBoards are not centered at origin, thus offset
	float yPos = board->GetPosition().y + 230;
	float halfWidth = SCREEN_WIDTH / 2;
	float halfHeight = SCREEN_HEIGHT / 2;

	if (board->boardState != MiniBoard::XWin && board->boardState != MiniBoard::OWin)
	{
		board->boardState = MiniBoard::Selected;
		allValid = false;

		// Makes sure the views do not go off to the sides
		viewX = xPos < halfWidth ? std::max(halfWidth, xPos) : std::min(BOARD_WIDTH - halfWidth, xPos);
		viewY = yPos < halfHeight ? std::max(halfHeight, yPos) : std::min(BOARD_HEIGHT - halfHeight, yPos);
		currentBoard = board;
	}
	else
	{
		allValid = true;
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

void Game::MoveView()
{
	sf::Vector2i mouseCoords = sf::Mouse::getPosition(_mainWindow);
	if (mouseCoords.x > SCREEN_WIDTH - 100)
	{
		if (viewX < BOARD_WIDTH - SCREEN_WIDTH / 2)
			viewX += 20;
	}
	if (mouseCoords.x < 100)
	{
		if (viewX > SCREEN_WIDTH / 2)
			viewX -= 20;
	}
	if (mouseCoords.y > SCREEN_HEIGHT - 100)
	{
		if (viewY < BOARD_HEIGHT - SCREEN_HEIGHT / 2)
			viewY += 20;
	}
	if (mouseCoords.y < 100)
	{
		if (viewY > SCREEN_HEIGHT / 2)
			viewY -= 20;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::Font Game::regular;
sf::View Game::_view;
MiniBoard* Game::currentBoard;

int Game::score;
int Game::player;
bool Game::allValid;

float Game::viewX;
float Game::viewY;
float Game::viewH;
float Game::viewW;