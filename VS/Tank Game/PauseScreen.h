#pragma once
#include "stdafx.h"
#include "Button.h"

class PauseScreen : public VisibleGameObject
{
public:
	PauseScreen();
	~PauseScreen();

	void Show(sf::RenderWindow& rw, sf::Event ev);

private:
	Button ResumeButton;
	Button ReinforceButton;
	Button SwarmButton;
	Button WorldButton;
	sf::Texture bgtexture;
	sf::Sprite background;
};