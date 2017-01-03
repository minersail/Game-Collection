#include "stdafx.h"
#include "MiniBoard.h"
#include "Game.h"

MiniBoard::MiniBoard(std::string filename)
	: Button1(150, 150), Button2(150, 150), Button3(150, 150),
	Button4(150, 150), Button5(150, 150), Button6(150, 150),
	Button7(150, 150), Button8(150, 150), Button9(150, 150)
{
	Load(filename);
	assert(IsLoaded());

	texturefile = filename;

	Button1.name = "1";
	Button2.name = "2";
	Button3.name = "3";
	Button4.name = "4";
	Button5.name = "5";
	Button6.name = "6";
	Button7.name = "7";
	Button8.name = "8";
	Button9.name = "9";

	Button1.owner = this;
	Button2.owner = this;
	Button3.owner = this;
	Button4.owner = this;
	Button5.owner = this;
	Button6.owner = this;
	Button7.owner = this;
	Button8.owner = this;
	Button9.owner = this;

	boardState = Blank;
	clicks = 0;
	full = false;
}

MiniBoard::MiniBoard()
	: Button1(150, 150), Button2(150, 150), Button3(150, 150),
	Button4(150, 150), Button5(150, 150), Button6(150, 150),
	Button7(150, 150), Button8(150, 150), Button9(150, 150)
{
}

MiniBoard::~MiniBoard()
{
}

void MiniBoard::Update(float deltaTime, sf::Event ev)
{
	float POS1 = 75;
	float POS2 = 230;
	float POS3 = 385;

	Button1.SetPosition(GetPosition().x + POS1, GetPosition().y + POS1);
	Button2.SetPosition(GetPosition().x + POS2, GetPosition().y + POS1);
	Button3.SetPosition(GetPosition().x + POS3, GetPosition().y + POS1);
	Button4.SetPosition(GetPosition().x + POS1, GetPosition().y + POS2);
	Button5.SetPosition(GetPosition().x + POS2, GetPosition().y + POS2);
	Button6.SetPosition(GetPosition().x + POS3, GetPosition().y + POS2);
	Button7.SetPosition(GetPosition().x + POS1, GetPosition().y + POS3);
	Button8.SetPosition(GetPosition().x + POS2, GetPosition().y + POS3);
	Button9.SetPosition(GetPosition().x + POS3, GetPosition().y + POS3);

	if (clicks == 9)
	{
		full = true;
	}

	if (Game::allValid == true && boardState != OWin && boardState != XWin && !full)
	{ // If all boards are valid and this board is not in a final state			
		Button1.Update(deltaTime, ev);
		Button2.Update(deltaTime, ev);
		Button3.Update(deltaTime, ev);
		Button4.Update(deltaTime, ev);
		Button5.Update(deltaTime, ev);
		Button6.Update(deltaTime, ev);
		Button7.Update(deltaTime, ev);
		Button8.Update(deltaTime, ev);
		Button9.Update(deltaTime, ev);
		boardState = Selected;
	}
	else if (Game::currentBoard == this) // If this is the currently selected board
	{
		Button1.Update(deltaTime, ev);
		Button2.Update(deltaTime, ev);
		Button3.Update(deltaTime, ev);
		Button4.Update(deltaTime, ev);
		Button5.Update(deltaTime, ev);
		Button6.Update(deltaTime, ev);
		Button7.Update(deltaTime, ev);
		Button8.Update(deltaTime, ev);
		Button9.Update(deltaTime, ev);
	}
	else if (boardState != OWin && boardState != XWin) // If this is not a selected or won board
	{
		if (full)
		{
			boardState = Full;
		}
		else
		{
			boardState = Blank;
		}
	}

	ColorBoard();
}

void MiniBoard::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	Button1.Draw(rw);
	Button2.Draw(rw);
	Button3.Draw(rw);
	Button4.Draw(rw);
	Button5.Draw(rw);
	Button6.Draw(rw);
	Button7.Draw(rw);
	Button8.Draw(rw);
	Button9.Draw(rw);
}

Button* MiniBoard::GetButton(int b)
{
	switch (b)
	{
		case 1:
		{
			return &Button1;
			break;
		}
		case 2:
		{
			return &Button2;
			break;
		}
		case 3:
		{
			return &Button3;
			break;
		}
		case 4:
		{
			return &Button4;
			break;
		}
		case 5:
		{
			return &Button5;
			break;
		}
		case 6:
		{
			return &Button6;
			break;
		}
		case 7:
		{
			return &Button7;
			break;
		}
		case 8:
		{
			return &Button8;
			break;
		}
		case 9:
		{
			return &Button9;
			break;
		}
		default:
		{
			std::cout << "ERROR BUTTON DOES NOT EXIST" << std::endl;
			return NULL;
		}
	}
}

void MiniBoard::ColorBoard()
{
	switch (boardState)
	{
		case Blank:
		{
			GetSprite().setColor(sf::Color(255, 255, 255));
			break;
		}
		case XWin:
		{
			GetSprite().setColor(sf::Color(255, 0, 0));
			break;
		}
		case OWin:
		{
			GetSprite().setColor(sf::Color(0, 0, 255));
			break;
		}
		case Selected:
		{
			GetSprite().setColor(sf::Color(0, 255, 0));
			break;
		}
		case Full:
		{
			GetSprite().setColor(sf::Color(128, 128, 128));
			break;
		}
	}
}