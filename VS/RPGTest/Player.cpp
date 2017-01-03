#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player(float initX, float initY, std::string textureID, std::string name)
	: Character(initX, initY, textureID, name)
{
	keyPressed = None;
	frameCount = 0;
}

Player::~Player()
{
}

void Player::Update(float deltaTime, sf::Event ev)
{
	//std::cout << PlayerInventory.GetItems().size() << std::endl;
	UpdateChunk();

	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
	{
		Game::GetInventoryManager().SetQuestGiver(NULL);
		Game::_gameState = Game::Inventory;
		return;
	}

	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::W)
	{
		keyPressed = Up;
	}
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::A)
	{
		keyPressed = Left;
	}
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::S)
	{
		keyPressed = Down;
	}
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::D)
	{
		keyPressed = Right;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (keyPressed == None || keyPressed == Up)
		{
			Walk(Up);
			keyPressed = Up;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (keyPressed == None || keyPressed == Down)
		{
			Walk(Down);
			keyPressed = Down;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (keyPressed == None || keyPressed == Left)
		{
			Walk(Left);
			keyPressed = Left;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (keyPressed == None || keyPressed == Right)
		{
			Walk(Right);
			keyPressed = Right;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Walk(None);
		keyPressed = None;
	}

	if (collided)
	{
		collided = false;
	}

	// Set the game's view to be on Joe, but not move off screen
	Game::SetView(std::max(float(Game::SCREEN_WIDTH / 2), std::min(float(Game::SCREEN_WIDTH * Game::XCHUNKS - Game::SCREEN_WIDTH / 2), GetPosition().x)), 
				  std::max(float(Game::SCREEN_HEIGHT / 2), std::min(float(Game::SCREEN_HEIGHT * Game::YCHUNKS - Game::SCREEN_HEIGHT / 2), GetPosition().y)));
}

Inventory& Player::GetInventory()
{
	return PlayerInventory;
}