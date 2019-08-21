#include "pch.h"
#include "MapData.h"

MapData MapData::m_arrData[eGame::MaxStage] = { {}, };

MapData* MapData::Get(int a_nStage)
{
	return &m_arrData[a_nStage];
}

void MapData::Init()
{
	// 1스테이지
	m_arrData[0].x = 10;
	m_arrData[0].y = 10;
	m_arrData[0].mapOriginData =
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[0].MakeMap();

	// 2스테이지
	m_arrData[1].x = 10;
	m_arrData[1].y = 10;
	m_arrData[1].mapOriginData =
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[1].MakeMap();

	// 3스테이지
	m_arrData[2].x = 10;
	m_arrData[2].y = 10;
	m_arrData[2].mapOriginData =
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[2].MakeMap();
}

void MapData::Release()
{
	for (auto& mapData : m_arrData)
	{
		mapData.ReleaseData();
	}
}

void MapData::MakeMap()
{
	pMap = new char*[y];

	for (int i = 0; i < y; ++i)
	{
		pMap[i] = new char[x + 1];

		int gap = i * x;

		memcpy_s(pMap[i], sizeof(char) * (x + 1),
			mapOriginData + gap, sizeof(char)* x);

		pMap[i][x] = 0;
	}
}

void MapData::ReleaseData()
{
	for (int i = 0; i < y; ++i)
	{
		SAFE_DELETE_ARR(pMap[i])
	}

	SAFE_DELETE_ARR(pMap);
}

void MapData::Render()
{
	for (int i = 0; i < y; ++i)
	{
		cout << pMap[i] << endl;
	}
}
