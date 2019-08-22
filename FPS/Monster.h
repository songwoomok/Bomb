
#include "Object.h"

class Monster : public Object
{
public:
	Monster(int x, int y);
	virtual ~Monster();

	virtual eObjectType GetObjectType() const override;
	virtual bool Interaction(class Player* a_refHero) override;
	RenderTile m_Data;
};
