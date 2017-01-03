#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class DisplayBox : public VisibleGameObject
{
public:
	DisplayBox();
	DisplayBox(sf::Vector2i loc, float width, float height, std::string filename, bool tiled);
	DisplayBox(sf::Vector2i loc, float width, float height, std::string filename, std::string message, bool tiled);
	~DisplayBox();

	void SetBoxSize(float newW, float newH, bool tiled = false); // Resize box, either scaled or tiled
	void Update(float deltaTime, sf::Event ev); // Update box state, called 60 times a second
	void Draw(sf::RenderWindow& rw); // Update box sprite, called 60 times a second

	// all of these are self-explanatory
	void SetColor(sf::Color color);
	void SetSize(int size);
	void SetMessage(std::string mess);
	void SetFont(sf::Font& font);
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f newPos);

	std::string GetMessage();
	
	sf::Vector2i location; // On the screen, not world coordinates
	sf::Text text;
};