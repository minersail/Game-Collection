#pragma once
#include "stdafx.h"
#include "DisplayBox.h"
#include "Game.h"

class KeypadNum : public DisplayBox 
{
public:
	KeypadNum(std::string name, float width, float height);
	
	sf::Texture text1;
	sf::Texture text2;

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& window);

	std::string num;
};