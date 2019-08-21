#include "pch.h"
#include "Box.h"

#include "GameManager.h"

Box::Box(int x, int y) : Object(x, y) { }
Box::~Box() { }

eObjectType Box::GetObjectType() const
{
	return eObjectType::Box;
}

void Box::Explosived(Bomb* a_refBomb)
{
	GameMng()->RemoveObject(this);
	GameMng()->DropItem(this);
}