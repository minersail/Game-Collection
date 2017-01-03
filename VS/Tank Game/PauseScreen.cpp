#include "stdafx.h"
#include "PauseScreen.h"
#include "Game.h"
#include "Soldier.h"
#include "Tank.h"

PauseScreen::PauseScreen()
	: ResumeButton(sf::Vector2i(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2 + 300), 280, 100),
	ReinforceButton(sf::Vector2i(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2 + 100), 280, 100),
	SwarmButton(sf::Vector2i(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2 - 100), 280, 100),
	WorldButton(sf::Vector2i(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2 - 300), 280, 100)
{
	Load("images/pausemenu.png");
	assert(IsLoaded());
	texturefile = "images/pausemenu.png";

	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	SetPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);

	// Create a mostly-transparent grey background to layer over paused game screen, creating fade effect
	bgtexture.loadFromFile("images/blank.png");
	background.setTexture(bgtexture);
	background.setColor(sf::Color(100, 100, 100, 5));
	background.setTextureRect(sf::Rect<int>(0, 0, 2048, 2048));

	ResumeButton.SetMessage("Resume");
	ReinforceButton.SetMessage("Reinforce");
	SwarmButton.SetMessage("Swarm");
	WorldButton.SetMessage("World");
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::Show(sf::RenderWindow& rw, sf::Event ev)
{
	rw.setFramerateLimit(6);

	sf::Vector2f adjustedPos = Game::GetWindow().mapPixelToCoords(sf::Vector2i(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2)); // Transfer the world coordinates to screen coordinates
	SetPosition(adjustedPos);

	rw.draw(background); // Draw the fade effect
	rw.draw(_sprite);
	ResumeButton.Draw(rw);
	ReinforceButton.Draw(rw);
	SwarmButton.Draw(rw);
	WorldButton.Draw(rw);

	if (ResumeButton.Clicked(ev))
	{
		rw.setFramerateLimit(60);
		Game::_gameState = Game::Playing;
		return;
	}
	else if (ReinforceButton.Clicked(ev))
	{
		Tank* tank = dynamic_cast<Tank*>(Game::GetObjectManager().Get("Tank"));

		for (int i = 1; i <= 4; i++)
		{
			Soldier* ally = new Soldier("images/allysoldier.png", 100, Entity::Ally);
			Game::GetObjectQueue().Add("ally" + std::to_string(i), ally, "back");
			Game::EntityList.push_back(ally);
			ally->SetPosition(tank->GetPosition().x + (i * 20 - 50), tank->GetPosition().y - (i * 20 - 50));
		}

		rw.setFramerateLimit(60);
		Game::_gameState = Game::Playing;
		return;
	}
	else if (SwarmButton.Clicked(ev))
	{
		for (int i = 1; i <= 10; i++)
		{
			Soldier* enemy = new Soldier("images/soldier.png", 30, Entity::Enemy);
			Game::GetObjectQueue().Add("enemy" + std::to_string(i), enemy, "back");
			Game::EntityList.push_back(enemy);
			enemy->SetPosition(rand() % 2048, rand() % 2048);
		}

		rw.setFramerateLimit(60);
		Game::_gameState = Game::Playing;
		return;
	}
	else if (WorldButton.Clicked(ev))
	{
		rw.setFramerateLimit(60);
		Game::_gameState = Game::ShowingWorld;
		return;
	}
	rw.display();
}