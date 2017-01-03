#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Apple : public VisibleGameObject
{
public:
	Apple(std::string filename, bool perm);
	~Apple();

	void Update(float deltaTime, sf::Event ev);
	void Move();

	bool permanent;
};