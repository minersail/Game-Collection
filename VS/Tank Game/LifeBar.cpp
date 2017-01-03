#include "stdafx.h"
#include "LifeBar.h"

/*
LifeBar object that comes with every entity; Is not in GameObjectManager so Draw() must be called in parent Draw() function
*/
LifeBar::LifeBar()
	: scale(1)
{
	Load("images/baroutline.png");
	assert(IsLoaded());
	texturefile = "images/baroutline.png";

	inside.loadFromFile("images/bar.png");

	healthBarRect.left = 0;
	healthBarRect.top = 0;
	healthBarRect.width = 46;
	healthBarRect.height = 4;

	healthBar.setTexture(inside);
	healthBar.setTextureRect(healthBarRect);
}

LifeBar::~LifeBar()
{
}

void LifeBar::Draw(sf::RenderWindow& rw)
{
	healthBar.setPosition(GetPosition().x + 2 * scale, GetPosition().y + 2 * scale);
	rw.draw(GetSprite());
	rw.draw(healthBar);
}

void LifeBar::SetHealth(float health, float max)
{
	healthBarRect.width = health / max * 46 * scale; // 46 being original width; Cannot use healthBarRect.width because that will change as life decreases
	healthBar.setTextureRect(healthBarRect);
}

void LifeBar::SetScale(float size)
{
	scale = size;
	healthBarRect.width *= scale;
	healthBarRect.height *= scale;
	_sprite.scale(size, size);
}