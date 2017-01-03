#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Game.h"

VisibleGameObject::VisibleGameObject(float initX, float initY, std::string textureID)
	: pendingDestruction(false), frameCount(0)
{
	SetPosition(initX * 16, initY * 16);
	_sprite.setTexture(Game::GetResourceManager().Get(textureID));
	ChunkID = std::floor(initX / Game::SCREEN_WIDTH * 16) + std::floor(initY / Game::SCREEN_HEIGHT * 16) * Game::YCHUNKS;
	textureName = textureID;
}

VisibleGameObject::VisibleGameObject(float initX, float initY, std::string textureID, std::string name)
	: pendingDestruction(false), frameCount(0)
{
	SetPosition(initX * 16, initY * 16);
	_sprite.setTexture(Game::GetResourceManager().Get(textureID));
	Game::GetObjectManager().Add(name, this);
	ChunkID = std::floor(initX / Game::SCREEN_WIDTH * 16) + std::floor(initY / Game::SCREEN_HEIGHT * 16) * Game::YCHUNKS;
	textureName = textureID;
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	renderWindow.draw(_sprite);
}

void VisibleGameObject::Update(float deltaTime, sf::Event ev)
{
}

void VisibleGameObject::SetPosition(float x, float y, bool absolute)
{
	if (absolute)
	{
		sf::Vector2f adjustedPos = Game::GetWindow().mapPixelToCoords(sf::Vector2i(x, y)); // Screen coordinates instead of game coordinates
		_sprite.setPosition(adjustedPos);
	}
	else
	{
		_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::SetPosition(sf::Vector2f newPos, bool absolute)
{
	if (absolute)
	{
		sf::Vector2f adjustedPos = Game::GetWindow().mapPixelToCoords(sf::Vector2i(newPos)); // Screen coordinates instead of game coordinates
		_sprite.setPosition(adjustedPos);
	}
	else
	{
		_sprite.setPosition(newPos);
	}
}

void VisibleGameObject::SetRotation(float angle)
{
	_sprite.setRotation(angle);
}

void VisibleGameObject::UpdateChunk()
{
	ChunkID = std::floor(GetPosition().x / Game::SCREEN_WIDTH) + std::floor(GetPosition().y / Game::SCREEN_HEIGHT) * Game::YCHUNKS;
}

void VisibleGameObject::UpdateTexture(std::string newID)
{
	_sprite.setTexture(Game::GetResourceManager().Get(newID));
	textureName = newID;
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	return _sprite.getPosition();
}

float VisibleGameObject::GetRotation(bool useDegrees) const
{
	if (useDegrees)
		return _sprite.getRotation();
	else
		return _sprite.getRotation() / 180 * 3.141592f;
}

float VisibleGameObject::GetDistance(VisibleGameObject other)
{
	return sqrt(pow(GetPosition().x - other.GetPosition().x, 2) + pow(GetPosition().y - other.GetPosition().y, 2));
}

float VisibleGameObject::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

sf::Rect<int> VisibleGameObject::GetTextureRect() const
{
	return _sprite.getTextureRect();
}

void VisibleGameObject::SetTextureRect(int left, int top, int width, int height)
{
	sf::Rect<int> newRect(left, top, width, height);
	_sprite.setTextureRect(newRect);
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}