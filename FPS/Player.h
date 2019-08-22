#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int x, int y);
	virtual ~Player();

	virtual eObjectType GetObjectType() const override;

	virtual Rect GetRedertRect() const override;

	RenderTile m_Data;
};

