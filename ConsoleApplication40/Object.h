#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	virtual void Init();
	virtual void Update(float a_fDelta);
	virtual void Explosived(class Bomb* a_refBomb);
	virtual void Interaction(class Hero* a_refHero);

	inline void SetPos(int _x, int _y) { x = _x; y = _y; }
	inline void SetMap(char** a_refMap) { assert(a_refMap != nullptr); m_refMap = a_refMap; }

public:
	int x;
	int y;

private:

	char** m_refMap = nullptr;
};
