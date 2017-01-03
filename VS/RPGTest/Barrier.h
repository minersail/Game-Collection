#pragma once
#include "stdafx.h"
#include "Entity.h"

/*
Barrier allows for four combinations of blocking objects:
1. Non-animated, non-tiled barriers
2. Animated, non-tiled barriers (requires a texture that has different frames laid out horizontally)
3. Non-animated, tiled barriers (tile must be 16x16)
4. Animated, tiled barriers (frames must be both laid out horizontally and 16x16)
*/
class Barrier : public Entity
{
public:
	Barrier(float initX, float initY, std::string textureID, std::string name, int animationFrames = 1, sf::IntRect customHitBox = sf::IntRect(0, 0, 0, 0));
	// If tiled texture is used, size determines 16x16 tiles in both directions
	Barrier(float initX, float initY, std::string textureID, std::string name, sf::Vector2i size, int animationFrames = 1, sf::IntRect customHitBox = sf::IntRect(0, 0, 0, 0));
	~Barrier();

	virtual void Update(float deltaTime, sf::Event ev);
	virtual void Draw(sf::RenderWindow& rw);

	virtual void Animate();

private:
	// Whether or not the barrier is tiled
	bool tiled;

	sf::VertexArray VerticeList;
	// If tiled is true, this is the size, in 16x16 tiles, of the sprite
	sf::Vector2i tiledSize;

	int currentFrame;
	int maxFrame;
};