#include "stdafx.h"
#include "Block.h"
#include "Game.h"
#include "Tank.h"
#include "Projectile.h"

// Use this constructor if you want the block to be exactly the size of the image
Block::Block(std::string filename)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	faction = Neutral;
	infantry = false;
}

// Use this constructor if you have a small texture and want the block with certain dimensions with the texture tiled
Block::Block(std::string filename, int width, int height)
{
	Load(filename, true);
	assert(IsLoaded());
	texturefile = filename;

	tiledRect.width = width;
	tiledRect.height = height;
	_sprite.setTextureRect(tiledRect);

	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	MTV.second = FLT_MAX;
	MTV.first = sf::Vector2f(0, 0);
	faction = Neutral;
	infantry = false;
}

Block::Block()
{
	//Default constructor
	GetSprite().setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);
	MTV.second = FLT_MAX;
	MTV.first = sf::Vector2f(0, 0);
	faction = Neutral;
	infantry = false;
}

Block::~Block()
{
}

void Block::Update(float deltaTime, sf::Event ev)
{
	std::vector<Entity*>::iterator iter = Game::EntityList.begin();
	while (iter != Game::EntityList.end())
	{
		Block* test = dynamic_cast<Block*>(*iter);
		if (GetBoundingRect().intersects((*iter)->GetBoundingRect()) && !test) // If there is a bounding-box collision and the other collider is not a block
		{
			if (CheckForCollision(*iter)) // Perform SAT test for detailed collision
			{
				(*iter)->SetPosition((*iter)->GetPosition().x + MTV.first.x * MTV.second, (*iter)->GetPosition().y + MTV.first.y * MTV.second);
			}
		}
		iter++;
	}

	/*/////////////////////CHRIS FUN///////////////////////////

	
	sf::Vector2f loc1 = GetVertices()[0];
	sf::Vector2f loc2 = GetVertices()[1];
	sf::Vector2f loc3 = GetVertices()[2];
	sf::Vector2f loc4 = GetVertices()[3];

	Projectile* chris1 = new Projectile("images/chris.png", 90);
	Projectile* chris2 = new Projectile("images/chris.png", 90);
	Projectile* chris3 = new Projectile("images/chris.png", 90);
	Projectile* chris4 = new Projectile("images/chris.png", 90);

	chris1->SetPosition(loc1);
	chris2->SetPosition(loc2);
	chris3->SetPosition(loc3);
	chris4->SetPosition(loc4);

	Game::GetObjectQueue().push_back(std::pair<std::string, VisibleGameObject*>("proj", chris1));
	Game::GetObjectQueue().push_back(std::pair<std::string, VisibleGameObject*>("proj", chris2));
	Game::GetObjectQueue().push_back(std::pair<std::string, VisibleGameObject*>("proj", chris3));
	Game::GetObjectQueue().push_back(std::pair<std::string, VisibleGameObject*>("proj", chris4));
	*////////////////////////////////////////////////////////////////////////////////////////////
}

void Block::Damage(float damage)
{
	// Override the entity behavior for damaging; projectiles should not damage blocks
}