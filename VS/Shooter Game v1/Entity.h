#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "LifeBar.h"

// Class that is the base of all objects with collision
class Entity : public VisibleGameObject
{
public:
	Entity();
	~Entity();
	virtual void Update(float deltaTime, sf::Event ev);
	virtual void Draw(sf::RenderWindow& rw);

	// Gets vertices of rectangle, regardless of rotation
	std::vector<sf::Vector2f> GetVertices() const;
	// Gets axes (normal vectors) from a list of vertices
	std::vector<sf::Vector2f> GetAxes(std::vector<sf::Vector2f> VertVect) const;
	// Gets the projection of the shape onto an axis given its vertices. Yeah, I have no idea how this works either
	sf::Vector2f GetProjection(sf::Vector2f Axis, std::vector<sf::Vector2f> VertVect) const;
	// Checks for collision, even with rotated rectangles, and stores the MTV in MTV
	bool CheckForCollision(Entity* other);
	virtual void Damage(float damage);
	void RemoveFromList(Entity* obj, std::vector<Entity*>& List);
	/* X and Y coordinates in pixels above and to the left for location of life bar */
	void UpdateLifeBar(int xOffset, int yOffset);
	/* Replaces destructor, as destructor is not working */
	virtual void Destroy();

	/* Minimum Translation Vector, the smallest vector required
	to push two objects out of intersection; First item is
	direction, second is magitude */
	std::pair<sf::Vector2f, float> MTV;

	enum Faction
	{
		Ally, Enemy, Neutral
	};

	float health;
	float healthMax;
	Faction faction;
	bool infantry;

	LifeBar LifeBar;
	bool drawLifeBar;
};