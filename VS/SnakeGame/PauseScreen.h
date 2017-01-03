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
	Button LeftButton3;
	Button RightButton3;
	Button PlayerButton;
	Button HitSelfButton;
	Button HitWallButton;
	Button HitOtherButton;
	Button TransparencyButton;
	Button LengthButton;
	Button ConfirmButton;
	DisplayBox Player1Box;
	DisplayBox Player2Box;
	DisplayBox TextureBox;
	DisplayBox Player1Name;
	DisplayBox Player2Name;
	DisplayBox TextureName;

	std::vector<std::string> TextureList;
	std::vector<std::string> BackgroundList;

	sf::Texture currentTexture1;
	sf::Texture currentTexture2;
	sf::Texture gameBackground; // Texture for the icon for the game's background

	sf::Texture bgTexture; // Sprite and texture for the background of the pause screen
	sf::Sprite bgSprite;

	int currentIndex1;
	int currentIndex2;
	int backgroundIndex;

	bool switched; // Boolean to detect whether or not the image changed; 
				  // Used to reduce the number of times files are loaded
};