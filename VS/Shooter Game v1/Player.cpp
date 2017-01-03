#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Projectile.h"
#include "Map.h"

Player::Player()
{
	Load("images/soldierAK.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 2);
	moveSpeed = 4;
	rotateSpeed = 4;
	highscore = 400;
	faction = Ally;

	healthMax = health = 1000;
}

Player::~Player()
{
}

void Player::Update(float deltaTime, sf::Event ev)
{
	float PI = 3.141592f;
	// Point in direction of mouse
	sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
	sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);

	float dx = mouseCoords.x - GetPosition().x;
	float dy = mouseCoords.y - GetPosition().y;

	if (dx == 0)
		dx = 0.0001f;

	float angle = atan(dy / dx) * 180 / PI;

	if (dx < 0)
	{
		angle += 180;
	}
	SetRotation(angle);

	// Moving
	float rotRad = GetRotation(false);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		SetPosition(GetPosition().x, GetPosition().y - moveSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		SetPosition(GetPosition().x, GetPosition().y + moveSpeed); 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetPosition(GetPosition().x - moveSpeed, GetPosition().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetPosition(GetPosition().x + moveSpeed, GetPosition().y);
	}

	// Shooting
	if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
	{
		Projectile* bullet = new Projectile("images/bullet.png", GetRotation(false), 10, Ally, 5);
		Game::GetObjectQueue().Add("bullet", bullet, "back");
		//                  20 is distance in front of player  | 6 is offset from center of player
		bullet->SetPosition(GetPosition().x + 20 * cos(rotRad) + 6 * cos(rotRad + 3.1415926f / 2), 
							GetPosition().y + 20 * sin(rotRad) + 6 * sin(rotRad + 3.1415926f / 2));
		bullet->SetRotation(GetRotation());
	}

	if (!Game::bossMode) // If there is no boss scroll the game screen with the player
	{
		// Reset map if player reaches coordinates
		if (GetPosition().y < -400)
		{
			Game::GetObjectManager().Shift();
			Map* map = dynamic_cast<Map*>(Game::GetObjectManager().Get("Map"));
			map->InitializeObjects(1);
			highscore = 400; // Resets the highscore back to original Y-coord
		}
		Game::viewY = std::min(GetPosition().y, 400.0f);
	}
	else
	{
		// Map will not reset until boss has died
		if (GetPosition().y < 0)
		{
		
		}
		Game::viewY = -400;
	}

	UpdateLifeBar(20, 50);

	// Add to scoreboard
	if (GetPosition().y < highscore) // Prevents the score from rising every time the player travels up;
	{								 // Score will only rise if position is higher than the previous highest
		Game::score += 1;
		highscore = GetPosition().y;
	}
	std::cout << "Player Position: " << GetPosition().y << std::endl;
}

void Player::Damage(float damage)
{
	health -= damage;
}