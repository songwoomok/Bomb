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

Rect Player::GetRendertRect() const
{
	return Rect{ rt.x - 1, rt.y - 1, rt.w, rt.h };
}

void Player::SetStat(struct CharacterData* a_pStat)
{
	m_refStat = a_pStat;
	m_nPutBombCount = 0;
}

void Player::_PreUpdate(float a_fDelta)
{
	RenderClear();
}

bool Player::_Update(float a_fDelta)
{
	Move(a_fDelta);
	BombCheck();

	return false;
}

void Player::Move(float a_fDeltaTime)
{
	float fAdd = a_fDeltaTime * (m_refStat->fMoveSeepd);

	float fX = 0;
	float fY = 0;

	if (IsKeyDown(eKey::A)) { fX -= fAdd; }
	if (IsKeyDown(eKey::D)) { fX += fAdd; }

	if (IsKeyDown(eKey::S)) { fY += fAdd; }
	if (IsKeyDown(eKey::W)) { fY -= fAdd; }

	if (fX == 0 && fY == 0) { return; }

	rt.x += fX;
	rt.y += fY;

	if (GameMng()->MoveCheck(m_refBomb) == false)
	{
		rt.x -= fX;
		rt.y -= fY;
	}

	if (m_refBomb != nullptr)
	{
		if (m_refBomb->IsCross(this) == false)
		{
			m_refBomb = nullptr;
		}
	}
}

void Player::BombCheck()
{
	if (m_nPutBombCount >= m_refStat->nBombCount) { return; }

	if (IsKeyDown(eKey::Space))
	{
		COORD c = rt.Center();

		auto* pBomb = GameMng()->AddBomb(c.X, c.Y);
		if (pBomb != nullptr)
		{
			++m_nPutBombCount;
			m_refBomb = pBomb; 
		}
	}
}

void Player::ResetBomb(Object* a_refBomb)
{
	if (m_refBomb == a_refBomb)
	{
		m_refBomb = nullptr;
	}

	--m_nPutBombCount;

	if (m_nPutBombCount < 0)
	{
		m_nPutBombCount = 0;
	}
}

bool Player::Explosived()
{
	GameMng()->Die(this);
	return false;
}
