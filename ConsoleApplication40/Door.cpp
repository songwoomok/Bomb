#include "pch.h"
#include "Door.h"

#include "GameManager.h"

Door::Door(int x, int y) : Object(x, y)
{
}


Door::~Door()
{
}

eObjectType Door::GetObjectType() const
{
	return eObjectType::Door;
}

void Door::Init()
{
	m_eState = eDoorState::Close;
}

void Door::Interaction(class Hero* a_refHero)
{
	if (m_eState == eDoorState::Close) { return; }

	GameMng()->StageStart();
}