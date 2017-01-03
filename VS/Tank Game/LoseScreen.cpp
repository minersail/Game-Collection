#include "stdafx.h"
#include "LoseScreen.h"
#include "DisplayBox.h"
#include "Game.h"

LoseScreen::LoseScreen()
{
}

LoseScreen::~LoseScreen()
{
}

void LoseScreen::ShowScreen(sf::RenderWindow& rw, sf::Event ev)
{
	rw.clear(sf::Color(80, 50, 50));

	DisplayBox box(sf::Vector2i(512, 400), 500, 200);
	box.SetMessage("YOU LOSE");
	box.Draw(rw);

	DisplayBox box2(sf::Vector2i(512, 650), 300, 100);
	box2.SetSize(20);
	box2.SetMessage("PRESS ANY KEY TO CONTINUE");
	box2.Draw(rw);

	rw.display();

	if (ev.type == sf::Event::KeyReleased)
	{
		Game::_gameState = Game::Exiting;
	}
}