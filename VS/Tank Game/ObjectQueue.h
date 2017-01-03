#include "stdafx.h"
#include "VisibleGameObject.h"

// Class for holding newly created objects that will transfer into the game object manager at the end of each update cycle
class ObjectQueue
{
public:
	ObjectQueue();
	~ObjectQueue();

	/* Standard name/object pair for first two arguments, then "front" or "back" for third argument depending on where the object should go in the game manager.
	"front" means the object will be drawn first and thus under tanks and entities, "back" means that the object will be drawn over tanks and other entities. */ 
	void Add(std::string name, VisibleGameObject* obj, std::string location);

	std::vector<std::pair<std::pair<std::string, VisibleGameObject*>, std::string>> _queue;
};