#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Button.h"
#include "Block.h"

class WorldScreen : public VisibleGameObject
{
public:
	WorldScreen();
	~WorldScreen();

	void Show(sf::RenderWindow& rw, sf::Event ev);

private:
	DisplayBox Title;
	Block marker1;
	Block marker2;
	Block marker3;
	Block marker4;

	std::vector<Block> markerList;
	int CurrentMarker;
};