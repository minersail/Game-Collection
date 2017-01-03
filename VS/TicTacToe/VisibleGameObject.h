#pragma once
#include "stdafx.h"

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	/////////Most of this is from tank game and not used in this game/////////
	virtual void Load(std::string filename);
	virtual void Load(std::string filename, bool tiled);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float deltaTime, sf::Event ev);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(sf::Vector2f newPos);
	virtual void SetRotation(float angle);
	//Returns a vector containing x and y values of the sprite's center
	virtual sf::Vector2f GetPosition() const;
	virtual float GetRotation(bool useDegrees = true) const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual float GetDistance(VisibleGameObject other);

	virtual sf::Rect<float> GetBoundingRect() const;
	virtual sf::Rect<float> GetTextureRect() const;

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
