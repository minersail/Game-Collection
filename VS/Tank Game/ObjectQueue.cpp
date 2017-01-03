#include "stdafx.h"
#include "ObjectQueue.h"

ObjectQueue::ObjectQueue()
{
}

ObjectQueue::~ObjectQueue()
{
}

void ObjectQueue::Add(std::string name, VisibleGameObject* obj, std::string location)
{
	_queue.push_back(std::pair<std::pair<std::string, VisibleGameObject*>, std::string>(std::pair<std::string, VisibleGameObject*>(name, obj), location));
}