#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Button.h"

class Money : public VisibleGameObject
{
public:
	Money(std::string filename, int val);
	~Money();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	bool hovered;
	int value;
};