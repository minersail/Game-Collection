#pragma once
#include "stdafx.h"

class VisibleGameObject
{
public:
	/*
	Overload 1: For an object that will not be put into GameObjectManager
	Ex. for components such as life bars
	*/
	VisibleGameObject(float initX, float initY, std::string textureID);
	/*
	Overload 2: For objects that will be put into GameObjectManager
	Ex. the player
	*/
	VisibleGameObject(float initX, float initY, std::string textureID, std::string name);
	virtual ~VisibleGameObject();

	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float deltaTime, sf::Event ev);

	virtual void SetPosition(float x, float y, bool absolute = false);
	virtual void SetPosition(sf::Vector2f newPos, bool absolute = false);
	virtual void SetRotation(float angle);
	virtual void SetTextureRect(int left, int top, int width, int height);
	// Inheritable, overridable function to manage chunk data
	virtual void UpdateChunk();
	virtual void UpdateTexture(std::string newID);

	//Returns a vector containing x and y values of the sprite's center
	virtual sf::Vector2f GetPosition() const;
	virtual float GetRotation(bool useDegrees = true) const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual float GetDistance(VisibleGameObject other);

	// Returns an axis-aligned rectangle that contains the sprite including transformations -- mainly used in simple collision detection 
	virtual sf::Rect<float> GetBoundingRect() const;
	// Returns the rectangle of the texture that the sprite uses -- includes top and left coordinates for spritesheets
	virtual sf::Rect<int> GetTextureRect() const;

	// Whether or not the object is set to be destroyed at the end of the game loop
	bool pendingDestruction;
	int frameCount;
	// This is what chunk the center of the object resides in
	int ChunkID;

	// Name of the texture in the resource manager
	std::string textureName;
	// String name of the object, used to retrieve the object from the object manager
	std::string name;
	sf::Sprite& GetSprite();

private:
	sf::Sprite  _sprite;
};
