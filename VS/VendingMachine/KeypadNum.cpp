#include "stdafx.h"
#include "KeypadNum.h"
#include "Game.h"
#include "Button.h"

KeypadNum::KeypadNum(std::string name, float width, float height)
{
	Load("images/" + name + ".png");
	assert(IsLoaded());
	texturefile = "images/" + name + ".png";

	text1.loadFromFile("images/" + name + ".png");
	text2.loadFromFile("images/" + name + "press.png");
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);

	SetBoxSize(width, height);

	num = name;
}

void KeypadNum::Update(float deltaTime, sf::Event ev)
{
	sf::Vector2i mouseCoords = sf::Mouse::getPosition(Game::GetWindow());

	if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
	{
		if (_sprite.getGlobalBounds().contains(mouseCoords.x, mouseCoords.y)) 
		{
			_sprite.setTexture(text2);
			if (num == "x")
			{
				Game::keypadNum = "";
			}
			else if (num == "v")
			{
				if (Game::keypadNum.length() < 3)
				{
					Game::keypadNum = "ERR";
				}
				else
				{
					int first = Game::keypadNum[0] - '0'; // convert from character to integer
					int second = Game::keypadNum[1] - '0';
					int third = Game::keypadNum[2] - '0';

					// Check for valid inputs; All valid inputs are in the form X0Y, with X < 5 and Y being odd
					if (first > 5 || second != 0 || third % 2 != 1)
					{
						Game::keypadNum = "ERR";
					}
					else
					{
						if (Game::balance >= 99)
						{
							int buttonID = (first - 1) * 5 + (third + 1) / 2;
							Button* button = dynamic_cast<Button*>(Game::GetObjectManager().Get("Chip " + std::to_string(buttonID)));
							if (button->currentState == Button::Stocked)
							{
								button->currentState = Button::Vending;
								button->frameCount = 0; // Set the frameCount to 0 to count to 90
								Game::keypadNum = "VEND";
							}
							else
							{
								Game::keypadNum = "ERR";
							}
						}
						else
						{
							Game::keypadNum = "$.99";
						}
					}
				}
			}
			else
			{
				if (Game::keypadNum == "VEND" || Game::keypadNum == "ERR" || Game::keypadNum == "$.99")
				{
					Game::keypadNum = "";
				}

				if (Game::keypadNum.length() < 3)
				{
					Game::keypadNum += num;
				}
			}
		}
	}
	else if (ev.type == sf::Event::MouseButtonReleased)
	{
		_sprite.setTexture(text1);
	}
}

void KeypadNum::Draw(sf::RenderWindow& window)
{
	window.draw(_sprite);
}
