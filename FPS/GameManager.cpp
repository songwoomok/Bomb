#include "pch.h"
#include "GameManager.h"

#include "MapData.h"
#include "Object.h"
#include "Player.h"
#include "ObjectFactory.h"

CharacterData::CharacterData()
{
	fMoveSeepd = GameManager::MoveSpeed;
	fBombTime = GameManager::BombTime;
	nBombPower = GameManager::BombBasePower;
	nBombCount = GameManager::BombBaseCount;
}

GameManager::GameManager() {}
GameManager::~GameManager()
{
	ClearObject();
	SAFE_DELETE(m_pPlayer);
}

void GameManager::Init()
{
	MapData::Init();
}

void GameManager::Release()
{
	MapData::Release();
}

void GameManager::GameInit()
{
	m_nNowLife = 3;
	m_nScore = 0;
	m_nNowStage = 0;
}

void GameManager::StageStart()
{
	++m_nNowStage;
	m_fGameTime = RoundTime;
	m_eState = eGameState::Run;

	ClearObject();

	m_refMap = MapData::Get(m_nNowStage);
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr);

	int nWidth = m_refMap->x;
	int nHeight = m_refMap->y;
	const std::string& sRef = m_refMap->mapOriginData;
	m_pMap = m_refMap->pMap;

	// ∏  ¡¶¿€
	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			int nIndex = y * nWidth + x;
			eObjectType eType = MapData::DataToObjectType(sRef[nIndex]);

			if (eType == eObjectType::None) { continue; }

			if (eType == eObjectType::Player && m_pPlayer != nullptr)
			{
				m_pPlayer->SetPos(x, y);
				m_pPlayer->SetMap(m_pMap);
				continue;
			}

			CreateObject(eType, x, y);
		}
	}
}

void GameManager::StageEnd()
{
	m_eState = eGameState::End;
}

void GameManager::ClearObject()
{
	for (auto& vc : m_arrObj)
	{
		for (auto* pObj : vc)
		{
			SAFE_DELETE(pObj);
		}

		vc.clear();
	}
}

Object* GameManager::CreateObject(eObjectType a_eObjType, int x, int y)
{
	auto* pObj = ObjectFactory::Make(a_eObjType, x, y);
	if (a_eObjType == eObjectType::Player)
	{
		m_pPlayer = static_cast<Player*>(pObj);
		m_pPlayer->SetStat(&m_stPlayerData);
	}
	else
	{
		int nDepthIndex = (int)a_eObjType / (int)eObjectType::RenderDepthGap;
		nDepthIndex -= 1;

		m_arrObj[nDepthIndex].push_back(pObj);
	}

	pObj->SetMap(m_pMap);
	return pObj;
}

void GameManager::Update(float a_fDeltaTime)
{
	m_vcDelete.clear();
	int nSize = m_arrObj.size();

	for (int i = 1; i < nSize; ++i)
	{
		auto& arrObj = m_arrObj[i];

		for (auto* pObj : arrObj)
		{
			Object* p = nullptr;

			if (pObj->Update(a_fDeltaTime) == true)
			{
				p = pObj;
			}

			if (pObj->Interaction(m_pPlayer) == true)
			{
				p = pObj;
			}

			if (p != nullptr)
			{
				m_vcDelete.push_back(p);
			}
		}
	}

	m_pPlayer->Update(a_fDeltaTime);
}

void GameManager::Render()
{
	for (auto& vc : m_arrObj)
	{
		for (auto* pObj : vc)
		{
			pObj->Render();
		}
	}

	m_pPlayer->Render();
	m_refMap->Render();

	if (m_eState == eGameState::End)
	{
		StageStart();
	}

	cout << "pos : " << m_pPlayer->rt.x << " /// " << m_pPlayer->rt.y << endl;
	COORD center = m_pPlayer->rt.Center();

	cout << "center : " << center.X << " /// " << center.Y << endl;

	if (m_sLog.size() > 0)
	{
		cout << m_sLog.c_str() << endl;
		m_sLog.clear();
	}
}

void GameManager::PostRender()
{
	for (auto* pDeleteObj : m_vcDelete)
	{
		pDeleteObj->RenderClear();
		RemoveObject(pDeleteObj);
	}
	m_vcDelete.clear();

	for (auto& ex : m_vcExplision)
	{
		int nBombX = ex.x;
		int nBombY = ex.y;
		int nPow = ex.pow;

		CreateObject(eObjectType::Explosion, nBombX, nBombY);

		CreateExplosionRecursive(eDir::Left, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Top, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Right, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Bottom, nBombX, nBombY, nPow);
	}

	m_vcExplision.clear();
}

