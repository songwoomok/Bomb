
#include "Object.h"

class Monster : public Object
{
public:

	enum { MonsterScore = 100, };

	Monster(int x, int y);
	virtual ~Monster();

	virtual eObjectType GetObjectType() const override;
	virtual bool CanMove() const override;
	virtual bool Interaction(class Player* a_refHero) override;
	virtual bool Explosived() override;

	int m_nLife = 1;
	RenderTile	m_Data;
};
