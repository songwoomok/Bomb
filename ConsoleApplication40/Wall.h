#pragma once
#include "Object.h"
class Wall : public Object
{
public:
	Wall(int x, int y);
	virtual ~Wall();

	virtual eObjectType GetObjectType() const override;
	RenderTile m_Data;
};

