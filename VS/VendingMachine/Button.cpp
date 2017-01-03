#include "stdafx.h"
#include "Button.h"
#include "Game.h"

Button::Button(std::string filename, float width, float height)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	SetBoxSize(width, height);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	coilTexture.loadFromFile("images/coil.png");
	coil.setTexture(coilTexture);
	coil.setOrigin(coil.getTextureRect().width / 2, coil.getTextureRect().height / 2);
	
	chip2Texture.loadFromFile(filename);
	chip2.setTexture(chip2Texture);

	float currW = GetTextureRect().width;
	float currH = GetTextureRect().height;

	float scaleX = width / currW;
	float scaleY = height / currH;

	chip2.scale(scaleX, scaleY);

	chip2.setOrigin(chip2.getTextureRect().width / 2, chip2.getTextureRect().height / 2);

	currentState = Stocked;
	stock = 3;
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& rw)
{
	if (currentState == Stocked)
	{
		rw.draw(_sprite);
	}
	else if (currentState == Vending)
	{
		coil.setRotation(coil.getRotation() + 5);
		rw.draw(_sprite);
		rw.draw(chip2);
	}
	else if (currentState == Message)
	{
		text.setPosition(GetPosition().x - 100, GetPosition().y - 25);
		rw.draw(text);
	}

	if (currentState != Message) // Don't want coils appearing on top of message buttons
	{
		rw.draw(coil);
	}
}

void Button::Update(float deltaTime, sf::Event ev)
{
	frameCount++;

	if (currentState == Stocked)
	{
		coil.setPosition(GetPosition().x, GetPosition().y + (GetBoundingRect().height - coil.getLocalBounds().height) / 2);
		if (stock != 1)
			chip2.setPosition(GetPosition().x, GetPosition().y);
	}

	//////////////////   Enable for insta-click vending
	/*if (Clicked(ev))
	{
		if (currentState == Stocked)
		{
			currentState = Vending;
			frameCount = 0; // Set the frameCount to 0 to count to 90
		}
	}*/
	
	if (currentState == Vending)
	{
		if (frameCount >= 90)
		{
			Fall();
		}
	}
}

bool Button::Clicked(sf::Event ev)
{
	if (ev.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
		sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);
		if (GetBoundingRect().contains(mouseCoords.x, mouseCoords.y))
		{
			return true;
		}
	}
	return false;
}

void Button::Fall()
{
	if (stock != 1)
	{
		if (chip2.getRotation() != 180)
		{
			chip2.setRotation(chip2.getRotation() + 5);
		}
		else
		{
			chip2.setPosition(chip2.getPosition().x, chip2.getPosition().y + 5);
			if (chip2.getPosition().y > 550)
			{
				stock--;
				Game::score += 500;
				Game::balance -= 99;
				if (stock == 0)
				{
					currentState = Unstocked;
				}
				else
				{
					currentState = Stocked;
					chip2.setRotation(0);
				}
			}
		}
	}
	else
	{
		if (GetRotation() != 180)
		{
			SetRotation(GetRotation() + 5);
		}
		else
		{
			SetPosition(GetPosition().x, GetPosition().y + 5);
			if (GetPosition().y > 550)
			{
				stock--;
				Game::score += 500;
				Game::balance -= 99;
				if (stock == 0)
				{
					currentState = Unstocked;
				}
				else
				{
					currentState = Stocked;
				}
			}
		}
	}
}

void Button::SetActive(bool makeActive)
{
	if (makeActive)
		_sprite.setColor(sf::Color(255, 255, 255));
	else
		_sprite.setColor(sf::Color(128, 128, 128));
}