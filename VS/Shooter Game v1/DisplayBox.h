#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class DisplayBox : public VisibleGameObject
{
public:
	DisplayBox();
	DisplayBox(sf::Vector2i loc, float width, float height);
	~DisplayBox();

	void SetBoxSize(float newW, float newH);
	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	void SetColor(sf::Color color);
	void SetSize(int size);
	void SetMessage(std::string mess);
	void SetFont(sf::Font& font);
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f newPos);
	
	sf::Vector2i location; // On the screen, not world coordinates
	sf::Text text;
};