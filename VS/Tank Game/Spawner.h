#pragma once
#include "stdafx.h"
#include "Block.h"

template<class T>
class Spawner : public Block
{
public:
	Spawner(std::string filename, T* spawn, sf::Vector2f spawnLoc);
	~Spawner();

	void Draw(sf::RenderWindow& rw);
	void Update(float deltaTime, sf::Event ev);
	void Damage(float damage);

	sf::Vector2f SpawnLoc;
	// This template is a copy of an object passed into the constructor - this copy will be spawned over and over
	T* SpawnTemplate;
	float frameCount;
};