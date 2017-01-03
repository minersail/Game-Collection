#pragma once
#include "stdafx.h"
#include "MessageBox.h"
#include "Messenger.h"

/*
Singleton class designed to manage dialogue
*/
class DialogueManager
{
public:
	DialogueManager();
	~DialogueManager();

	void Manage(sf::Event ev, sf::RenderWindow& rw);
	void EndDialogue(bool toInventory = false);
	void SetNPC(Messenger* otherM);

	// Struct that contains information about all dialogue for a single character
	struct Dialogue
	{
		// The actual dialogue
		std::vector<std::pair<std::string, int>> dialogueSequence;
		// For characters whose dialogue changes after quests, etc., this is the continue point
		int resumeIndex;

		Dialogue()
		{
			resumeIndex = 0;
		}

		// First parameter is the dialogue message, second is an ID to tell which character is talking
		// -1 represents a break in dialogue, 0 is always Joe, 1+ is for other NPCs
		void AddMessage(std::string message, int playerID)
		{
			dialogueSequence.push_back(std::make_pair(message, playerID));
		}
	};

	Dialogue& GetCurrentDialogue();
	void AdvanceDialogue();

	std::vector<Dialogue> MasterDialogueList;

private:
	MessageBox dialogueBox;
	// Change to vector later
	Messenger* other;

	int talkIter;

	// Offsets from the center of the MessageBox
	static const int SPRITE_OFFSET_X = 335;
	static const int SPRITE_OFFSET_Y = 30;
	static const int TEXT_OFFSET_X = 320;
	static const int TEXT_OFFSET_Y = 70;
};