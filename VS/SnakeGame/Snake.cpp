#include "stdafx.h"
#include "Snake.h"
#include "Game.h"
#include "Apple.h"
#include "PowerUp.h"

Snake::Snake(std::string filename)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	currentDir = Right;

	sf::Sprite segment(_sprite);
	segment.setPosition(GetPosition());
	snakeList.push_back(segment);

	ArmorTexture.loadFromFile("images/armor.png");
	
	powerCount = 0;
}

Snake::~Snake()
{
}

void Snake::Update(float deltaTime, sf::Event ev)
{
	frameCount++;

	if (playerNum == 1)
	{
		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::W && currentDir != Down)
		{
			currentDir = Up;
		}
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::D && currentDir != Left)
		{
			currentDir = Right;
		}
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::S && currentDir != Up)
		{
			currentDir = Down;
		}
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::A && currentDir != Right)
		{
			currentDir = Left;
		}
		if (powerCount == 0 && GetSprite().getTexture() == &ArmorTexture)
		{
			GetSprite().setTexture(Game::texture1);
		}
	}
	else if (playerNum == 2)
	{
		if (Game::singlePlayer)
			return;

		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Up && currentDir != Down)
		{
			currentDir = Up;
		}
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Right && currentDir != Left)
		{
			currentDir = Right;
		}
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Down && currentDir != Up)
		{
			currentDir = Down;
		}
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Left && currentDir != Right)
		{
			currentDir = Left;
		}
		if (powerCount == 0 && GetSprite().getTexture() == &ArmorTexture)
		{
			GetSprite().setTexture(Game::texture2);
		}
	}
	
	if (fmod(frameCount, 5) == 0)
	{
		sf::Sprite segment(_sprite);
		if (currentDir == Up)
		{
			SetPosition(GetPosition().x, GetPosition().y - 20); // The sprite is not shown, but moved as an anchor
		}
		else if (currentDir == Right)
		{
			SetPosition(GetPosition().x + 20, GetPosition().y);
		}
		else if (currentDir == Down)
		{
			SetPosition(GetPosition().x, GetPosition().y + 20);
		}
		else if (currentDir == Left)
		{
			SetPosition(GetPosition().x - 20, GetPosition().y);
		}

		CheckWallCollision();
		
		segment.setPosition(GetPosition().x, GetPosition().y);
		snakeList.insert(snakeList.begin(), segment);

		CheckAppleCollision();

		CheckSelfCollision(); // Checks whether the snake hits itself

		CheckOtherCollision();
	}
	std::cout << powerCount << std::endl;
}

void Snake::CheckWallCollision()
{
	if (Game::wallDeath)
	{
		if (GetPosition().x > 800 || GetPosition().x < 0 || GetPosition().y > 800 || GetPosition().y < 0)
		{
			if (Game::singlePlayer)
			{
				Game::gameOverMessage = "Game Over";
			}
			else
			{
				Game::gameOverMessage = "Player " + std::to_string(playerNum % 2 + 1) + " Wins!";
			}
			Game::_gameState = Game::GameOver;
		}
	}
	else
	{
		if (GetPosition().x > 800)
			SetPosition(2, GetPosition().y);
		else if (GetPosition().x < 0)
			SetPosition(782, GetPosition().y);
		else if (GetPosition().y > 800)
			SetPosition(GetPosition().x, 2);
		else if (GetPosition().y < 0)
			SetPosition(GetPosition().x, 782);
	}
}

void Snake::CheckSelfCollision()
{
	std::vector<sf::Sprite>::iterator iter = snakeList.begin() + 1; // Don't bother checking itself
	while (iter != snakeList.end())
	{
		if (GetBoundingRect().intersects(iter->getGlobalBounds())) // If the front head intersects any other segment
		{
			if (Game::selfDeath)
			{
				if (Game::singlePlayer)
				{
					Game::gameOverMessage = "Game Over";
				}
				else
				{
					Game::gameOverMessage = "Player " + std::to_string(playerNum % 2 + 1) + " Wins!";
				}
				Game::_gameState = Game::GameOver;
				return;
			}
			else
			{ // Bisect yourself and spawn apples at the bisected part
				iter++;
				while (iter != snakeList.end())
				{
					Apple* apple = new Apple(texturefile, false);
					apple->GetSprite().setTexture(playerNum == 1 ? Game::texture1 : Game::texture2);
					apple->GetSprite().setColor(sf::Color(255, 255, 255, 128));
					apple->SetPosition(iter->getPosition().x, iter->getPosition().y);
					Game::GetObjectQueue().Add("Apple", apple, "front");

					iter = snakeList.erase(iter);
				}
			}
		}
		else
		{
			iter++;
		}
	}
}

