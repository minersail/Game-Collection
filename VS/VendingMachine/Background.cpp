#include "stdafx.h"
#include "Background.h"

Background::Background(std::string filename)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;
}

Background::~Background()
{
}