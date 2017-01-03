#pragma once
#include "stdafx.h"
#include "DisplayBox.h"

/*
Button for menus and stuff. Currently not compatible with a GameObjectManager
*/
class Button : public DisplayBox
{
public:
	Button(std::string filename, float width, float height);
	~Button();

	void Draw(sf::RenderWindow& rw);
	void Update(float deltaTime, sf::Event ev);
	bool Clicked(sf::Event ev); // Called sixty times a second in Update(), checks if button has recieved a click event
	void SetActive(bool makeActive); // Darkens the sprite if inactive
	void Fall(); // Chip falling animation

	sf::Texture coilTexture;
	sf::Sprite coil;

	sf::Texture chip2Texture;
	sf::Sprite chip2;

	enum ButtonState
	{
		Stocked, Vending, Unstocked, Message
	};

	int stock;
	ButtonState currentState;
};