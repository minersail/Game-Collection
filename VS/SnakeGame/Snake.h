#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Snake : public VisibleGameObject
{
public:
	Snake(std::string filename);
	~Snake();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	void CheckSelfCollision();
	void CheckWallCollision();
	void CheckAppleCollision();
	void CheckOtherCollision();

	void Reset();

	enum Direction
	{
		Up, Right, Down, Left, None
	};

	Direction currentDir;
	int playerNum;
	int powerCount; // Ticks of powerup time

	sf::Texture ArmorTexture;

	std::vector<sf::Sprite> snakeList;
};