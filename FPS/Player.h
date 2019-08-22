#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int x, int y);
	virtual ~Player();

	virtual eObjectType GetObjectType() const override;

	virtual Rect GetRendertRect() const override;
	void SetStat(struct CharacterData* a_pStat);

private:
	void Move(float a_fDeltaTime);
	void BombCheck();

protected:
	virtual bool _Update(float a_fDelta);

	RenderTile	m_Data;
	struct CharacterData* m_refStat;

public:
	int m_nPutBombCount = 0;
};