void Snake::CheckAppleCollision()
{
	bool appleEaten = false;
	std::vector<Apple*>::iterator iterA = Game::appleList.begin();
	while (iterA != Game::appleList.end())
	{
		if (GetBoundingRect().intersects((*iterA)->GetBoundingRect()))
		{
			(*iterA)->Move();
			appleEaten = true;

			if (Game::extraLength == 1 && (*iterA)->texturefile == "images/apple.png") // Only apples trigger extra length
			{
				sf::Sprite segment(_sprite);
				sf::Sprite segment2(_sprite);
				if (currentDir == Up)
				{
					segment.setPosition(GetPosition().x, GetPosition().y + 20); // The sprite is not shown, but moved as an anchor
					segment2.setPosition(GetPosition().x, GetPosition().y + 40);
				}
				else if (currentDir == Right)
				{
					segment.setPosition(GetPosition().x - 20, GetPosition().y);
					segment2.setPosition(GetPosition().x - 40, GetPosition().y);
				}
				else if (currentDir == Down)
				{
					segment.setPosition(GetPosition().x, GetPosition().y - 20);
					segment2.setPosition(GetPosition().x, GetPosition().y - 40);
				}
				else if (currentDir == Left)
				{
					segment.setPosition(GetPosition().x + 20, GetPosition().y);
					segment2.setPosition(GetPosition().x + 40, GetPosition().y);
				}
				snakeList.insert(snakeList.end(), segment);
				snakeList.insert(snakeList.end(), segment2);
				snakeList.erase(snakeList.end() - 3);
			}
			if ((*iterA)->texturefile == "images/powerup.png")
			{
				GetSprite().setTexture(ArmorTexture);
				powerCount = 60;
			}
		}
		iterA++;
	}
		
	if (snakeList.size() > 0 && appleEaten == false)
		snakeList.erase(snakeList.end() - 1);
		
	if (snakeList.size() < 1)
		return;
}

void Snake::CheckOtherCollision()
{
	if (Game::singlePlayer || !Game::otherDeath) // None of the code runs if the game is singleplayer or playerAvoidance
		return;

	Snake* other = dynamic_cast<Snake*>(Game::GetObjectManager().Get("Player " + std::to_string(playerNum % 2 + 1)));
	std::vector<sf::Sprite>::iterator iter = other->snakeList.begin();
	while (iter != other->snakeList.end())
	{
		if (GetBoundingRect().intersects(iter->getGlobalBounds())) // If your head intersects any part of their body
		{
			if (powerCount > 0)
			{
				iter++;
				while (iter != other->snakeList.end())
				{
					Apple* apple = new Apple(texturefile, false);
					apple->GetSprite().setTexture(playerNum == 1 ? Game::texture2 : Game::texture1);
					apple->GetSprite().setColor(sf::Color(255, 255, 255, 128));
					apple->SetPosition(iter->getPosition().x, iter->getPosition().y);
					Game::GetObjectQueue().Add("Apple", apple, "front");

					iter = other->snakeList.erase(iter);
				}
			}
			else if (iter == other->snakeList.begin())
			{
				if (powerCount > 0)
				{
					Game::gameOverMessage = "Player " + std::to_string(playerNum) + " Wins!";
				}
				else if (other->powerCount > 0)
				{
					Game::gameOverMessage = "Player " + std::to_string(playerNum % 2 + 1) + " Wins!";
				}
				else
				{
					Game::gameOverMessage = "Tie!";
				}
				Game::_gameState = Game::GameOver;
				return;
			}
			else
			{
				Game::gameOverMessage = "Player " + std::to_string(playerNum % 2 + 1) + " Wins!";
				Game::_gameState = Game::GameOver;
				return;
			}
		}
		else
		{
			iter++;
		}
	}
	if (powerCount > 0)
	{
		powerCount--;
	}
	else
	{
		GetSprite().setTexture(playerNum == 1 ? Game::texture1 : Game::texture2);
	}
}

void Snake::Draw(sf::RenderWindow& rw)
{
	if (playerNum == 2 && Game::singlePlayer)
	{
		return;
	}

	std::vector<sf::Sprite>::iterator iter = snakeList.begin();
	while (iter != snakeList.end())
	{
		if (Game::transparent)
		{
			if (iter == snakeList.begin())
			{
				rw.draw(*iter);
				iter++;
			}
			else
			{
				iter->setColor(sf::Color(255, 255, 255, (255 - (float(iter - snakeList.begin()) / float(snakeList.size())) * 205)));
				rw.draw(*iter);
				iter++;
			}
		}
		else
		{
			rw.draw(*iter);
			iter++;
		}
	}
	//rw.draw(_sprite); // The sprite is not drawn, but still necessary as a position setter for the first head
}

/*
Called before every game
*/
void Snake::Reset()
{
						   // 01234567
	char num = name[7];    // Player 1
	playerNum = num - '0'; 

	if (playerNum == 1)
	{
		SetPosition(42, 42);
		GetSprite().setTexture(Game::texture1);
		currentDir = Right;
	}
	else
	{
		SetPosition(762, 762);
		GetSprite().setTexture(Game::texture2);
		currentDir = Left;
	}
	powerCount = 0;
	snakeList.clear();
	sf::Sprite segment(_sprite);
	snakeList.push_back(segment);
}