#include "stdafx.h"
#include "Map.h"
#include <fstream>

Map::Map(float initX, float initY, std::string textureID, std::string name, sf::Vector2i tileSize, int* tiles, int width, int height)
	: VisibleGameObject(initX, initY, textureID, name)
{
	// resize the vertex array to fit the level size
	VerticeList.setPrimitiveType(sf::Quads);
	VerticeList.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (GetSprite().getTexture()->getSize().x / tileSize.x);
			int tv = tileNumber / (GetSprite().getTexture()->getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &VerticeList[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(GetPosition().x + i * tileSize.x, GetPosition().y + j * tileSize.y);
			quad[1].position = sf::Vector2f(GetPosition().x + (i + 1) * tileSize.x, GetPosition().y + j * tileSize.y);
			quad[2].position = sf::Vector2f(GetPosition().x + (i + 1) * tileSize.x, GetPosition().y + (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(GetPosition().x + i * tileSize.x, GetPosition().y + (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
}

Map::Map(float initX, float initY, std::string textureID, std::string name, sf::Vector2i tileSize, std::string mapname, int width, int height)
	: VisibleGameObject(initX, initY, textureID, name)
{
	int* tileMap = new int[width * height];
	LoadMap(mapname, tileMap, width, height);

	// resize the vertex array to fit the level size
	VerticeList.setPrimitiveType(sf::Quads);
	VerticeList.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tileMap[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (GetSprite().getTexture()->getSize().x / tileSize.x);
			int tv = tileNumber / (GetSprite().getTexture()->getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &VerticeList[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(GetPosition().x + i * tileSize.x, GetPosition().y + j * tileSize.y);
			quad[1].position = sf::Vector2f(GetPosition().x + (i + 1) * tileSize.x, GetPosition().y + j * tileSize.y);
			quad[2].position = sf::Vector2f(GetPosition().x + (i + 1) * tileSize.x, GetPosition().y + (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(GetPosition().x + i * tileSize.x, GetPosition().y + (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
}

Map::~Map()
{
}

void Map::LoadMap(std::string filename, int* tiles, int width, int height)
{
	std::ifstream inputfile(filename);
	std::string map;

	for (int i = 0; i < height; i++)
	{
		std::getline(inputfile, map);
		for (int j = 0; j < width * 4; j += 4)
		{
			int num1 = (map[j] - '0') * 10;
			int num2 = map[j + 1] - '0';

			tiles[i * height + j / 4] = num1 + num2;
		}
	}
	inputfile.close();
}

void Map::Draw(sf::RenderWindow& rw)
{
	rw.draw(VerticeList, GetSprite().getTexture());
}