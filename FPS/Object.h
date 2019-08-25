#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;
	virtual bool CanMove() const;

	bool Update(float a_fDelta);
	void Render();
	void SetMap(char** a_refMap);
	void RenderClear();

	virtual void Init();
	virtual bool Explosived();
	virtual bool Interaction(class Player* a_refHero);

	inline void SetPos(int _x, int _y) { x = _x; y = _y; rt.x = _x; rt.y = _y; }
	inline bool IsCross(const Object& a_refObj) const
	{
		return rt.IsCross(a_refObj.rt);
	}
	inline bool IsCross(Object* a_refObj) const
	{
		assert((a_refObj != nullptr) && "arg error");
		return IsCross(*a_refObj);
	}

	virtual Rect GetRendertRect() const; 

protected:

	virtual void _PreUpdate(float a_fDelta); 
	virtual bool _Update(float a_fDelta);

public:
	int x;
	int y;
	Rect rt; 

protected:

	static RenderTile Empty;
	char**	m_refMap = nullptr;
	RenderTile*	m_pNowAni = nullptr;
};
