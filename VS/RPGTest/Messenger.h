#pragma once
#include "stdafx.h"
#include "UseObject.h"

/*
Object that initiates dialogue when the player activates it, such as an NPC or a sign
Not to be confused with the NPC class, which only walks around and has text pop above its head
*/
class Messenger : public UseObject
{
public:
	Messenger(float initX, float initY, std::string textureID, std::string name, int talkID);
	~Messenger();

	virtual void Update(float deltaTime, sf::Event ev);

	// Number corresponding to the dialogue stored in the DialogueManager
	// 1-indexed
	int dialogueID;
};