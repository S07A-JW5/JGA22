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
	, m_MapGenerator(nullptr)
	, m_MapGenerated(false)
	, m_PlayerPos(aqua::CVector2::ZERO)
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
	IGameObject::Finalize();
}

void CUnitManager::Clear()
{
}

void CUnitManager::Create()
{
	cBot* Bot = aqua::CreateGameObject<cBot>(this);
	Bot->Initialize();
	Bot->Create(1);
}

void CUnitManager::MapGeneration()
{
	m_MapGenerated = false;
	cMapGenerator* MapGen = (cMapGenerator*)m_MapGenerator;
	MapGen->GenerateMap(40, 40, 5, 8, 10, 5, 8, 10);
	cMap* Map = MapGen->GetMap();
	m_Player->GetMap(Map);
	m_Player->SetPosition(Map->GetStartPoint());
	m_Player->CameraUpdate();
	m_Player->SetStairPosition(Map->GetStairPos());
	Map->Update();
	Map->SetMapped(m_Player->GetPosition(), 8);
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
