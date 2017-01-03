#include "stdafx.h"
#include "AITank.h"
#include "Game.h"
#include "TileData.h"
#include "RayCast.h"
#include "Item.h"

AITank::AITank(std::string basefile, std::string turretfile, float life, Faction fac)
	: MainTurret(turretfile, fac)
{
	Load(basefile);
	assert(IsLoaded());
	texturefile = basefile;

	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	health = healthMax = life;
	speed = 3;
	faction = fac;

	if (fac == Enemy)
	{
		TileData::CurrentTile->EnemyList.push_back(this); // To initialize tanks created in TileData
		Game::EnemyList.push_back(this); // To initialize tanks created during game loop
	}
	else if (fac == Ally)
	{
		TileData::CurrentTile->AllyList.push_back(this); // To initialize tanks created in TileData
		Game::AllyList.push_back(this); // To initialize tanks created during game loop
	}
	infantry = false;
}

AITank::~AITank()
{
	Item* hull = new Item("images/destroyedtank.png", 20);
	Game::GetObjectQueue().Add("Hull", hull, "front");
	hull->SetPosition(GetPosition());
	hull->SetRotation(GetRotation());

	Game::score += 10;
}

void AITank::Update(float deltaTime, sf::Event ev)
{
	const float PI = 3.141592f;
	GetTarget(faction);
	//target = dynamic_cast<Entity*>(Game::GetObjectManager().Get("Tank")); UNCOMMENT FOR TANK V. TANK
	if (target == NULL)
	{
		return;
	}
	float dx = target->GetPosition().x - GetPosition().x;
	float dy = target->GetPosition().y - GetPosition().y;

	if (!collided) // Normal behavior, pre-obstruction
	{
		if (fmod(frameCount, 20) == 0) // Perform a ray cast three times a second
		{
			Entity hitEntity; // Empty block that will be passed by reference to Cast()
			RayCast cast(sf::Vector2i(16, 16), GetPosition(), GetRotation(), 40.0f); // Cast out directly in front of the tank
			if (cast.Cast(hitEntity, Neutral))
			{
				collided = true;
				GetTraceDir(hitEntity, dx, dy);
				return; // Do not follow normal behavior; Go to else block
			}
		}

		float angleRad = atan(dy / dx); // Angle in the direction of the target, based on locations and trigonometry

		if (dx < 0)
		{
			angleRad += PI;
		}
		float angleDeg = angleRad * 180 / PI;

		SetRotation(angleDeg);		
		SetPosition(GetPosition().x + cos(angleRad) * speed, GetPosition().y + sin(angleRad) * speed);

		//if (fmod(frameCount, 20) == 0)
			//Fire(angleRad);
	}
	else // collided flag has been flipped and trace direction has been initialized; follow specific behavior for object tracing 
	{
		Block hitEntity;
		// The direction enum is set up so that their index multiplied by PI/2 is their numerical rotation
		RayCast cast(sf::Vector2i(GetTextureRect().width, GetTextureRect().height), GetPosition(), traceDir * 3.141592f / 2, 50.0f);
		if (cast.Cast(hitEntity, Neutral))
		{
			SetPosition(GetPosition().x + speed * cos(GetRotation() / 180 * 3.141592f), GetPosition().y + speed * sin(GetRotation() / 180 * 3.141592f));
		}
		else
		{
			collided = false;
			traceDir = Uninitialized;
		}
	}

	std::vector<Entity*> FactionList;
	if (faction == Enemy)
		FactionList = Game::AllyList;
	else if (faction == Ally)
		FactionList = Game::EnemyList;
		
	// Collision damage
	std::vector<Entity*>::iterator iter = FactionList.begin();
	while (iter != FactionList.end())
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

	MainTurret.SetPosition(GetPosition());
	MainTurret.Update(deltaTime, ev);
	LifeBar.SetPosition(GetPosition().x - 25, GetPosition().y - 50);
	LifeBar.SetHealth(health, healthMax);
}

void AITank::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	LifeBar.Draw(rw);
	MainTurret.Draw(rw);

	// Draws the casts, useful for debugging
	/*sf::RectangleShape shape(sf::Vector2f(GetTextureRect().width, GetTextureRect().height));
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
	shape.setPosition(GetPosition().x + 50 * cos(traceDir * 3.141592f / 2), GetPosition().y + 50 * sin(traceDir * 3.141592f / 2));
	rw.draw(shape);

	sf::RectangleShape shape2(sf::Vector2f(16, 16));
	shape2.setFillColor(sf::Color::Red);
	shape2.setOrigin(shape2.getLocalBounds().width / 2, shape2.getLocalBounds().height / 2);
	shape2.setPosition(GetPosition().x + 40 * cos(GetRotation() / 180 * 3.141592f), GetPosition().y + 40 * sin(GetRotation() / 180 * 3.141592f));
	rw.draw(shape2);*/
}
