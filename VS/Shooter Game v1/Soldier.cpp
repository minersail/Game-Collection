#pragma once
#include "stdafx.h"
#include "Soldier.h"
#include "Game.h"
#include "Projectile.h"
#include "Item.h"
#include "RayCast.h"

Soldier::Soldier()
	: collided(false), traceDir(Uninitialized), LoS(true)
{
}

Soldier::Soldier(std::string filename, float life, Faction fac)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;
	
	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 6);
	health = healthMax = life;
	faction = fac;
	speed = 3;
	range = 300;
	collided = false;
	traceDir = Uninitialized;
	infantry = true;
	dispRect.height = (int)GetSpriteRect().height;
	dispRect.width = (int)GetSpriteRect().width;
	GetSprite().setTextureRect(dispRect);
	LifeBar.SetScale(0.5);

	if (fac == Enemy)
	{
		Game::EnemyList.push_back(this); // To initialize soldiers created during game loop
	}
	else if (fac == Ally)
	{
		Game::AllyList.push_back(this); // To initialize soldiers created during game loop
	}
}

Soldier::Soldier(const Soldier& obj)
{
	Load(obj.texturefile);
	texturefile = obj.texturefile;

	GetSprite().setOrigin(GetSpriteRect().width / 2, GetSpriteRect().height / 6);
	health = obj.health;
	healthMax = obj.healthMax;
	faction = obj.faction;
	speed = obj.speed;
	range = 300;
	collided = false;
	traceDir = Uninitialized;
	infantry = true;
	dispRect.height = (int)GetSpriteRect().height;
	dispRect.width = (int)GetSpriteRect().width;
	GetSprite().setTextureRect(dispRect);
	LifeBar.SetScale(0.5);

	if (faction == Enemy)
	{
		Game::EnemyList.push_back(this);
	}
	else if (faction == Ally)
	{
		Game::AllyList.push_back(this);
	}
	else
	{
		std::cout << "Faction entered that does not exist" << std::endl;
	}
}

Soldier::~Soldier()
{
	if (Game::_gameState != Game::Exiting)
	{
		if (texturefile != "images/ghostsoldier.png" && infantry)
		{
			// UNCOMMENT FOR GHOSTS
			/*Soldier* newSoldier = new Soldier("images/ghostsoldier.png", healthMax, faction);
			Game::GetObjectQueue().Add("Ghost Soldier", newSoldier, "front");
			Game::EntityList.push_back(newSoldier);
			newSoldier->SetPosition(GetPosition());*/

			Item* bones = new Item("images/bones.png", 10);
			Game::GetObjectQueue().Add("Bones", bones, "front"); // Spawn bones where the soldier used to be
			bones->SetPosition(GetPosition());
		}
		if (faction == Enemy)
			Game::score += 1;
		else if (faction == Ally)
			Game::score -= 1;
	}
}

void Soldier::Update(float deltaTime, sf::Event ev)
{
	frameCount += 1;
	const float PI = 3.141592f;

	GetTarget(faction); // Store nearest target in target

	if (target == NULL) // Do nothing if there is no target
	{
		return;
	}

	float dx = target->GetPosition().x - GetPosition().x;
	float dy = target->GetPosition().y - GetPosition().y;

	if (!collided) // Normal behavior, pre-obstruction
	{
		////////////////////// COLLISION DETECTION /////////////////////////////
		if (fmod(frameCount, 20) == 0) // Perform a ray cast three times a second
		{
			Entity hitEntity; // Empty block that will be passed by reference to Cast()
			RayCast cast(sf::Vector2i(16, 16), GetPosition(), GetRotation(false), 20.0f); // Cast out directly in front of the soldier
			if (cast.Cast(hitEntity, Neutral))
			{
				collided = true;
				GetTraceDir(hitEntity, dx, dy);
				return; // Do not follow normal behavior; Go to else block
			}
		}

		float angleRad = atan(dy / dx); // Angle in the direction of the target, based on locations and trigonometry

		if (dx < 0)
			angleRad += PI;

		float angleDeg = angleRad * 180 / PI;
		SetRotation(angleDeg);

		///////////////////// LINE OF SIGHT DETECTION ////////////////////////
		if (LoS) // If there is line of sight
		{
			if (sqrt(pow(abs(dx), 2) + pow(abs(dy), 2)) > range) // If the nearest enemy is more than 300 pixels away chase it
			{
				SetPosition(GetPosition().x + cos(angleRad) * speed, GetPosition().y + sin(angleRad) * speed);

				if (fmod(frameCount, 20) == 0)
					Walk();
			}
			else // Fire instead
			{
				if (fmod(frameCount, 20) == 0) // Cast will be three times a second, adjustable if necessary
				{
					Entity hitEntity; // Empty object that will be passed by reference to Cast()
					RayCast cast(sf::Vector2i(16, 16), GetPosition(), GetRotation(false), range); // Cast out directly in front of the soldier the distance of its range
					float castDist = cast.Cast(hitEntity, Neutral); // Actual cast here

					// If the cast hits something and that something is blocking the target
					if (castDist != 0 && castDist < GetDistance(*target))
						LoS = false;
				}

				dispRect.top = 0;
				_sprite.setTextureRect(dispRect); // Use firing sprite

				if (fmod(frameCount, 20) == 0)
					Fire(angleRad); // Fire
			}
		}
		else // No line of sight to target
		{
			SetPosition(GetPosition().x + cos(angleRad) * speed, GetPosition().y + sin(angleRad) * speed); // Just walk forward and trigger obstacle tracing

			if (fmod(frameCount, 20) == 0) // Cast will be three times a second, adjustable if necessary
			{
				Entity hitEntity; // Empty object that will be passed by reference to Cast()
				RayCast cast(sf::Vector2i(16, 16), GetPosition(), GetRotation(false), range); // Cast out directly in front of the soldier the distance of its range
				float castDist = cast.Cast(hitEntity, Neutral); // Actual cast here

				// True if: \/ Cast returns false or \/ The object hit by the cast is not blocking the target
				if (castDist == 0 || GetDistance(hitEntity) > GetDistance(*target))
					LoS = true;
			}
		}
	}
	else // collided flag has been flipped and trace direction has been initialized; follow specific behavior for object tracing
	{
		////////////////////////// OBJECT TRACING BEHAVIOR /////////////////////////
		if (fmod(frameCount, 20) == 0) // Ray tracing is laggy... Perhaps a better solution can be found
		{
			Entity hitEntity;
			// The direction enum is set up so that their index multiplied by PI/2 is their numerical rotation
			RayCast cast(sf::Vector2i(GetSpriteRect().width, GetSpriteRect().height), GetPosition(), traceDir * 3.141592f / 2, 30.0f);
			if (cast.Cast(hitEntity, Neutral))
			{
				if (fmod(frameCount, 20) == 0)
				{
					Walk();
				}
				SetPosition(GetPosition().x + speed * cos(GetRotation(false)), GetPosition().y + speed * sin(GetRotation(false)));
			}
			else
			{
				collided = false;
				traceDir = Uninitialized;
			}
		}
		else
		{
			SetPosition(GetPosition().x + speed * cos(GetRotation(false)), GetPosition().y + speed * sin(GetRotation(false)));
		}
	}
	LifeBar.SetPosition(GetPosition().x - 12.5, GetPosition().y - 20);
	LifeBar.SetHealth(health, healthMax);
}

