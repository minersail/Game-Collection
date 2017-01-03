#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class DisplayBox : public VisibleGameObject
{
public:
	DisplayBox();
	DisplayBox(sf::Vector2i loc, float width, float height);
	~DisplayBox();

	void SetBoxSize(float newW, float newH); // Resize box
	void Update(float deltaTime, sf::Event ev); // Update box state, called 60 times a second
	void Draw(sf::RenderWindow& rw); // Update box sprite, called 60 times a second

	// all of these are self-explanatory
	void SetColor(sf::Color color);
	void SetSize(int size);
	void SetMessage(std::string mess);
	void SetFont(sf::Font& font);
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f newPos);
	
	sf::Vector2i location; // On the screen, not world coordinates
	sf::Text text;
};