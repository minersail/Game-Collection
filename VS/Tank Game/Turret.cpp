#include "stdafx.h"
#include "Turret.h"
#include "Game.h"
#include "Projectile.h"
#include <cmath>

Turret::Turret(std::string filename)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	GetSprite().setOrigin(GetTextureRect().width * 3/8, GetTextureRect().height / 2);
}

Turret::~Turret()
{
}

void Turret::Update(float deltaTime, sf::Event ev)
{
	sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
	sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);

	float dx = mouseCoords.x - GetPosition().x;
	float dy = mouseCoords.y - GetPosition().y;

	if (dx == 0)
		dx = 0.0001f;

	float angle = atan(dy/dx) * 180 / 3.1415926f;
	
	if (dx < 0)
	{
		angle += 180;
	}
	SetRotation(angle);

	if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
	{
		Projectile* shell = new Projectile("images/chris2.png", angle / 180 * 3.141592f, 6, Entity::Ally);
		Game::GetObjectQueue().Add("chris", shell, "back");

		float rotRad = GetRotation() / 180 * 3.141592f;
		shell->SetPosition(GetPosition().x + 50 * cos(rotRad), GetPosition().y + 50 * sin(rotRad));
	}
}