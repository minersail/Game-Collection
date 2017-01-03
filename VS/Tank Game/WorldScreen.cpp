#include "stdafx.h"
#include "WorldScreen.h"
#include "Game.h"
#include "TileData.h"

WorldScreen::WorldScreen()
	: Title(sf::Vector2i(Game::SCREEN_HEIGHT / 2, 100), 200, 100),
	marker1("images/marker.png"),
	marker2("images/marker.png"),
	marker3("images/marker.png"),
	marker4("images/marker.png")
{
	Load("images/world2.png");
	assert(IsLoaded());
	texturefile = "images/world2.png";

	Title.SetMessage("World");

	marker1.SetPosition(81, 768);
	marker2.SetPosition(83, 870);
	marker3.SetPosition(182, 925);
	marker4.SetPosition(291, 818);

	marker1.name = "marker1";
	marker2.name = "marker2";
	marker3.name = "marker3";
	marker4.name = "marker4";

	markerList.push_back(marker1);
	markerList.push_back(marker2);
	markerList.push_back(marker3);
	markerList.push_back(marker4);

	CurrentMarker = 1;
}

WorldScreen::~WorldScreen()
{
}

void WorldScreen::Show(sf::RenderWindow& rw, sf::Event ev)
{
	rw.draw(_sprite);
	Title.Draw(rw);

	if (ev.type == sf::Event::KeyReleased)
	{
		if (ev.key.code == sf::Keyboard::Right)
		{
			CurrentMarker++;
			if (CurrentMarker > 4) // Change number based on highest marker
			{
				CurrentMarker = 1;
			}
		}
		else if (ev.key.code == sf::Keyboard::Left)
		{
			CurrentMarker--;
			if (CurrentMarker < 1)
			{
				CurrentMarker = 4; // Change number based on highest marker
			}
		}
		else if (ev.key.code == sf::Keyboard::Return)
		{
			TileData::LoadTile(CurrentMarker);
			Game::SwitchTile();
			Game::_gameState = Game::Playing;
		}
	}

	std::vector<Block>::iterator iter = markerList.begin();
	while (iter != markerList.end())
	{
		if (iter->name == "marker" + std::to_string(CurrentMarker))
		{
			iter->GetSprite().setColor(sf::Color::Blue);
		}
		else
		{
			iter->GetSprite().setColor(sf::Color::Red);
		}
		iter->Draw(rw);
		iter++;
	}

	rw.display();
}