#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

/*
Decoration allows for four combinations of decorations:
1. Non-animated, non-tiled Decorations
2. Animated, non-tiled Decorations (requires a texture that has different frames laid out horizontally)
3. Non-animated, tiled Decorations (tile must be 16x16)
4. Animated, tiled Decorations (frames must be both laid out horizontally and 16x16)
*/
class Decoration : public VisibleGameObject
{
public:
	Decoration(float initX, float initY, std::string textureID, std::string name, int rotation = 0, int animationFrames = 1);
	// If tiled texture is used, size determines 16x16 tiles in both directions
	Decoration(float initX, float initY, std::string textureID, std::string name, sf::Vector2i size, int rotation = 0, int animationFrames = 1);
	~Decoration();

	virtual void Update(float deltaTime, sf::Event ev);
	virtual void Draw(sf::RenderWindow& rw);

	virtual void Animate();

private:
	// Whether or not the Decoration is tiled
	bool tiled;

	sf::VertexArray VerticeList;
	// If tiled is true, this is the size, in 16x16 tiles, of the sprite
	sf::Vector2i tiledSize;

	int currentFrame;
	int maxFrame;
};