#include "stdafx.h"
#include "Map.h"

Map::Map(std::string filename)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;
}

Map::~Map()
{
}