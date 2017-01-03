#include "stdafx.h"
#include "Entity.h"
#include "Game.h"

Entity::Entity(float initX, float initY, std::string textureID, std::string name)
	: MTV(std::pair<sf::Vector2f, float>(sf::Vector2f(0, 0), FLT_MAX)), HitBox(0, 0, 0, 0),
	VisibleGameObject(initX, initY, textureID, name), collided(false), immovable(false), drawHitBox(false)
{
	SetHitBox(GetTextureRect());
	InitializeChunks();
}

Entity::Entity(float initX, float initY, std::string textureID, std::string name, sf::IntRect customHB)
	: MTV(std::pair<sf::Vector2f, float>(sf::Vector2f(0, 0), FLT_MAX)), HitBox(0, 0, 0, 0),
	VisibleGameObject(initX, initY, textureID, name), collided(false), immovable(false), drawHitBox(false)
{
	SetHitBox(customHB);
	InitializeChunks();
}

Entity::~Entity()
{
	// Remove from EntityList
}

void Entity::Update(float deltaTime, sf::Event ev)
{
}

std::vector<sf::Vector2f> Entity::GetVertices()
{
	std::vector<sf::Vector2f> VertexList;
	float angle = GetRotation(false); // Current rotation in radians
	float offset = sqrt(pow(GetHitBox().width / 2, 2) + pow(GetHitBox().height / 2, 2)); // Length of diagonal from center to corner
	float angleoffset = atan2f(GetHitBox().height, GetHitBox().width); // Angle theta between horizontal and diagonal
	float PI = 3.1415926535f; // Apple, of course

	float x = GetPosition().x;
	float y = GetPosition().y;

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
	std::pair<sf::Vector2f, float> TestMTV;

	TestMTV.second = FLT_MAX;

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
			if (olap < TestMTV.second)
			{
				TestMTV.second = olap;
				TestMTV.first = axis;
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
			if (olap < TestMTV.second)
			{
				TestMTV.second = olap;
				TestMTV.first = axis;
			}
		}
	}

	//---------If you have gotten this far there has been a collision---------//

	sf::Vector2f centerVect = other->GetPosition() - GetPosition();
	if (centerVect.x * TestMTV.first.x + centerVect.y * TestMTV.first.y < 0)
	{
		TestMTV.first = sf::Vector2f(-TestMTV.first.x, -TestMTV.first.y);
	}
		
	MTV = TestMTV;

	if (immovable && !other->immovable)
	{
		other->SetPosition(other->GetPosition().x + MTV.first.x * MTV.second, other->GetPosition().y + MTV.first.y * MTV.second);
	}
	else if (!immovable && other->immovable)
	{
		SetPosition(GetPosition().x - MTV.first.x * MTV.second, GetPosition().y - MTV.first.y * MTV.second);
	}
	else if (!immovable && !other->immovable)
	{
		SetPosition(GetPosition().x - MTV.first.x * MTV.second / 2, GetPosition().y - MTV.first.y * MTV.second / 2);
		other->SetPosition(other->GetPosition().x + MTV.first.x * MTV.second / 2, other->GetPosition().y + MTV.first.y * MTV.second / 2);
	}

	other->MTV.first = MTV.first;
	other->MTV.second = -MTV.second;
	return true;
}

void Entity::SetHitBox(int left, int top, int width, int height)
{
	sf::Rect<int> newRect(left, top, width, height);

	SetHitBox(newRect);
}

void Entity::SetHitBox(sf::Rect<int> newRect)
{
	if (HitBox == sf::IntRect(0, 0, 0, 0)) // This is the first initialization of the HitBox
	{
		// Collision calculations require the origin to be at center
		GetSprite().setOrigin(newRect.width / 2 + newRect.left, newRect.height / 2 + newRect.top);
		// Account for change in position from setting origin
		SetPosition(GetPosition().x + newRect.width / 2 + newRect.left, GetPosition().y + newRect.height / 2 + newRect.top);
	}
	else
	{
		float dL = HitBox.left - newRect.left;
		float dT = HitBox.top - newRect.top;
		float dW = HitBox.width - newRect.width;
		float dH = HitBox.height - newRect.height;

		// Collision calculations require the origin to be at center
		GetSprite().setOrigin(newRect.width / 2 + newRect.left, newRect.height / 2 + newRect.top);
		// Account for change in position from setting origin
		SetPosition(GetPosition().x + dW + dL / 2, GetPosition().y + dH + dT / 2);
	}

	HitBox = newRect;
}

sf::Rect<int> Entity::GetHitBox()
{
	return HitBox;
}

void Entity::InitializeChunks()
{
	// Math is easier when you start at the top left
	sf::Vector2f topLeft(GetPosition().x - GetHitBox().width / 2, GetPosition().y - GetHitBox().height / 2);

	int topLeftChunk = std::floor(topLeft.x / Game::SCREEN_WIDTH) + std::floor((topLeft.y / Game::SCREEN_HEIGHT)) * Game::XCHUNKS;
	int botRightChunk = std::floor((topLeft.x + GetHitBox().width - 16) / Game::SCREEN_WIDTH) + 
						std::floor((topLeft.y + GetHitBox().height - 16) / Game::SCREEN_HEIGHT) * Game::XCHUNKS;

	if (topLeftChunk == botRightChunk)
	{
		Game::GetCollisionManager().Add(ChunkID, this);
	}
	else // The entity occupies more than one chunk
	{
		int topRightChunk = std::floor((topLeft.x + GetHitBox().width - 16) / Game::SCREEN_WIDTH) + std::floor((topLeft.y) / Game::SCREEN_HEIGHT) * Game::XCHUNKS;
		int botLeftChunk = std::floor(topLeft.x / Game::SCREEN_WIDTH) + std::floor((topLeft.y + GetHitBox().height - 16) / Game::SCREEN_HEIGHT) * Game::XCHUNKS;

		int chunksX = topRightChunk - topLeftChunk + 1; // How many chunks in the x direction the entity occupies
		int chunksY = (botLeftChunk - topLeftChunk) / Game::XCHUNKS + 1; // How many chunks in the y direction the entity occupies

		for (int i = 0; i < chunksY; i++)
		{
			for (int j = 0; j < chunksX; j++)
			{
				Game::GetCollisionManager().Add(topLeftChunk + i * Game::XCHUNKS + j, this); // Add the entity to the EntityLists of all the chunks it occupies
			}
		}
	}
}

void Entity::Draw(sf::RenderWindow& rw)
{
	if (drawHitBox)
	{
		sf::RectangleShape hitbox;
		hitbox.setSize(sf::Vector2f(GetHitBox().width, GetHitBox().height));
		hitbox.setOutlineColor(sf::Color::Red);
		hitbox.setFillColor(sf::Color(255, 255, 255, 0));
		hitbox.setOutlineThickness(2);
		hitbox.setOrigin(GetHitBox().width / 2, GetHitBox().height / 2);
		hitbox.setPosition(GetPosition().x, GetPosition().y);
		rw.draw(hitbox);
	}
	rw.draw(GetSprite());
}