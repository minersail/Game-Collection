#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

/*
Class of Visible Game Object that has no collision and self-destructs after a certain amount of time
*/
class Item : public VisibleGameObject
{
public:
	Item(std::string filename, float time);
	~Item();

	void Update(float deltaTime, sf::Event ev);
	float totalTime;
};