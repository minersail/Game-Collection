#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

// Class that is the base of all objects with collision
class Entity : public VisibleGameObject
{
public:
	Entity(float initX, float initY, std::string textureID, std::string name);
	// Constructor used if hit box is not the same as texture size
	Entity(float initX, float initY, std::string textureID, std::string name, sf::IntRect customHB);
	~Entity();
	virtual void Update(float deltaTime, sf::Event ev);
	virtual void Draw(sf::RenderWindow& rw);

	// Gets vertices of rectangle, regardless of rotation
	std::vector<sf::Vector2f> GetVertices();
	// Gets axes (normal vectors) from a list of vertices
	std::vector<sf::Vector2f> GetAxes(std::vector<sf::Vector2f> VertVect) const;
	// Gets the projection of the shape onto an axis given its vertices. Yeah, I have no idea how this works either
	sf::Vector2f GetProjection(sf::Vector2f Axis, std::vector<sf::Vector2f> VertVect) const;
	// Checks for collision, even with rotated rectangles, and stores the MTV in MTV
	bool CheckForCollision(Entity* other);

	void SetHitBox(int left, int top, int width, int height);
	void SetHitBox(sf::Rect<int> newRect);
	sf::Rect<int> GetHitBox();

	void InitializeChunks();

	/* Minimum Translation Vector, the smallest vector required
	to push two objects out of intersection; First item is
	direction, second is magitude */
	std::pair<sf::Vector2f, float> MTV;
	// Boolean for whether or not the entity has registered a collision this tick
	bool collided;
	bool immovable;
	bool drawHitBox;

	enum Direction
	{
		Up, Down, Left, Right, None
	};

private:
	sf::IntRect HitBox;
};