#include "pch.h"
#include "Player.h"


Player::Player(int x, int y) : Object(x, y)
, m_Data{
		{ 'P', 'P', 'P', 'P', 'P' },
		{ 'P', ' ', ' ', ' ', 'P' },
		{ 'P', ' ', ' ', ' ', 'P' },
		{ 'P', ' ', ' ', ' ', 'P' },
		{ 'P', 'P', 'P', 'P', 'P' } }
{
	m_pNowAni = &m_Data;
}


Player::~Player()
{
}

eObjectType Player::GetObjectType() const
{
	return eObjectType::Player;
}


Rect Player::GetRedertRect() const
{
	return Rect{ rt.x - 1, rt.y - 1, rt.w,rt.h };
}