#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Entity.h"
#include "Block.h"

class Soldier : public Entity
{
public:
	Soldier();
	Soldier(std::string filename, float life, Faction fac);
	Soldier(const Soldier& obj);
	~Soldier();

	virtual void Update(float deltaTime, sf::Event ev);
	virtual void Draw(sf::RenderWindow& rw);
	// Finds the direction of the trace and stores it in traceDir
	void GetTraceDir(Entity& hitEntity, float dx, float dy);
	void GetTarget(Faction fac);
	void Walk(); // Switches to next walking sprite
	void Fire(float angle);

	float speed;
	float range;
	/* Boolean that controls behavior of AI, whether normal straight-line behavior or obstacle tracing.
	Flipped to true when raycast to front returns true, flipped to false when obstacle is navigated. */
	bool collided;
	bool LoS;
	Entity* target;

	enum Direction
	{
		Right, Down, Left, Up, Uninitialized
	};
	Direction traceDir;

private:
	sf::Rect<int> dispRect;
};