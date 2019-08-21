#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(int x, int y);
	virtual ~Item();

	virtual eObjectType GetObjectType() const override;
	virtual void Interaction(class Hero* a_refHero) override;

	eItem m_eType = eItem::None;
	RenderTile m_Item[(int)eItem::Max];
};

