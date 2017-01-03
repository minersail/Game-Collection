#include "stdafx.h"
#include "PauseScreen.h"
#include "Game.h"

PauseScreen::PauseScreen()
	: LeftButton1(100, 100, "images/leftbutton.png"), RightButton1(100, 100, "images/rightbutton.png"),
	LeftButton2(100, 100, "images/leftbutton.png"), RightButton2(100, 100, "images/rightbutton.png"),
	PlayerButton(300, 60, "images/button.png", "Single Player"), ConfirmButton(200, 60, "images/button.png", "Confirm"),
	Player1Box(sf::Vector2i(250, 150), 150, 150, "images/austin1.png"),
	Player2Box(sf::Vector2i(250, 370), 150, 150, "images/austin2.png"),
	Player1Name(sf::Vector2i(250, 40), 150, 50, "images/displaybox.png", "Player 1"),
	Player2Name(sf::Vector2i(250, 260), 150, 50, "images/displaybox.png", "Player 2")
{
	LeftButton1.SetPosition(50, 150);
	RightButton1.SetPosition(450, 150);
	LeftButton2.SetPosition(50, 370);
	RightButton2.SetPosition(450, 370);
	PlayerButton.SetPosition(256, 550);
	ConfirmButton.SetPosition(256, 650);

	std::string tempArr[8] = {"images/X.png", "images/O.png", "images/austinbeard.png", "images/austin1.png",
							  "images/austin2.png", "images/chris.png", "images/ben.png", "images/peytwo.png"};
	TextureList.insert(TextureList.end(), &tempArr[0], &tempArr[8]);

	currentIndex1 = 1;
	currentIndex2 = 0;

	currentTexture1.loadFromFile(TextureList[currentIndex1]);
	currentTexture2.loadFromFile(TextureList[currentIndex2]);
	Player1Box.GetSprite().setTexture(currentTexture1);
	Player2Box.GetSprite().setTexture(currentTexture2);

	switched = false;
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::SelectScreen(sf::Event ev, sf::RenderWindow& rw)
{
	rw.clear(sf::Color(128, 0, 128));
	if (LeftButton1.Clicked(ev))
	{
		currentIndex1 -= 1;
		if (currentIndex1 < 0)
		{
			currentIndex1 = TextureList.size() - 1;
		}
		switched = true;
	}
	else if (RightButton1.Clicked(ev))
	{
		currentIndex1 += 1;
		if (currentIndex1 >= TextureList.size())
		{
			currentIndex1 = 0;
		}
		switched = true;
	}
	else if (LeftButton2.Clicked(ev))
	{
		currentIndex2 -= 1;
		if (currentIndex2 < 0)
		{
			currentIndex2 = TextureList.size() - 1;
		}
		switched = true;
	}
	else if (RightButton2.Clicked(ev))
	{
		currentIndex2 += 1;
		if (currentIndex2 >= TextureList.size())
		{
			currentIndex2 = 0;
		}
		switched = true;
	}
	else if (PlayerButton.Clicked(ev))
	{
		Game::singleplayer = Game::singleplayer ? false : true; // Switch to true if false, to false if true
		PlayerButton.SetMessage((PlayerButton.GetMessage() == "Single Player" ? "Two Players" : "Single Player"));
	}
	else if (ConfirmButton.Clicked(ev))
	{
		Game::text1 = currentTexture1;
		Game::text2 = currentTexture2;
		Game::_gameState = Game::Playing;
		return;
	}
	
	if (switched)
	{
		currentTexture1.loadFromFile(TextureList[currentIndex1]);
		currentTexture2.loadFromFile(TextureList[currentIndex2]);

		Player1Box.GetSprite().setTexture(currentTexture1, true);
		Player2Box.GetSprite().setTexture(currentTexture2, true);
		
		switched = false;
	}

	LeftButton1.Draw(rw);
	RightButton1.Draw(rw);
	LeftButton2.Draw(rw);
	RightButton2.Draw(rw);
	PlayerButton.Draw(rw);
	ConfirmButton.Draw(rw);
	Player1Box.Draw(rw);
	Player2Box.Draw(rw);
	Player1Name.Draw(rw); // Call custom draw function for displayboxes with text
	Player2Name.Draw(rw);
}