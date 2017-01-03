#include "stdafx.h"
#include "VisibleGameObject.h"

class Background : public VisibleGameObject
{
public:
	Background(std::string filename);
	~Background();
};