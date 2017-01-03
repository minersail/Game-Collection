#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Game.h"

Character::Character(float initX, float initY, std::string textureID, std::string name)
	: Entity(initX, initY, textureID, name, sf::IntRect(0, // See Barrier() to know why this was implemented
	Game::GTS(textureID).y / 4 / 2, Game::GTS(textureID).x / 4, Game::GTS(textureID).y / 4 / 2)), speed(2)
{
	charW = GetSprite().getTexture()->getSize().x / 4;
	charH = GetSprite().getTexture()->getSize().y / 4;

	SetTextureRect(0, 0, charW, charH);

	immovable = false;
}

Character::~Character()
{
}

void Character::Walk(Direction dir)
{
	// Update the frame count
	frameCount += 1;

	// Move the NPC based on the direction parameter, and change the NPC's facing direction
	switch (dir)
	{
		case Up:
		{
			SetTextureRect(0, GetSprite().getTextureRect().top, charW, charH);
			SetPosition(GetPosition().x, GetPosition().y - speed);
			break;
		}
		case Down:
		{
			SetTextureRect(charW * 2, GetSprite().getTextureRect().top, charW, charH);
			SetPosition(GetPosition().x, GetPosition().y + speed);
			break;
		}
		case Left:
		{
			SetTextureRect(charW * 3, GetSprite().getTextureRect().top, charW, charH);
			SetPosition(GetPosition().x - speed, GetPosition().y);
			break;
		}
		case Right:
		{
			SetTextureRect(charW * 1, GetSprite().getTextureRect().top, charW, charH);
			SetPosition(GetPosition().x + speed, GetPosition().y);
			break;
		}
		case None:
		{
			SetTextureRect(GetSprite().getTextureRect().left, 0, charW, charH);
			return; // Skip the rest in this case
			break;
		}
	}

	// Every ten ticks advance the "walking" by moving to the next walking sprite in the same facing direction
	if (frameCount % 10 == 0)
	{
		if (GetSprite().getTextureRect().top != 78)
		{
			SetTextureRect(GetSprite().getTextureRect().left, GetSprite().getTextureRect().top + charH, charW, charH);
		}
		else
		{
			SetTextureRect(GetSprite().getTextureRect().left, 0, charW, charH);
		}
	}
}

void Character::UpdateChunk() // CHANGE WHEN THERE ARE MORE THAN 9 CHUNKS
{
	// Offset to top-left corner of player's hitbox
	int newChunk = std::floor((GetPosition().x + GetHitBox().width / 2) / Game::SCREEN_WIDTH) + std::floor((GetPosition().y + GetHitBox().height / 2) / Game::SCREEN_HEIGHT) * Game::YCHUNKS;
	if (newChunk != ChunkID) // There has been a change in chunk
	{
		if (newChunk < ChunkID - 1) // Up
		{
			//std::cout << "Up" << std::endl;
		}
		else if (newChunk < ChunkID) // Left
		{
			//std::cout << "Left" << std::endl;
		}
		else if (newChunk > ChunkID + 1) // Down
		{
			//std::cout << "Down" << std::endl;
		}
		else if (newChunk > ChunkID) // Right
		{
			//std::cout << "Right" << std::endl;
		}
		Game::GetCollisionManager().Remove(ChunkID, this);
		ChunkID = newChunk;
		Game::GetCollisionManager().Add(ChunkID, this);
	}
}