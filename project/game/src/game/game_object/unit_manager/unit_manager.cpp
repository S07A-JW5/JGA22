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
	m_Player->Create(0, 0);

	MapGeneration();
}

void CUnitManager::Update(void)
{
	cMapGenerator* MapGen = (cMapGenerator*)m_MapGenerator;

	if (!MapGen->MapGenerated()) return;

	IGameObject::Update();
	if (m_Player->DidAction())
	{
		for (int i = 0; i < m_NPCs.size(); i++)
		{
			if (m_NPCs[i])
				if (m_NPCs[i]->DidAction())
					continue;

			if (m_NPCs[i])
				m_NPCs[i]->Action();

			if (m_NPCs[i])
				if (!m_NPCs[i]->DidAction())
					return;
		}
		m_Player->SetActFlag(false);
		for (int i = 0; i < m_NPCs.size(); i++)
			if (m_NPCs[i])
				m_NPCs[i]->SetActFlag(false);
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
	{
		if (m_NPCs[i])
			m_NPCs[i]->DeleteObject();
	}
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

	m_NPCs.push_back(Bot);
	m_UnitPos[x_pos][y_pos] = m_NPCs.size();

	Bot->Initialize();
	Bot->Create(id, m_NPCs.size());
	Bot->SetPosition(aqua::CVector2(x_pos, y_pos));
}

void CUnitManager::MapGeneration()
{
	Clear();
	m_MapGenerated = false;
	cMapGenerator* MapGen = (cMapGenerator*)m_MapGenerator;
	MapGen->GenerateMap(m_Floor, 30 + m_Floor, 30 + m_Floor,
		5, 8, 2 + m_Floor, 5, 8, 1 + m_Floor);
	cMap* Map = MapGen->GetMap();
	aqua::CVector2 PlayerPos = Map->GetStartPoint();
	m_MapObj = Map;
	m_Player->GetMap(Map);
	m_Player->SetPosition(PlayerPos);
	SetPlayerPos(PlayerPos);
	m_Player->CameraUpdate();
	m_Player->SetStairPosition(Map->GetStairPos());
	Map->Update();
	Map->SetMapped(m_Player->GetPosition(), 8);
	for (int i = 0; i < m_NPCs.size(); i++)
	{
		if (m_NPCs[i])
			m_NPCs[i]->GetMap(Map);
	}
	++m_Floor;
}

bool CUnitManager::IsPlayerNearBy(aqua::CVector2 pos)
{
	if (!m_Player)
		return false;

	aqua::CVector2 Vector2 = m_PlayerPos - pos;
	return Vector2.Length() <= 1;
}

bool CUnitManager::HasSpace(aqua::CVector2 pos)
{
	if (m_UnitPos)
	{
		return m_UnitPos[(int)pos.x][(int)pos.y] < 0;
	}
	return true;
}

bool CUnitManager::CanAttack(aqua::CVector2 target_pos)
{
	if (!m_UnitPos) return false;
	if (m_UnitPos[(int)target_pos.x][(int)target_pos.y] < 0) return false;
	return true;
}

bool CUnitManager::Attack(aqua::CVector2 target_pos, int damage, IUnit::DAMAGE_TYPE type)
{
	if (!CanAttack(target_pos)) return false;

	int UnitNo = m_UnitPos[(int)target_pos.x][(int)target_pos.y];

	if (UnitNo == 0)
	{
		m_Player->TakeDamage(damage, type);
		return true;
	}
	if (m_NPCs[UnitNo - 1]->TakeDamage(damage, type))
	{
		m_NPCs[UnitNo - 1]->Dead();
		m_NPCs[UnitNo - 1] = nullptr;
		m_UnitPos[(int)target_pos.x][(int)target_pos.y] = -1;
	}
	return true;
}

void CUnitManager::SetMovedPos(aqua::CVector2 prev, aqua::CVector2 moved)
{
	if (!m_UnitPos) return;

	int UnitNo = m_UnitPos[(int)prev.x][(int)prev.y];

	if (UnitNo < 0) return;

	m_UnitPos[(int)prev.x][(int)prev.y] = -1;
	m_UnitPos[(int)moved.x][(int)moved.y] = UnitNo;

}

void CUnitManager::SetPlayerPos(aqua::CVector2 pos)
{
	m_UnitPos[(int)m_PlayerPos.x][(int)m_PlayerPos.y] = -1;
	m_PlayerPos = pos;
	m_UnitPos[(int)m_PlayerPos.x][(int)m_PlayerPos.y] = 0;
}

aqua::CVector2 CUnitManager::GetPlayerPos()
{
	return m_PlayerPos;
}

float CUnitManager::BetweenPlayer(aqua::CVector2 pos)
{
	aqua::CVector2 Dst = m_PlayerPos - pos;

	return Dst.Length();
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

uint8_t CUnitManager::GetFloorCount()
{
	return m_Floor;
}
