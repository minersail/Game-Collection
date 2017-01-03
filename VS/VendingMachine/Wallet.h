#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Button.h"
#include "Money.h"

class Wallet : public VisibleGameObject
{
public:
	Wallet();
	~Wallet();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	Money quarter;
	Money dime;
	Money nickel;
	Money penny;
	Money dollar;
	Money fivedollar;
	Money tendollar;

	sf::Texture openTexture;
	sf::Sprite open;

	bool isOpen;
};