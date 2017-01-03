#pragma once
#include "stdafx.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Load(std::string filename, std::string texturename);
	sf::Texture& Get(std::string texturename);

private:
	std::map<std::string, sf::Texture*> TextureList;
};