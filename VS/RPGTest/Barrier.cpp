#pragma once
#include "stdafx.h"
#include "Barrier.h"
#include "Game.h"

Barrier::Barrier(float initX, float initY, std::string textureID, std::string name, int animationFrames, sf::IntRect customHitBox)
	: Entity(initX, initY, textureID, name, // Ternary operator to check if customHitBox is default to determine whether or not a
	// custom hitbox was supplied. Simply using the Texture Rect will not work since this is called before VisibleGameObject() allocates
	// the texture, and using the Get() function of the ResourceManager will not work as a default constructor as textureID is undefined in the .h
	(customHitBox == sf::IntRect(0, 0, 0, 0) ? sf::IntRect(0, 0, Game::GTS(textureID).x / animationFrames, Game::GTS(textureID).y) : customHitBox)),
	tiled(false), maxFrame(animationFrames), currentFrame(1), tiledSize(sf::Vector2f(0, 0))
{
	Animate();
	immovable = true;
}

Barrier::Barrier(float initX, float initY, std::string textureID, std::string name, sf::Vector2i size, int animationFrames, sf::IntRect customHitBox)
	: Entity(initX, initY, textureID, name, (customHitBox == sf::IntRect(0, 0, 0, 0) ? sf::IntRect(0, 0, size.x * 16, size.y * 16) : customHitBox)),
	tiled(true), maxFrame(animationFrames), currentFrame(1), tiledSize(size)
{
	// Resize VerticeList to size of Barrier
	VerticeList.setPrimitiveType(sf::Quads);
	VerticeList.resize(tiledSize.x * tiledSize.y * 4);

	Animate();

	immovable = true;
}

Barrier::~Barrier()
{
}

void Barrier::Update(float deltaTime, sf::Event ev)
{
	frameCount++;

	if (frameCount % 30 == 0)
	{
		Animate();
	}
}

void Barrier::Animate()
{
	currentFrame++;
	if (currentFrame > maxFrame)
	{
		currentFrame = 1;
	}

	if (tiled) // Barrier type 4
	{
		// Manually repeat the texture; sf::Texture.setRepeated() will not work because it interferes with animation
		for (int i = 0; i < tiledSize.x; ++i)
		{
			for (int j = 0; j < tiledSize.y; ++j)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &VerticeList[(j + i * tiledSize.y) * 4];

				// define its 4 corners
				// We subtract GetHitBox().width and height in order for GetPosition() to return the top-left corner
				quad[0].position = sf::Vector2f(GetPosition().x - GetHitBox().width / 2 + i * 16, GetPosition().y - GetHitBox().height / 2 + j * 16);
				quad[1].position = sf::Vector2f(GetPosition().x - GetHitBox().width / 2 + (i + 1) * 16, GetPosition().y - GetHitBox().height / 2 + j * 16);
				quad[2].position = sf::Vector2f(GetPosition().x - GetHitBox().width / 2 + (i + 1) * 16, GetPosition().y - GetHitBox().height / 2 + (j + 1) * 16);
				quad[3].position = sf::Vector2f(GetPosition().x - GetHitBox().width / 2 + i * 16, GetPosition().y - GetHitBox().height / 2 + (j + 1) * 16);

				// define its 4 texture coordinates
				// With animated barriers the textures should be in a straight, horizontal line, so y values do not change
				// Frames are 1-indexed, but the textures are 0-indexed, hence the (currentFrame - 1)
				quad[0].texCoords = sf::Vector2f((currentFrame - 1) * 16, 0);
				quad[1].texCoords = sf::Vector2f((currentFrame) * 16, 0);
				quad[2].texCoords = sf::Vector2f((currentFrame) * 16, 16);
				quad[3].texCoords = sf::Vector2f((currentFrame - 1) * 16, 16);
			}
		}
	}
	else // Barrier type 2
	{
		// Size of one frame
		sf::Vector2i frameSize(GetSprite().getTexture()->getSize().x / maxFrame, GetSprite().getTexture()->getSize().y);
		SetTextureRect(frameSize.x * (currentFrame - 1), 0, GetTextureRect().width, GetTextureRect().height);
	}
	collided = false;
}

void Barrier::Draw(sf::RenderWindow& rw)
{
	if (tiled)
	{
		rw.draw(VerticeList, GetSprite().getTexture());
	}
	else
	{
		rw.draw(GetSprite());
	}

	/*sf::RectangleShape hitbox;
	hitbox.setSize(sf::Vector2f(GetHitBox().width, GetHitBox().height));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setFillColor(sf::Color(255, 255, 255, 0));
	hitbox.setOutlineThickness(2);
	hitbox.setOrigin(GetHitBox().width / 2, GetHitBox().height / 2);
	hitbox.setPosition(GetPosition().x, GetPosition().y);
	rw.draw(hitbox);

	sf::CircleShape center;
	center.setRadius(3);
	center.setOrigin(1.5, 1.5);
	center.setPointCount(15);
	center.setPosition(GetPosition().x, GetPosition().y);
	center.setFillColor(sf::Color::Blue);
	rw.draw(center);*/
};