#pragma once
#include "stdafx.h"

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Load(std::string filename, bool tiled);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float deltaTime, sf::Event ev);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(sf::Vector2f newPos);
	// Takes in argument of angle in degrees
	virtual void SetRotation(float angleDeg);
	//Returns a vector containing x and y values of the sprite's center
	virtual sf::Vector2f GetPosition() const;
	virtual float GetRotation(bool useDegrees = true) const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual float GetDistance(VisibleGameObject other);

	// Returns an axis-aligned box that would fit the entire sprite, rotated and all
	virtual sf::Rect<float> GetBoundingRect() const;
	// Returns the bounds of the current sprite
	virtual sf::Rect<float> GetSpriteRect() const;
	// Returns the bounds of the current texture rect; Similar to 
	// GetSpriteRect(), except the top and left values may be different
	virtual sf::IntRect GetTextureRect() const;
	virtual void SetTextureRect(int left, int top, int width, int height);

	virtual bool IsLoaded() const;
	bool pendingDestruction;
	float frameCount;
	
	//Name of the file used to load the texture
	std::string texturefile;
	//String name of the object, used to retrieve the object from the object manager
	std::string name;
	sf::Sprite& GetSprite();

protected:
	sf::Sprite  _sprite;

private:
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
};
