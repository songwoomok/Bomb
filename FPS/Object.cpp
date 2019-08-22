#include "pch.h"
#include "Object.h"

RenderTile Object::Empty = RenderTile{
	{"     "},
	{"     "},
	{"     "},
	{"     "},
	{"     "},
};

Object::Object(int _x, int _y) : x(_x), y(_y) 
{ 
	rt.x = _x * TileSize;
	rt.y = _y * TileSize;
	rt.w = TileSize;
	rt.h = TileSize;
}

Object::~Object() { }

void Object::Init() { }

void Object::Explosived(class Bomb* a_refBomb) { }
void Object::Interaction(class Hero* a_refHero) { }
void Object::_PreUpdate(float a_fDelta) { }
void Object::_Update(float a_fDelta) { }

void Object::SetMap(char** a_refMap)
{
	assert(a_refMap != nullptr);
	m_refMap = a_refMap;
}


void Object::Update(float a_fDelta)
{
	_PreUpdate(a_fDelta);
	_Update(a_fDelta);
}

Rect Object::GetRenderRect() const
{
	return rt;
}

void Object::Clear()
{
	Rect rt = GetRendertRect();
	int nX = rt.x;
	int nY = rt.y;

	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			Empty[i], TileSize * sizeof(char));
	}
}

void Object::Render()
{
	Rect rt = GetRenderRect();
	int nX = rt.x;
	int nY = rt.y;

	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			(*m_pNowAni)[i], TileSize * sizeof(char));
	}
}
