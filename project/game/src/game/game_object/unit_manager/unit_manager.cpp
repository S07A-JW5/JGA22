#include "unit_manager.h"
#include"game/game_object/text_manager/text_manager.h"
#include"game/game_object/scene_manager/scene/game_main/game_main.h"
#include"game/game_object/scene_manager/scene/game_main/map_generator/map_generator.h"
#include <filesystem>

// コンストラクタ
CUnitManager::CUnitManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "UnitManager")
	, m_Player(nullptr)
	, m_MapGenerator(nullptr)
{
}

void CUnitManager::Initialize(void)
{
	CGameMainScene* Gamemain = (CGameMainScene*)GetParent();
	m_MapGenerator = Gamemain->GetMapGenerator();
	cMapGenerator* MapGen = (cMapGenerator*)m_MapGenerator;
	MapGen->GenerateMap();

	m_TextManager = aqua::FindGameObject("TextManager");
	m_Player = aqua::CreateGameObject<cPlayer>(this);
	m_Player->GetMap(MapGen->GetMap());

	IGameObject::Initialize();
}

void CUnitManager::Update(void)
{
	cMapGenerator* MapGen = (cMapGenerator*)m_MapGenerator;

	if (MapGen->MapGenerated())
		IGameObject::Update();
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
