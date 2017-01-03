#include "stdafx.h"
#include "Boss.h"
#include "Game.h"
#include "Player.h"

Boss::Boss(std::string filename)
	: LTurret("images/turret1.png", Enemy, Projectile::Straight), 
	RTurret("images/turret1.png", Enemy, Projectile::Straight)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 2);
	faction = Enemy;
	frameCount = 0;
	targetLocation = 400;

	Game::EntityList.push_back(&LTurret);
	Game::EntityList.push_back(&RTurret);
}

Boss::~Boss()
{
}

void Boss::Destroy()
{
}

void Boss::Update(float deltaTime, sf::Event ev)
{
	frameCount++;
	sf::Vector2f coords = Game::GetWindow().mapPixelToCoords(sf::Vector2i(0, -600)); // Only care about y

	if (fmod(frameCount, 60) == 0)
	{
		targetLocation = rand() % 400 + 200; // Every second generate a random x-coord for the boss to move to
	}
	
	int newX;
	if (abs(GetPosition().x - targetLocation) > 3) // If it is more than three away from its destination
	{
		newX = GetPosition().x > targetLocation ? GetPosition().x - 3 : GetPosition().x + 3;
	}
	else
	{
		newX = (GetPosition().x + targetLocation) / 2; // Move halfway to the target location
	}
	SetPosition(newX, coords.y);

	// Turrets are not part of game loop and so have to be controlled updated in the boss' update function
	LTurret.SetPosition(GetPosition().x - 100, GetPosition().y - 50);
	RTurret.SetPosition(GetPosition().x + 100, GetPosition().y - 50);

	if (LTurret.pendingDestruction != true)
	{
		LTurret.Update(deltaTime, ev);
	}
	else
	{
		RemoveFromList(&LTurret, Game::EntityList);
	}

	if (RTurret.pendingDestruction != true)
	{
		RTurret.Update(deltaTime, ev);
	}
	else
	{
		RemoveFromList(&RTurret, Game::EntityList);
	}

	if (LTurret.pendingDestruction == true && RTurret.pendingDestruction == true)
	{
		static int first; // Static in this sense means that local variables can retain their value
		if (first++ == 0)	  // even after going out of scope and being re-initialized
		{
			Game::EntityList.push_back(this); // Meaning that this will only run the first time the if statement returns true
		}
	}
	std::cout << "Boss Position: " << GetPosition().y << std::endl;
}

void Boss::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	if (LTurret.pendingDestruction != true)
	{
		LTurret.Draw(rw);
	}
	if (RTurret.pendingDestruction != true)
	{
		RTurret.Draw(rw);
	}
}