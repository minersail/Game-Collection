#include "stdafx.h"
#include "PauseScreen.h"
#include "Game.h"
#include "Snake.h"
#include "Map.h"

PauseScreen::PauseScreen()
	: LeftButton1(100, 100, "images/leftbutton.png", false), RightButton1(100, 100, "images/rightbutton.png", false),
	LeftButton2(100, 100, "images/leftbutton.png", false), RightButton2(100, 100, "images/rightbutton.png", false),
	LeftButton3(100, 100, "images/leftbutton.png", false), RightButton3(100, 100, "images/rightbutton.png", false),
	PlayerButton(300, 50, "images/button.png", "Single Player", true), ConfirmButton(200, 50, "images/button.png", "Confirm", true),
	HitSelfButton(300, 50, "images/button.png", "Death on Hit", true), HitWallButton(300, 50, "images/button.png", "Wall Death", true),
	HitOtherButton(300, 50, "images/button.png", "Player Collision", true), TransparencyButton(300, 50, "images/button.png", "Solid Color", true), 
	LengthButton(300, 50, "images/button.png", "Extra Length: 0", true),
	Player1Box(sf::Vector2i(200, 150), 150, 150, "images/snakeblue.png", false),
	Player2Box(sf::Vector2i(200, 370), 150, 150, "images/snakeorange.png", false),
	TextureBox(sf::Vector2i(200, 590), 150, 150, "images/greyBG.png", false),
	Player1Name(sf::Vector2i(200, 40), 150, 50, "images/displaybox.png", "Player 1", false),
	Player2Name(sf::Vector2i(200, 260), 150, 50, "images/displaybox.png", "Player 2", false),
	TextureName(sf::Vector2i(200, 480), 250, 50, "images/displaybox.png", "Background", false)
{
	bgTexture.loadFromFile("images/pausebg.png");
	bgSprite.setTexture(bgTexture);

	LeftButton1.SetPosition(50, 150);
	RightButton1.SetPosition(350, 150);
	LeftButton2.SetPosition(50, 370);
	RightButton2.SetPosition(350, 370);
	LeftButton3.SetPosition(50, 590);
	RightButton3.SetPosition(350, 590);
	PlayerButton.SetPosition(600, 90);
	HitSelfButton.SetPosition(600, 150);
	HitWallButton.SetPosition(600, 210);
	HitOtherButton.SetPosition(600, 270);
	TransparencyButton.SetPosition(600, 330);
	LengthButton.SetPosition(600, 390);
	ConfirmButton.SetPosition(600, 650);

	std::string tempArr[8] = {"images/snakeblue.png", "images/snakeorange.png", "images/chris.png", "images/austin1.png",
							  "images/austin2.png", "images/austinbeard.png", "images/ben.png", "images/peytwo.png"};
	TextureList.insert(TextureList.end(), &tempArr[0], &tempArr[8]); // Make sure this matches above

	std::string tempArr2[4] = {"images/greyBG.png", "images/gridBG.png", "images/spaceBG.png", "images/keanuBG.png"};
	BackgroundList.insert(BackgroundList.end(), &tempArr2[0], &tempArr2[4]);

	currentIndex1 = 1;
	currentIndex2 = 0;
	backgroundIndex = 0;

	currentTexture1.loadFromFile(TextureList[currentIndex1]);
	currentTexture2.loadFromFile(TextureList[currentIndex2]);
	gameBackground.loadFromFile(BackgroundList[backgroundIndex]);

	Player1Box.GetSprite().setTexture(currentTexture1);
	Player2Box.GetSprite().setTexture(currentTexture2);
	TextureBox.GetSprite().setTexture(gameBackground);

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
	else if (LeftButton3.Clicked(ev))
	{
		backgroundIndex -= 1;
		if (backgroundIndex < 0)
		{
			backgroundIndex = BackgroundList.size() - 1;
		}
		switched = true;
	}
	else if (RightButton3.Clicked(ev))
	{
		backgroundIndex += 1;
		if (backgroundIndex >= BackgroundList.size())
		{
			backgroundIndex = 0;
		}
		switched = true;
	}
	else if (PlayerButton.Clicked(ev))
	{
		Game::singlePlayer = Game::singlePlayer ? false : true; // Switch to true if false, to false if true
		PlayerButton.SetMessage((PlayerButton.GetMessage() == "Single Player" ? "Two Players" : "Single Player"));
	}
	else if (HitSelfButton.Clicked(ev))
	{
		Game::selfDeath = Game::selfDeath ? false : true; // Switch to true if false, to false if true
		HitSelfButton.SetMessage((HitSelfButton.GetMessage() == "Death on Hit" ? "Split on Hit" : "Death on Hit"));
	}
	else if (HitWallButton.Clicked(ev))
	{
		Game::wallDeath = Game::wallDeath ? false : true; // Switch to true if false, to false if true
		HitWallButton.SetMessage((HitWallButton.GetMessage() == "Wall Death" ? "Wall Teleport" : "Wall Death"));
	}
	else if (HitOtherButton.Clicked(ev))
	{
		Game::otherDeath = Game::otherDeath ? false : true; // Switch to true if false, to false if true
		HitOtherButton.SetMessage((HitOtherButton.GetMessage() == "Player Collision" ? "Player Avoidance" : "Player Collision"));
	}
	else if (TransparencyButton.Clicked(ev))
	{
		Game::transparent = Game::transparent ? false : true; // Switch to true if false, to false if true
		TransparencyButton.SetMessage((TransparencyButton.GetMessage() == "Solid Color" ? "Transparent Tail" : "Solid Color"));
	}
	else if (LengthButton.Clicked(ev))
	{
		Game::extraLength = Game::extraLength == 0 ? 1 : 0; // Switch to true if false, to false if true
		LengthButton.SetMessage((LengthButton.GetMessage() == "Extra Length: 0" ? "Extra Length: 1" : "Extra Length: 0"));
	}
	else if (ConfirmButton.Clicked(ev))
	{
		Game::texture1 = currentTexture1;
		Game::texture2 = currentTexture2;
		Game::_gameState = Game::Playing;

		Map* bg = dynamic_cast<Map*>(Game::GetObjectManager().Get("Map"));
		bg->GetSprite().setTexture(gameBackground);
		
		Snake* p1 = dynamic_cast<Snake*>(Game::GetObjectManager().Get("Player 1"));
		Snake* p2 = dynamic_cast<Snake*>(Game::GetObjectManager().Get("Player 2"));

		p1->Reset();
		p2->Reset();

		return;
	}
	
	if (switched)
	{
		currentTexture1.loadFromFile(TextureList[currentIndex1]);
		currentTexture2.loadFromFile(TextureList[currentIndex2]);
		gameBackground.loadFromFile(BackgroundList[backgroundIndex]);

		Player1Box.GetSprite().setTexture(currentTexture1, true);
		Player2Box.GetSprite().setTexture(currentTexture2, true);
		TextureBox.GetSprite().setTexture(gameBackground);
		
		switched = false;
	}

	rw.draw(bgSprite);
	LeftButton1.Draw(rw);
	RightButton1.Draw(rw);
	LeftButton2.Draw(rw);
	RightButton2.Draw(rw);
	LeftButton3.Draw(rw);
	RightButton3.Draw(rw);
	PlayerButton.Draw(rw);
	HitSelfButton.Draw(rw);
	HitWallButton.Draw(rw);
	HitOtherButton.Draw(rw);
	TransparencyButton.Draw(rw);
	LengthButton.Draw(rw);
	ConfirmButton.Draw(rw);
	Player1Box.Draw(rw);
	Player2Box.Draw(rw);
	TextureBox.Draw(rw);
	Player1Name.Draw(rw); // Call custom draw function for displayboxes with text
	Player2Name.Draw(rw);
	TextureName.Draw(rw);
}