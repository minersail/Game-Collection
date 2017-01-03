#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class LifeBar : public VisibleGameObject
{
public:
	LifeBar();
	~LifeBar();

	void SetHealth(float health, float max);
	void Draw(sf::RenderWindow& rw);
	void SetScale(float size);

	// Scale of the healthbar
	float scale;

private:
	// Texture of the inside of the bar
	sf::Texture inside;
	// Sprite for the inside of the bar
	sf::Sprite healthBar;
	// Rectangle to control how much of the inside to display
	sf::Rect<int> healthBarRect;
};