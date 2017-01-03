#pragma once
#include "stdafx.h"
#include "Entity.h"

/*
Base class for any class that the player can face and press space to interact with
*/
class UseObject : public Entity
{
public:
	struct UsePoint
	{
		int x;
		int y;
		Direction dir;

		// X and Y values are using the 16x16 coordinate system, not pixels
		UsePoint(int X, int Y,Direction Dir)
		{
			dir = Dir;
			x = X;
			y = Y;
		}
	};

	// This constructor takes in one activation point
	UseObject(float initX, float initY, std::string textureID, std::string name, UsePoint point);
	// This constructor takes in a vector of given points
	UseObject(float initX, float initY, std::string textureID, std::string name, std::vector<UsePoint> points);
	// Constructor that only takes in a hitbox and requires the inherited class to set the UsePoints
	UseObject(float initX, float initY, std::string textureID, std::string name, sf::IntRect hitbox);
	~UseObject();

	std::vector<UsePoint>& GetActivationLocations();
	// Returns true if the player is overlapping one of the UsePoints with the correct direction
	bool CheckUsePoints(sf::Event ev);

private:
	std::vector<UsePoint> activationLocs;
};