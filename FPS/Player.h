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
	void ResetBomb(Object* a_refBomb);
	virtual bool Explosived() override;

private:
	void Move(float a_fDeltaTime);
	void BombCheck();

protected:

	virtual void _PreUpdate(float a_fDelta) override;
	virtual bool _Update(float a_fDelta) override;

	RenderTile	m_Data;
	struct CharacterData* m_refStat;

	int m_nPutBombCount = 0;
	Object* m_refBomb = nullptr;
};