void GameManager::CreateExplosionRecursive(eDir a_eDir, int nBombX, int nBombY, int a_nRemainPower)
{
	switch (a_eDir)
	{
	case eDir::Left: { nBombX -= 1; } break;
	case eDir::Top: { nBombY -= 1; } break;
	case eDir::Right: { nBombX += 1; } break;
	case eDir::Bottom: { nBombY += 1; } break;
	}

	CreateObject(eObjectType::Explosion, nBombX, nBombY);

	--a_nRemainPower;
	if (a_nRemainPower == 0) { return; }

	CreateExplosionRecursive(a_eDir, nBombX, nBombY, a_nRemainPower);
}

void GameManager::RemoveObject(class Object* a_pObj)
{
	eObjectType eType = a_pObj->GetObjectType();

	int nLevelIndex = (int)eType / (int)eObjectType::RenderDepthGap;
	nLevelIndex -= 1; // ¿Œµ¶Ω∫

	auto& vc = m_arrObj[nLevelIndex];

	auto itor = std::find_if(std::begin(vc), std::end(vc), [a_pObj](Object*p) {return p == a_pObj; });
	if (itor != vc.end())
	{
		vc.erase(itor);
		SAFE_DELETE(a_pObj);
	}
}

void GameManager::DropItem(Object* a_pObj)
{

}

void GameManager::ObtainItem(eItem a_eItem)
{
	switch (a_eItem)
	{
	case eItem::PowerUp:
		m_stPlayerData.nBombPower += 1;
		break;
	case eItem::BombCount:
		m_stPlayerData.nBombCount += 1;
		break;
	case eItem::SpeedUp:
		m_stPlayerData.fMoveSeepd += 30;
		break;
	default:
		assert(false && "arg error");
		break;
	}
}

void GameManager::Die(class Object* a_refObj)
{
	cout << "Player Die" << endl;
}

Object* GameManager::AddBomb(int a_nPlayerX, int a_nPlayerY)
{
	if (FindObject_withPosition(eObjectType::Bomb, a_nPlayerX, a_nPlayerY) == false)
	{
		int nX = a_nPlayerX / TileSize;
		int nY = a_nPlayerY / TileSize;

		return CreateObject(eObjectType::Bomb, nX, nY);
	}

	return nullptr;
}

bool GameManager::FindObject_withPosition(eObjectType a_eObj, int x, int y)
{
	int nX = x / TileSize;
	int nY = y / TileSize;
	int nIndex = ((int)a_eObj / (int)eObjectType::RenderDepthGap) - 1;

	for (auto* pObj : m_arrObj[nIndex])
	{
		if (pObj->GetObjectType() == a_eObj)
		{
			if (pObj->rt.IsIn(x, y) == true)
			{
				return true;
			}
		}
	}

	return false;
}

void GameManager::ResistExplosion(Object* a_refBomb, int x, int y, int pow)
{
	m_pPlayer->ResetBomb(a_refBomb);
	m_vcExplision.emplace_back(x / TileSize, y / TileSize, pow);
}

bool GameManager::MoveCheck(Object* a_pMoveIgnoreObject /*= nullptr*/)
{
	for (auto& vc : m_arrObj)
	{
		for (auto* pObj : vc)
		{
			if (a_pMoveIgnoreObject == pObj) { continue; }

			if (pObj->CanMove() == true) { continue; }

			if (pObj->IsCross(m_pPlayer) == true)
			{
				return false;
			}
		}
	}

	return true;
}

void GameManager::CheckExplosion(Object* a_refExplosion)
{
	int nIndex = (int)eObjectType::RenderDepth3 - 1; 
	const auto& vc = m_arrObj[nIndex];

	for (auto* pObj : vc)
	{
		if (pObj == a_refExplosion) { continue; } 

		if (a_refExplosion->IsCross(pObj) == true)
		{
			if (pObj->Explosived() == true)
			{
				m_vcDelete.push_back(pObj);
			}
		}
	}

}

void GameManager::AddScore(int a_nScore)
{
	m_nScore += m_nScore;
}

#include "Bomb.h"
void GameManager::GetBombData(OUT Bomb* a_refBomb) const
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}