#pragma once
#include "stdafx.h"
#include "Entity.h"

class Character : public Entity
{
public:
	Character(float initX, float initY, std::string textureID, std::string name);
	~Character();

	// In order for this to work, the spritesheet provided for characters should be 4x4:
	// Vertically the walk animation should progress and the four columns should be
	// North, East, South, West
	virtual void Walk(Direction dir);
	// Since characters will be moving from chunk to chunk, this will update the
	// EntityLists as they move from chunk to chunk
	virtual void UpdateChunk();

protected:
	int charW;
	int charH;

	int speed;
};