#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

/*
Class that has a text box sprite and a text object
*/
class MessageBox : public VisibleGameObject
{
public:
	MessageBox(float initX, float initY, std::string message = "", int size = 30, sf::Color color = sf::Color::Black);
	~MessageBox();

	void Draw(sf::RenderWindow& rw);

	void SetColor(sf::Color color);
	void SetSize(int size);
	void SetMessage(std::string mess);
	void SetFont(sf::Font& font);

	sf::Text& GetText();

private:
	sf::Color fontColor;
	int fontSize;
	std::string message;
	sf::Text text;
};