#include "pch.h"
#include "Bomb.h"

#include "GameManager.h"
Bomb::Bomb(int x, int y) : Object(x, y)
{
}


Bomb::~Bomb()
{
}


eObjectType Bomb::GetObjectType() const
{
	return eObjectType::Bomb;
}

void Bomb::Init()
{
	GameMng()->GetBombData(this);
}

void Bomb::Update(float a_fDelta)
{
	m_fLifeTime -= a_fDelta;

	if (m_fLifeTime <= 0.0f)
	{

	}
}

void Bomb::Explosived(Bomb* a_refBomb)
{
	if (a_refBomb == this) { return; }
}