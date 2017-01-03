#pragma once
#include "stdafx.h"
#include "DisplayBox.h"

/*
Button for menus and stuff. Currently not compatible with a GameObjectManager
*/
class Button : public DisplayBox
{
public:
	Button(sf::Vector2i loc, float width, float height);
	~Button();

	bool Clicked(sf::Event ev);
};