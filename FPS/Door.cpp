#include "pch.h"
#include "Door.h"

#include "GameManager.h"
#include "Player.h"

Door::Door(int x, int y) : Object(x, y)
, m_Close{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
}
, m_Open{
			{ ' ', 'D', 'D', 'D', ' ' },
			{ 'D', ' ', ' ', ' ', 'D' },
			{ 'D', ' ', ' ', ' ', 'D' },
			{ 'D', ' ', ' ', ' ', 'D' },
			{ ' ', 'D', 'D', 'D', ' ' },
} {
	m_pNowAni = &m_Close;
}

Door::~Door()
{
}

eObjectType Door::GetObjectType() const
{
	return eObjectType::Door;
}

bool Door::CanMove() const
{
	return (m_eState == eDoorState::Open);
}

void Door::Init()
{
	m_eState = eDoorState::Close;
}

bool Door::Interaction(class Player* a_refHero)
{
	if (m_eState == eDoorState::Close) { return false; }

	if (IsCross(a_refHero) == true)
	{
		GameMng()->StageEnd();
	}

	return false;
}