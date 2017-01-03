#include "stdafx.h"
#include "Messenger.h"
#include "Game.h"

Messenger::Messenger(float initX, float initY, std::string textureID, std::string name, int talkID)
	: UseObject(initX, initY, textureID, name, sf::IntRect(0, // See Barrier() to know why this was implemented
	Game::GTS(textureID).y / 4 / 2, Game::GTS(textureID).x / 4, Game::GTS(textureID).y / 4 / 2)),
	dialogueID(talkID)
{
	SetTextureRect(GetTextureRect().width * 3 / 4, 0, GetTextureRect().width / 4, GetTextureRect().height / 4);

	sf::Vector2i CoordVec(std::floor((GetPosition().x) / 16),
						  std::floor((GetPosition().y) / 16));

	GetActivationLocations().push_back(UsePoint(CoordVec.x + 1, CoordVec.y, Left));
	GetActivationLocations().push_back(UsePoint(CoordVec.x - 1, CoordVec.y, Right));
	GetActivationLocations().push_back(UsePoint(CoordVec.x, CoordVec.y + 1, Up));
	GetActivationLocations().push_back(UsePoint(CoordVec.x, CoordVec.y - 1, Down));

	immovable = true;
}

Messenger::~Messenger()
{
}

void Messenger::Update(float deltaTime, sf::Event ev)
{
	if (CheckUsePoints(ev))
	{
		sf::IntRect joeRect = Game::GetPlayer()->GetTextureRect();
		// Have the Messenger face Joe after talking
		if (joeRect.left == joeRect.width * 0)
			SetTextureRect(GetTextureRect().width * 2, 0, GetTextureRect().width, GetTextureRect().height);
		if (joeRect.left == joeRect.width * 1)
			SetTextureRect(GetTextureRect().width * 3, 0, GetTextureRect().width, GetTextureRect().height);
		if (joeRect.left == joeRect.width * 2)
			SetTextureRect(GetTextureRect().width * 0, 0, GetTextureRect().width, GetTextureRect().height);
		if (joeRect.left == joeRect.width * 3)
			SetTextureRect(GetTextureRect().width * 1, 0, GetTextureRect().width, GetTextureRect().height);

		Game::GetDialogueManager().SetNPC(this);
		Game::_gameState = Game::Talking;
	}
}