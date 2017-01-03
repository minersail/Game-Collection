#include "stdafx.h"
#include "MessageBox.h"
#include "Game.h"

MessageBox::MessageBox(float initX, float initY, std::string message, int size, sf::Color color)
	: VisibleGameObject(0, 0, "Message Box") // VisibleGameObject constructor is not used except for texture loading
	// since the MessageBox is drawn relative to the screen, not the game world
{
	SetColor(color);
	SetSize(size);
	SetMessage(message);
	SetFont(Game::GetFont("Regular"));

	// Origin is nice so we can set the text and the sprite on the same spot
	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
	GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT - GetHeight() / 2);
	GetText().setPosition(GetPosition().x, GetPosition().y);
}

MessageBox::~MessageBox()
{
}

void MessageBox::Draw(sf::RenderWindow& rw)
{
	SetPosition(400, 720, true);
	text.setPosition(GetPosition());

	rw.draw(GetSprite());
	rw.draw(text);
}

void MessageBox::SetColor(sf::Color color)
{
	fontColor = color;
	text.setColor(color);
}

void MessageBox::SetSize(int size)
{
	fontSize = size;
	text.setCharacterSize(size);
}

void MessageBox::SetMessage(std::string mess)
{
	message = mess;
	text.setString(mess);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
}

void MessageBox::SetFont(sf::Font& font)
{
	text.setFont(font);
}

sf::Text& MessageBox::GetText()
{
	return text;
}