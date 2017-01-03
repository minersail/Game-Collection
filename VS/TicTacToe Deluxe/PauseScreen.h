#pragma once
#include "stdafx.h"
#include "Button.h"

class PauseScreen
{
public:
	PauseScreen();
	~PauseScreen();

	void SelectScreen(sf::Event ev, sf::RenderWindow& rw);

private:
	Button LeftButton1;
	Button RightButton1;
	Button LeftButton2;
	Button RightButton2;
	Button PlayerButton;
	Button ConfirmButton;
	DisplayBox Player1Box;
	DisplayBox Player2Box;
	DisplayBox Player1Name;
	DisplayBox Player2Name;

	std::vector<std::string> TextureList;

	sf::Texture currentTexture1;
	sf::Texture currentTexture2;

	int currentIndex1;
	int currentIndex2;

	bool switched; // Boolean to detect whether or not the image changed; 
				  // Used to reduce the number of times files are loaded
};