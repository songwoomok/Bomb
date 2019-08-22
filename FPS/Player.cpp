#include "pch.h"
#include "Player.h"

#include "GameManager.h"


Player::Player(int x, int y) : Object(x, y)
, m_Data{
		{ ' ', ' ', ' ', ' ', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', 'P', ' ', 'P', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', ' ', ' ', ' ', ' ' } }
{
	m_pNowAni = &m_Data;

	rt.x += 1;
	rt.y += 1;
	rt.w = TileSize - 2;
	rt.h = TileSize - 2;
}


Player::~Player()
{
	m_refStat = nullptr;
}

eObjectType Player::GetObjectType() const
{
	return eObjectType::Player;
}


Rect Player::GetRedertRect() const
{
	return Rect{ rt.x - 1, rt.y - 1, rt.w,rt.h };
}

void Player::SetStat(struct CharacterData* a_pStat)
{
	m_refStat = a_pStat;
	m_nPutBombCount = 0;
}

bool Player::_Update(float a_fDelta)
{
	Move(a_fDelta);
	BombCheck();

	return false;
}