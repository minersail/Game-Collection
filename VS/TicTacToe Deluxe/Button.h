#pragma once
#include "stdafx.h"
#include "DisplayBox.h"

/*
Button for menus and stuff.
*/
class Button : public DisplayBox
{
public:
	Button(float width, float height, std::string filename);
	Button(float width, float height, std::string filename, std::string message);
	~Button();

	void Draw(sf::RenderWindow& rw);
	void Update(float deltaTime, sf::Event ev);
	bool Clicked(sf::Event ev); // Called sixty times a second in Update(), checks if button has recieved a click event
	void SetActive(bool makeActive); // Darkens the sprite if inactive

	sf::Sprite Player1;
	sf::Sprite Player2;

	enum ButtonState
	{
		Blank, Circle, X, Message
	};

	ButtonState currentState;
};