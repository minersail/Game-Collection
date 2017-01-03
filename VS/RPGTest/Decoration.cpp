#pragma once
#include "stdafx.h"
#include "Decoration.h"
#include "Game.h"

Decoration::Decoration(float initX, float initY, std::string textureID, std::string name, int rotation, int animationFrames)
	: VisibleGameObject(initX, initY, textureID, name), tiled(false), maxFrame(animationFrames), currentFrame(1), tiledSize(sf::Vector2f(0, 0))
{
	SetRotation(rotation);
	Animate();
}

Decoration::Decoration(float initX, float initY, std::string textureID, std::string name, sf::Vector2i size, int rotation, int animationFrames)
	: VisibleGameObject(initX + 0.5, initY + 0.5, textureID, name), tiled(true), maxFrame(animationFrames), currentFrame(1), tiledSize(size)
{
	SetRotation(rotation);
	// Resize VerticeList to size of Decoration
	VerticeList.setPrimitiveType(sf::Quads);
	VerticeList.resize(tiledSize.x * tiledSize.y * 4);

	Animate();
}

Decoration::~Decoration()
{
}

void Decoration::Update(float deltaTime, sf::Event ev)
{
	frameCount++;

	if (frameCount % 30 == 0)
	{
		Animate();
	}
}

void Decoration::Animate()
{
	currentFrame++;
	if (currentFrame > maxFrame)
	{
		currentFrame = 1;
	}

	if (tiled) // Decoration type 4
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
				quad[0].position = sf::Vector2f(GetPosition().x - GetTextureRect().width / 2 + i * 16, GetPosition().y - GetTextureRect().height / 2 + j * 16);
				quad[1].position = sf::Vector2f(GetPosition().x - GetTextureRect().width / 2 + (i + 1) * 16, GetPosition().y - GetTextureRect().height / 2 + j * 16);
				quad[2].position = sf::Vector2f(GetPosition().x - GetTextureRect().width / 2 + (i + 1) * 16, GetPosition().y - GetTextureRect().height / 2 + (j + 1) * 16);
				quad[3].position = sf::Vector2f(GetPosition().x - GetTextureRect().width / 2 + i * 16, GetPosition().y - GetTextureRect().height / 2 + (j + 1) * 16);

				int offset = GetRotation() / 90;

				// define its 4 texture coordinates
				// With animated Decorations the textures should be in a straight, horizontal line, so y values do not change
				// Frames are 1-indexed, but the textures are 0-indexed, hence the (currentFrame - 1)
				quad[offset].texCoords = sf::Vector2f((currentFrame - 1) * 16, 0);
				quad[1 + offset > 3 ? 1 + offset - 4 : 1 + offset].texCoords = sf::Vector2f((currentFrame) * 16, 0);
				quad[2 + offset > 3 ? 2 + offset - 4 : 2 + offset].texCoords = sf::Vector2f((currentFrame)* 16, 16);
				quad[3 + offset > 3 ? 3 + offset - 4 : 3 + offset].texCoords = sf::Vector2f((currentFrame - 1) * 16, 16);
			}
		}
	}
	else // Decoration type 2
	{
		// Size of one frame
		sf::Vector2i frameSize(GetSprite().getTexture()->getSize().x / maxFrame, GetSprite().getTexture()->getSize().y);
		SetTextureRect(frameSize.x * (currentFrame - 1), 0, GetTextureRect().width, GetTextureRect().height);
	}
}

void Decoration::Draw(sf::RenderWindow& rw)
{
	if (tiled)
	{
		rw.draw(VerticeList, GetSprite().getTexture());
	}
	else
	{
		rw.draw(GetSprite());
	}
};