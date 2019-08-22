#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	void Update(float a_fDelta);
	void Render();
	void SetMap(char** a_refMap);
	void RenderClear();

	virtual void Init();
	virtual void Explosived(class Bomb* a_refBomb);
	virtual void Interaction(class Hero* a_refHero);

	inline void SetPos(int _x, int _y) { x = _x; y = _y; }
	inline bool IsCross(const Object& a_refObj)
	{
		return rt.IsCross(a_refObj.rt);
	}
	inline bool IsCross(Object* a_refObj)
	{
		assert((a_refObj != nullptr) && "arg error");
		return IsCross(*a_refObj);
	}

	virtual Rect GetRenderRect() const;

protected:

	virtual void _PreUpdate(float a_fDelta);
	virtual bool _Update(float a_fDelta);

public:
	int x;
	int y;
	Rect rt;

protected:

	static RenderTile Empty;
	char** m_refMap = nullptr;
	RenderTile* m_pNowAni = nullptr
};
