#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
	: _isLoaded(false), pendingDestruction(false), frameCount(0)
{
	//_isLoaded = false; Slightly faster to use the above constructor initialization.
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Load(std::string filename, bool tiled)
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		if (tiled)
		{
			_filename = filename;
			_image.setRepeated(true);
			_sprite.setTexture(_image);
			_isLoaded = true;
		}
		else
		{
			std::cout << "Calling this overload of Load() with false does the same thing as calling the other overload" << std::endl;
			_filename = filename;
			_sprite.setTexture(_image);
			_isLoaded = true;
		}
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

void VisibleGameObject::Update(float deltaTime, sf::Event ev)
{
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::SetPosition(sf::Vector2f newPos)
{
	if (_isLoaded)
	{
		_sprite.setPosition(newPos);
	}
}

void VisibleGameObject::SetRotation(float angle)
{
	if (_isLoaded)
	{
		_sprite.setRotation(angle);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

float VisibleGameObject::GetRotation(bool useDegrees) const
{
	if (_isLoaded)
	{
		if (useDegrees)
			return _sprite.getRotation();
		else
			return _sprite.getRotation() / 180 * 3.141592f;
	}
	return -1;
}

float VisibleGameObject::GetDistance(VisibleGameObject other)
{
	return sqrt(pow(GetPosition().x - other.GetPosition().x, 2) + pow(GetPosition().y - other.GetPosition().y, 2));
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

float VisibleGameObject::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

sf::Rect<float> VisibleGameObject::GetTextureRect() const
{
	return _sprite.getLocalBounds();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}