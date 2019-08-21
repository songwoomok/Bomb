#pragma once

struct CharacterData
{
	float	fMoveSpeed;
	float	fBombTime;
	int		nBombPower;
	int		nBombCount;

	CharacterData();
};

class GameManager
{
#pragma region SINGLE_TON
private:
	static inline GameManager * m_pInstance = nullptr;
	GameManager();
	~GameManager();

	GameManager operator=(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager(const GameManager&) = delete;

public:

	static void CreateInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new GameManager();
			m_pInstance->Init();
		}
	}

	static GameManager * GetInstance()
	{
		return m_pInstance;
	}

	static void ReleaseInstance()
	{
		m_pInstance->Release();
		SAFE_DELETE(m_pInstance);
	}

#pragma endregion

public:
	enum
	{
		MaxLife = 3,		
		RoundTime = 90,		

		MoveSpeed = 10,		
		BombTime = 2,		
		BombBasePower = 2,	
		BombBaseCount = 1,	
	};

	void Init();
	void Release();

	void GameInit();
	void StageStart();

	void Update(float a_fDeltaTime);
	void Render();

	void ClearObject();

	void RemoveObject(class Object* a_pObj);
	void DropItem(class Object* a_pObj);
	void GetBombData(class Bomb* a_refBomb) const;
	void ObtainItem(eItem a_eItem);

private:

	std::vector<class Object*> m_vcObj;
	class Player* m_pPlayer = nullptr;

	int m_nNowStage = 0;
	float m_fGameTime = 0;	
	class MapData* m_refMap = nullptr;
	char** m_pMap = nullptr;

	int m_nNowLife = 0;		
	int m_nScore = 0;		

	std::queue<class Bomb*> m_qBomb;

	CharacterData m_stPlayerData;
};



#define InitGameMng()		{GameManager::CreateInstance(); }
#define GameMng()			(GameManager::GetInstance())
#define ReleaseGameMng()	(GameManager::ReleaseInstance())
