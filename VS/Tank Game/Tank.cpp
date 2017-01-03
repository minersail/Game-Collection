#include "stdafx.h"
#include "Tank.h"
#include "Game.h"
#include "Soldier.h"
#include "TileData.h"
#include <cmath>

Tank::Tank(std::string filename)
	: MainTurret("images/turret2.png")
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	speed = 4;
	health = 1500;
	healthMax = 1500;
	faction = Ally;
	infantry = false;

	TileData::CurrentTile->AllyList.push_back(this);
}

Tank::~Tank()
{
}

void Tank::Update(float deltaTime, sf::Event ev)
{
	// Moving
	float rotRad = GetRotation() / 180 * 3.141592f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		SetPosition(GetPosition().x + speed * cos(rotRad), GetPosition().y + speed * sin(rotRad));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		SetPosition(GetPosition().x - speed * cos(rotRad), GetPosition().y - speed * sin(rotRad)); 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		SetRotation(GetRotation() - 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		SetRotation(GetRotation() + 1);
	}

	// Collision damage
	std::vector<Entity*>::iterator iter = Game::EnemyList.begin();
	while (iter != Game::EnemyList.end())
	{
		if ((*iter)->texturefile != "images/ghostsoldier.png" && (*iter)->infantry == true)
		{
			if (GetBoundingRect().intersects((*iter)->GetBoundingRect()))
			{
				if (CheckForCollision(*iter))
				{
					(*iter)->Damage(5);
				}
			}
		}
		iter++;
	}

	// Spawn your own minions with space!
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
	{
		Soldier* ally = new Soldier("images/allysoldier.png", 100, Ally);
		Game::GetObjectQueue().Add("ally", ally, "back");
		Game::EntityList.push_back(ally);
		ally->SetPosition(GetPosition().x + 30, GetPosition().y + 30);
	}

	// Spawn your own enemies with E!
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::E)
	{
		Soldier* enemy = new Soldier("images/soldier.png", 30, Enemy);
		Game::GetObjectQueue().Add("enemy", enemy, "back");
		Game::EntityList.push_back(enemy);
		enemy->SetPosition(GetPosition().x + 100, GetPosition().y + 100);
	}

	MainTurret.SetPosition(GetPosition().x, GetPosition().y);
	MainTurret.Update(deltaTime, ev);

	if (GetPosition().x > Game::viewW / 2 && GetPosition().x < 2048 - Game::viewW / 2)
		Game::viewX = GetPosition().x;
	if (GetPosition().y > Game::viewH / 2 && GetPosition().y < 2048 - Game::viewH / 2)
		Game::viewY = GetPosition().y;

	LifeBar.SetPosition(GetPosition().x - 25, GetPosition().y - 50);
	LifeBar.SetHealth(health, healthMax);
}

void Tank::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	rw.draw(MainTurret.GetSprite());
	LifeBar.Draw(rw);
}

void Tank::Damage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		Game::viewX = 512;
		Game::viewY = 512;
		Game::_gameState = Game::GameOver;
	}
}