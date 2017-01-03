#include "stdafx.h"
#include "DialogueManager.h"
#include "Game.h"
#include "QuestGiver.h"

DialogueManager::DialogueManager()
	: dialogueBox(0, 0), talkIter(0)
{
	Dialogue D1;
	D1.AddMessage("Hello", 0);
	D1.AddMessage("Shut up", 1);
	D1.AddMessage("Uh.. Goodbye", 0);
	MasterDialogueList.push_back(D1);

	Dialogue D2;
	D2.AddMessage("Who are you?", 0);
	D2.AddMessage("I......uh.....", 1);
	D2.AddMessage("What are you doing in my house?", 0);
	D2.AddMessage("Err......um.....", 1);
	D2.AddMessage("Can you get out please", 0);
	D2.AddMessage("Uh......maybe...", 1);
	D2.AddMessage("Where am I?", 1);
	D2.AddMessage("...", 0);
	MasterDialogueList.push_back(D2);

	Dialogue D3;
	D3.AddMessage("Did you know I'm missing an arm?", 1);
	D3.AddMessage("But you're not.", 0);
	D3.AddMessage("Yes I am.", 1);
	D3.AddMessage("..what", 0);
	D3.AddMessage("I'm a magical unicorn", 1);
	D3.AddMessage("Uh...okay.", 0);
	MasterDialogueList.push_back(D3);

	Dialogue D4;
	D4.AddMessage("I want pie", 0);
	D4.AddMessage("What?", 1);
	D4.AddMessage("Pie", 0);
	D4.AddMessage("I mean, I guess I c..", 1);
	D4.AddMessage("pie pie pie pie pie \n pie pie pie pie pie", 0);
	D4.AddMessage("Fine, go get some apples.", 1);
	D4.AddMessage("CONTINUE", -1);//----------------
	D4.AddMessage("Did you get the apples yet?", 1);
	D4.AddMessage("I'll need about five.", 1);
	D4.AddMessage("LOOP", -1);
	D4.AddMessage("Ok fine now go wait for your pie", 1);
	MasterDialogueList.push_back(D4);
}

DialogueManager::~DialogueManager()
{
}

void DialogueManager::Manage(sf::Event ev, sf::RenderWindow& rw)
{
	std::vector<std::pair<std::string, int>> diaSeq = MasterDialogueList[other->dialogueID - 1].dialogueSequence;

	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
	{
		if (talkIter == diaSeq.size() - 1)
		{
			EndDialogue();
			return;
		}
		else
		{
			talkIter++;
		}
	}

	// Create two drawable objects, one for the name of the NPC and the image of it
	sf::Sprite NPCsprite;
	sf::Text NPCname;
	NPCname.setFont(Game::GetFont("Regular"));
	NPCname.setCharacterSize(30);
	NPCname.setColor(sf::Color::Black);

	if (diaSeq[talkIter].second == -1) // Flag for command instead of dialogue
	{
		if (diaSeq[talkIter].first == "LOOP") // Loop command
		{
			QuestGiver* giver = dynamic_cast<QuestGiver*>(other);
			if (giver != NULL) // Messenger is also a QuestGiver
			{
				EndDialogue(true);
			}
			else
			{
				EndDialogue();
			}
			return;
		}
		else if (diaSeq[talkIter].first == "CONTINUE") // Continue command
		{
			GetCurrentDialogue().resumeIndex = talkIter + 1;
			EndDialogue();
			return;
		}
		else
		{
			std::cout << "ERROR: INVALID DIALOGUE COMMAND CALLED" << std::endl;
			assert(false);
		}
	}
	if (diaSeq[talkIter].second == 0)
	{
		NPCsprite.setTexture(Game::GetResourceManager().Get(Game::GetPlayer()->textureName));
		NPCsprite.setTextureRect(sf::IntRect(Game::GetResourceManager().Get(Game::GetPlayer()->textureName).getSize().x * 2 / 4, 0,
			Game::GetResourceManager().Get(Game::GetPlayer()->textureName).getSize().x / 4, Game::GetResourceManager().Get(Game::GetPlayer()->textureName).getSize().y / 4));
		NPCname.setString(Game::GetPlayer()->name);
	}
	else if (diaSeq[talkIter].second == 1)
	{
		NPCsprite.setTexture(Game::GetResourceManager().Get(other->textureName));
		// Important that all character spritesheets are made with the same formula
		NPCsprite.setTextureRect(sf::IntRect(other->GetTextureRect().width * 2, 0, 
			other->GetTextureRect().width, other->GetTextureRect().height));
		// Use the same name that the Messenger was stored with;
		NPCname.setString(other->name);
	}

	NPCsprite.scale(3, 3);

	NPCsprite.setPosition(dialogueBox.GetPosition().x - SPRITE_OFFSET_X - NPCsprite.getLocalBounds().width / 2, dialogueBox.GetPosition().y - SPRITE_OFFSET_Y);
	NPCname.setPosition(dialogueBox.GetPosition().x - TEXT_OFFSET_X - NPCname.getLocalBounds().width / 2, dialogueBox.GetPosition().y - TEXT_OFFSET_Y);

	dialogueBox.SetMessage(diaSeq[talkIter].first);
	dialogueBox.Draw(rw);

	rw.draw(NPCname);
	rw.draw(NPCsprite);
}

void DialogueManager::EndDialogue(bool toInventory)
{
	if (!toInventory) // This is only dialogue; Don't go to inventory screen
	{
		if (Game::GetPlayer()->GetPosition().x > 0) // If player is in the building chunk
		{
			Game::_gameState = Game::Playing;
		}
		else
		{
			Game::_gameState = Game::InBuilding;
		}
	}
	else // Initiate Quest-giving
	{
		Game::_gameState = Game::Inventory;
	}
}

void DialogueManager::AdvanceDialogue()
{
	std::vector<std::pair<std::string, int>>::iterator it = GetCurrentDialogue().dialogueSequence.begin();
	while (it != GetCurrentDialogue().dialogueSequence.end())
	{
		if (it->second == -1)
		{
			if (it->first == "LOOP")
			{
				*it = std::make_pair("CONTINUE", -1); // Make sure that next time this is called it won't stumble on this loop again
				GetCurrentDialogue().resumeIndex = it - GetCurrentDialogue().dialogueSequence.begin() + 1; // Advance the dialogue past the loop
				return;
			}
		}
		it++;
	}
}

void DialogueManager::SetNPC(Messenger* otherM)
{
	other = otherM;
	talkIter = GetCurrentDialogue().resumeIndex; // SetNPC is called right before a dialogue sequence
}

DialogueManager::Dialogue& DialogueManager::GetCurrentDialogue()
{
	return MasterDialogueList[other->dialogueID - 1];
}