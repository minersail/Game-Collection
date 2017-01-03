#include "stdafx.h"
#include "NPC.h"
#include "Game.h"

NPC::NPC(float initX, float initY, std::string textureID, std::string name, sf::IntRect customHitBox)
	: Character(initX, initY, textureID, name)
{
	frameCount = rand() % 120;
	messageList.push_back(""); // Blank state of pausing between talking
	messageList.push_back("Welcome to MSJ open house");
	messageList.push_back("I hope you have a good time today!");
	messageList.push_back("We have many demonstrations open right now.");
	messageList.push_back("This game was written in C++.");
	messageList.push_back("Mr. Lucas is the guy in the green shirt.");
	/*
	messageList.push_back("Wow, it's slightly unconfortable \nout, Joe must be nearby");
	messageList.push_back("Don't you think that\nLIBERALS are awesome?");
	messageList.push_back("You know, I heard Joe reproduces \nby budding.");
	messageList.push_back("If you think this game is rigged:\nIt is.");
	messageList.push_back("EU4 is better than\nCiv 5");
	messageList.push_back("Doctor Who is overrated");
	messageList.push_back("Hamachi was a great invention");
	messageList.push_back("I'm taking US History over the \nsummer so I can have more Mr. Beck!");
	messageList.push_back("I really like doing \nPrezi presentations");
	messageList.push_back("Ronald Reagan was ok \nI guess");
	messageList.push_back("Des Stone's photography is\nbetter than Joe's");
	messageList.push_back("Modded gameplay is the lifeblood\nof gaming");
	messageList.push_back("I'm feeling the Bern \nso much that I'm sweating");
	messageList.push_back("Apple is better than Android");
	messageList.push_back("Who wants Carbon Leaf \nwhen you can have carbs \nand beef?");
	messageList.push_back("I'm so hyped about being hyped!");
	messageList.push_back("Global warming's not real \nI saw a snowball the other day");*/

	message.setFont(Game::GetFont("Regular"));
	message.setCharacterSize(12);
	message.setColor(sf::Color(0, 0, 0));
	message.setString(messageList[0]);
	message.setOrigin(message.getLocalBounds().width / 2, message.getLocalBounds().height / 2);

	speed = 1;
}

NPC::~NPC()
{
}

void NPC::Update(float deltaTime, sf::Event ev)
{
	UpdateChunk();

	if (frameCount % 120 == 0)
	{
		npcDirection = static_cast<Direction>(rand() % 5);
	}

	if (frameCount % 300 == 0)
	{
		message.setString(messageList[0]);
		message.setOrigin(message.getLocalBounds().width / 2, message.getLocalBounds().height / 2);
	}

	else if (frameCount % 150 == 0)
	{
		message.setString(messageList[(rand() % messageList.size() - 1) + 1]);
		message.setOrigin(message.getLocalBounds().width / 2, message.getLocalBounds().height / 2);
	}

	Walk(npcDirection);

	if (lastPosition.x == GetPosition().x && lastPosition.y == GetPosition().y && npcDirection != None)
	{
		frameCount = 120;
	}

	message.setPosition(GetPosition().x, GetPosition().y - GetTextureRect().height);
	lastPosition.x = GetPosition().x;
	lastPosition.y = GetPosition().y;
}

void NPC::Draw(sf::RenderWindow& rw)
{
	rw.draw(GetSprite());
	rw.draw(message);
}