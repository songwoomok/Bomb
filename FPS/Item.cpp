#include "pch.h"
#include "Item.h"

#include "GameManager.h"
#include "Ani.h"

#include "Player.h"

Item::Item(int x, int y) : Object(x, y), m_pAni(new Ani())
{
	int nNum = (rand() % (int)eItem::Max);
	m_eType = (eItem)nNum;

	m_pAni->Resize((int)eItem::Max);
	m_pAni->Add((int)eItem::PowerUp,
		{
		   {{"     "},
			{"|   |"},
			{"| P |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"| P |"},
			{"|   |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|   |"},
			{"|   |"},
			{"| P |"},
			{"     "}},
		}
	);

	m_pAni->Add((int)eItem::SpeedUp,
		{
		   {{"     "},
			{"|   |"},
			{"| S |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"| S |"},
			{"|   |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|   |"},
			{"|   |"},
			{"| S |"},
			{"     "}},
		}
	);

	m_pAni->Add((int)eItem::BombCount,
		{
		   {{"     "},
			{"|   |"},
			{"|B-C|"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|B-C|"},
			{"|   |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|   |"},
			{"|   |"},
			{"|B-C|"},
			{"     "}},
		}
	);

	m_pAni->SetState((int)m_eType);
	m_pNowAni = m_pAni->Get();
}

Item::~Item()
{
	SAFE_DELETE(m_pAni);
}

eObjectType Item::GetObjectType() const
{
	return eObjectType::Item;
}

bool Item::Interaction(class Player* a_refHero)
{
	if (IsCross(a_refHero) == true)
	{
		GameMng()->ObtainItem(m_eType);
		return true;
	}

	return false;
}

bool Item::CanMove() const
{
	return true;
}

void Item::_PreUpdate(float a_fDelta)
{
	RenderClear();
}

bool Item::_Update(float a_fDelta)
{
	m_pAni->Update(a_fDelta);
	m_pNowAni = m_pAni->Get();

	return false;
}
