#pragma once
#include "stdafx.h"

class LoseScreen
{
public:
	LoseScreen();
	~LoseScreen();

	void ShowScreen(sf::RenderWindow& rw, sf::Event ev);
};