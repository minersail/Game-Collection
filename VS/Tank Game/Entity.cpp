#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
	: health(50), healthMax(50), faction(Neutral), MTV(std::pair<sf::Vector2f, float>(sf::Vector2f(0, 0), FLT_MAX))
{
	// Just for some default values
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime, sf::Event ev)
{
}

std::vector<sf::Vector2f> Entity::GetVertices() const
{
	std::vector<sf::Vector2f> VertexList;
	float angle = GetRotation(); // Current rotation
	float offset = sqrt(pow(_sprite.getLocalBounds().width / 2, 2) + pow(_sprite.getLocalBounds().height / 2, 2)); // Length of diagonal from center to corner
	float angleoffset = atan2f(_sprite.getLocalBounds().height, _sprite.getLocalBounds().width); // Angle theta between horizontal and diagonal
	float PI = 3.1415926535f; // Apple, of course

	float x = GetPosition().x; // Syntatic
	float y = GetPosition().y; // Sugar

	angle = angle / 180 * PI;

	sf::Vector2f vert1(x + offset * cos(angle + angleoffset), y + offset * sin(angle + angleoffset)); // Quadrant 4
	sf::Vector2f vert2(x + offset * cos(angle + PI - angleoffset), y + offset * sin(angle + PI - angleoffset)); // Quadrant 3
	sf::Vector2f vert3(x + offset * cos(angle - PI + angleoffset), y + offset * sin(angle - PI + angleoffset)); // Quadrant 2
	sf::Vector2f vert4(x + offset * cos(angle - angleoffset), y + offset * sin(angle - angleoffset)); // Quadrant 1

	VertexList.push_back(vert1);
	VertexList.push_back(vert2);
	VertexList.push_back(vert3);
	VertexList.push_back(vert4);
	return VertexList;
}

std::vector<sf::Vector2f> Entity::GetAxes(std::vector<sf::Vector2f> VertVect) const
{
	std::vector<sf::Vector2f> AxisVect;

	for (int i = 0; i < VertVect.size(); i++)
	{
		sf::Vector2f v1 = VertVect[i]; // Get first vertice
		sf::Vector2f v2 = VertVect[i + 1 == VertVect.size() ? 0 : i + 1]; // Get second vertice
		sf::Vector2f edge = v1 - v2; // Get vector representing edge of shape
		sf::Vector2f normal(edge.y, -edge.x); // Get the normal (a vector perpendicular to the edge)

		// Normalize the normal vector (turn it into a unit vector)
		float length = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
		normal.x /= length;
		normal.y /= length;

		AxisVect.push_back(normal);
	}
	return AxisVect;
}


sf::Vector2f Entity::GetProjection(sf::Vector2f Axis, std::vector<sf::Vector2f> VertVect) const
{
	float min = Axis.x * VertVect[0].x + Axis.y * VertVect[0].y;
	float max = min;

	for (int i = 1; i < VertVect.size(); i++)
	{
		float p = Axis.x * VertVect[i].x + Axis.y * VertVect[i].y;
		if (p < min)
			min = p;
		else if (p > max)
			max = p;
	}
	sf::Vector2f proj(min, max);
	return proj;
}

/*
Checks for whether or not the two shapes are overlapping, and stores the MTV in MTV
*/
bool Entity::CheckForCollision(Entity* other)
{
	MTV.second = FLT_MAX;

	std::vector<sf::Vector2f> VertVect = GetVertices(); // All the vertices of current shape; Represents the shape in projections
	std::vector<sf::Vector2f> AxisVect = GetAxes(VertVect);

	std::vector<sf::Vector2f> VertVect2 = other->GetVertices(); // All the vertices of colliding shape; Represents the shape in projections
	std::vector<sf::Vector2f> AxisVect2 = other->GetAxes(VertVect2);

	for (int i = 0; i < AxisVect.size(); i++)
	{
		sf::Vector2f axis = AxisVect[i];
		// project both shapes onto the axis
		sf::Vector2f pB = GetProjection(axis, VertVect); // pB and pT aren't really vectors, they're projections:
		sf::Vector2f pT = GetProjection(axis, VertVect2); // lines parallel to an axis with x representing the minimum and y the maximum

		if (pB.x > pT.y || pB.x > pT.y) // Projections do not overlap  
		{															   //****************************************************************************************************************//
			// Shapes are guaranteed not to overlap					   // The collision here uses the separating axis theorem, which states that if you project two shapes onto every axis 
			return false;											   // formed by a normal vector, collision is only true if the projections of both shapes overlap on every single axis.
		}															   // This is convenient because when two projections on any axis do not overlap, the shapes do not overlap.
		else // Projections do overlap                                 //****************************************************************************************************************//
		{
			// get the overlap
			float olap = std::min(pB.y, pT.y) - std::max(pB.x, pT.x);


			// check for minimum
			if (olap < MTV.second)
			{
				MTV.second = olap;
				MTV.first = axis;
			}
		}
	}

	for (int i = 0; i < AxisVect2.size(); i++)
	{
		sf::Vector2f axis = AxisVect2[i];
		// project both shapes onto the axis
		sf::Vector2f pB = GetProjection(axis, VertVect);
		sf::Vector2f pT = GetProjection(axis, VertVect2);
		// do the projections overlap?
		if (pB.x > pT.y || pB.x > pT.y) // Projections do not overlap
		{
			// Shapes are guaranteed not to overlap
			return false;
		}
		else // Projections do overlap 
		{
			// get the overlap
			float olap = std::min(pB.y, pT.y) - std::max(pB.x, pT.x);


			// check for minimum
			if (olap < MTV.second)
			{
				MTV.second = olap;
				MTV.first = axis;
			}
		}
	}

	sf::Vector2f centerVect = other->GetPosition() - GetPosition();
	if (centerVect.x * MTV.first.x + centerVect.y * MTV.first.y < 0)
	{
		MTV.first = sf::Vector2f(-MTV.first.x, -MTV.first.y);
	}
	return true;
}

void Entity::Damage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		pendingDestruction = true;
	}
}

void Entity::RemoveFromList(Entity* obj, std::vector<Entity*>& List)
{
	std::vector<Entity*>::iterator iter = List.begin();
	while (iter != List.end())
	{
		if (*iter == obj)
		{
			List.erase(iter);
			return;
		}
		iter++;
	}
}