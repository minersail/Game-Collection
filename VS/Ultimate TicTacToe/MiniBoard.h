#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Button.h"

class MiniBoard : public VisibleGameObject
{
public:
	MiniBoard(std::string filename);
	MiniBoard();
	~MiniBoard();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);
	Button* GetButton(int b);
	void ColorBoard();

	Button Button1;
	Button Button2;
	Button Button3;
	Button Button4;
	Button Button5;
	Button Button6;
	Button Button7;
	Button Button8;
	Button Button9;

	enum BoardState
	{
		Blank, XWin, OWin, Selected, Full
	};

	BoardState boardState;
	int clicks;
	bool full;
};