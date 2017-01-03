#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "KeypadNum.h"

class Keypad : public VisibleGameObject
{
private:
	int storedNum;

public:
	Keypad();
	
	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	KeypadNum button0;
	KeypadNum button1;
	KeypadNum button2;
	KeypadNum button3;
	KeypadNum button4;
	KeypadNum button5;
	KeypadNum button6;
	KeypadNum button7;
	KeypadNum button8;
	KeypadNum button9;
	KeypadNum buttonX;
	KeypadNum buttonVend;

	sf::Vector2f center;
};

