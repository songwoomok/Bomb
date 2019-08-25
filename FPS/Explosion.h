#pragma once
#include "Object.h"

class Explosion : public Object
{
public:
	Explosion(int x, int y);
	virtual ~Explosion();

	virtual eObjectType GetObjectType() const override;
	virtual bool CanMove() const override;

	virtual void _PreUpdate(float a_fDelta) override;
	virtual bool _Update(float a_fDelta) override;

	float		m_fLife = 2.0f;
	class Ani* m_pAni = nullptr;
};