void Soldier::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	LifeBar.Draw(rw);

	// Draws the casts, useful for debugging
	/*sf::RectangleShape shape(sf::Vector2f(GetSpriteRect().width, GetSpriteRect().height));
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
	shape.setPosition(GetPosition().x + 30 * cos(traceDir * 3.141592f / 2), GetPosition().y + 30 * sin(traceDir * 3.141592f / 2));
	rw.draw(shape);

	sf::RectangleShape shape2(sf::Vector2f(16, 16));
	shape2.setFillColor(sf::Color::Red);
	shape2.setOrigin(shape2.getLocalBounds().width / 2, shape2.getLocalBounds().height / 2);
	shape2.setPosition(GetPosition().x + 20 * cos(GetRotation() / 180 * 3.141592f), GetPosition().y + 20 * sin(GetRotation() / 180 * 3.141592f));
	rw.draw(shape2);*/
}

void Soldier::GetTraceDir(Entity& hitEntity, float dx, float dy)
{
	if (GetPosition().y < hitEntity.GetPosition().y - hitEntity.GetSpriteRect().height / 2) // Hit top edge, traceDir will be down
	{
		if (dx > 0) // Target is on right
			SetRotation(0);
		else // Target is on left
			SetRotation(180);
		traceDir = Down;
	}
	else if (GetPosition().y > hitEntity.GetPosition().y + hitEntity.GetSpriteRect().height / 2) // Hit bottom edge, traceDir will be up
	{
		if (dx > 0) // Target is on right
			SetRotation(0);
		else // Target is on left
			SetRotation(180);
		traceDir = Up;
	}
	else if (GetPosition().x > hitEntity.GetPosition().x) // Hit right edge, traceDir will be left
	{
		if (dy > 0) // Target is on bottom
			SetRotation(90);
		else // Target is on top
			SetRotation(270);
		traceDir = Left;
	}
	else if (GetPosition().x < hitEntity.GetPosition().x) // Hit left edge, traceDir will be right
	{
		if (dy > 0) // Target is on bottom
			SetRotation(90);
		else // Target is on top
			SetRotation(270);
		traceDir = Right;
	}
}

void Soldier::GetTarget(Faction fac)
{
	float min = FLT_MAX;
	std::vector<Entity*> TargetList;
	if (fac == Enemy)
	{
		TargetList = Game::AllyList;
	}
	else if (fac == Ally)
	{
		TargetList = Game::EnemyList;
	}
	
	std::vector<Entity*>::iterator iter = TargetList.begin();
	while (iter != TargetList.end())
	{
		float dx = (*iter)->GetPosition().x - GetPosition().x;
		float dy = (*iter)->GetPosition().y - GetPosition().y;

		if (sqrt(pow(abs(dx), 2) + pow(abs(dy), 2)) < min)
		{
			min = sqrt(pow(abs(dx), 2) + pow(abs(dy), 2));
			target = *iter;
		}
		iter++;
	}
	if (TargetList.size() == 0)
	{
		target = NULL;
	}
}

void Soldier::Walk()
{
	/*if (dispRect.top == 0 || dispRect.top == 42)
	{
		dispRect.top = 21;
	}
	else
	{
		dispRect.top = 42;
	}
	_sprite.setTextureRect(dispRect);*/
}

void Soldier::Fire(float angle)
{
	Projectile* bullet = new Projectile("images/bullet.png", angle, 6, faction, 5);
	Game::GetObjectQueue().Add("bullet", bullet, "back");

	float rotRad = GetRotation() / 180 * 3.141592f;
	bullet->SetPosition(GetPosition().x + 30 * cos(rotRad), GetPosition().y + 30 * sin(rotRad));
}