#pragma once

#include "Object.h"

class Bomb : public Object
{
public:
	Bomb(int x, int y);
	virtual ~Bomb();

	virtual eObjectType GetObjectType() const override;

	virtual void Init() override;
	virtual bool _Update(float a_fDelta) override;
	virtual bool Explosived() override;

	float		m_fLifeTime = 2.0f;
	int			m_nExplosiveRange = 2;

	class Ani* m_pAni = nullptr;
};

