#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Entity.h"

class Block : public Entity
{
public:
	Block(std::string filename);
	Block(std::string filename, int width, int height);
	Block();
	~Block();

	void Update(float deltaTime, sf::Event ev);
	void Damage(float damage);

	// Bounding rect to use when the texture is to be tiled
	sf::Rect<int> tiledRect;
};