#include "unit_manager.h"
#include"game/game_object/text_manager/text_manager.h"
#include"game/game_object/scene_manager/scene/game_main/game_main.h"
#include"game/game_object/scene_manager/scene/game_main/map_generator/map_generator.h"
#include <filesystem>

// コンストラクタ
CUnitManager::CUnitManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "UnitManager")
	, m_TextManager(nullptr)
	, m_Player(nullptr)
	, m_MapObj(nullptr)
	, m_MapGenerator(nullptr)
	, m_MapGenerated(false)
	, m_PlayerPos(aqua::CVector2::ZERO)
	, m_Floor(0)
	, m_UnitPos(nullptr)
{
}

void CUnitManager::Initialize(void)
{
	CGameMainScene* Gamemain = (CGameMainScene*)GetParent();
	m_MapGenerator = Gamemain->GetMapGenerator();

	m_TextManager = aqua::FindGameObject("TextManager");
	m_Player = aqua::CreateGameObject<cPlayer>(this);

	IGameObject::Initialize();
	m_Player->Create(0);

	MapGeneration();
}

void CUnitManager::Update(void)
{
	cMapGenerator* MapGen = (cMapGenerator*)m_MapGenerator;

	if (MapGen->MapGenerated())
	{
		IGameObject::Update();
	}
}

void CUnitManager::Draw(void)
{
	IGameObject::Draw();
}

void CUnitManager::Finalize(void)
{
	m_NPCs.clear();
	if (m_UnitPos)
	{
		for (int i = 0; i < m_Width; i++)
			AQUA_SAFE_DELETE_ARRAY(m_UnitPos[i]);
		AQUA_SAFE_DELETE_ARRAY(m_UnitPos);
	}
	IGameObject::Finalize();
}

void CUnitManager::Clear()
{
	for (int i = 0; i < m_NPCs.size(); i++)
		m_NPCs[i]->DeleteObject();
	m_NPCs.clear();
	if (m_UnitPos)
	{
		for (int i = 0; i < m_Width; i++)
			for (int j = 0; j < m_Height; j++)
				m_UnitPos[i][j] = -1;
	}
}

void CUnitManager::Create(std::uint16_t id, int x_pos, int y_pos)
{
	cBot* Bot = aqua::CreateGameObject<cBot>(this);
	Bot->Initialize();
	Bot->Create(id);
	Bot->GetMap((cMap*)m_MapObj);
	Bot->SetPosition(aqua::CVector2(x_pos, y_pos));

	m_NPCs.push_back(Bot);
	m_UnitPos[x_pos][y_pos] = m_NPCs.size();
}

void CUnitManager::MapGeneration()
{
	Clear();
	m_MapGenerated = false;
	cMapGenerator* MapGen = (cMapGenerator*)m_MapGenerator;
	MapGen->GenerateMap(30 + m_Floor, 30 + m_Floor,
		5, 8, 4 + m_Floor * 2, 5, 8, 4 + m_Floor * 2);
	cMap* Map = MapGen->GetMap();
	m_MapObj = Map;
	m_Player->GetMap(Map);
	m_Player->SetPosition(Map->GetStartPoint());
	m_Player->CameraUpdate();
	m_Player->SetStairPosition(Map->GetStairPos());
	Map->Update();
	Map->SetMapped(m_Player->GetPosition(), 8);
	++m_Floor;
}

bool CUnitManager::IsPlayerNearBy(aqua::CVector2 pos)
{
	if (!m_Player)
		return false;

	aqua::CVector2 Vector2 = m_PlayerPos - pos;
	return Vector2.Normalize().Length() <= 1;
}

void CUnitManager::SetPlayerPos(aqua::CVector2 pos)
{
	m_PlayerPos = pos;
}

void CUnitManager::SetMapSize(int width, int height)
{
	if (m_UnitPos)
	{
		for (int i = 0; i < m_Width; i++)
			AQUA_SAFE_DELETE_ARRAY(m_UnitPos[i]);
		AQUA_SAFE_DELETE_ARRAY(m_UnitPos);
	}
	m_Width = width;
	m_Height = height;

	m_UnitPos = AQUA_NEW int * [m_Width];
	for (int i = 0; i < m_Width; i++)
		m_UnitPos[i] = AQUA_NEW int[m_Height];

	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Height; j++)
			m_UnitPos[i][j] = -1;
}
