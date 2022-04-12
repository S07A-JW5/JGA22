#include "unit.h"
#include "../unit_manager.h"
#include "file_name.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

IUnit::IUnit(aqua::IGameObject* parent, std::string name)
	: aqua::IGameObject(parent, name, "Unit")
	, m_Life(0)
	, m_MaxLife(0)
	, m_Heat(0)
	, m_Batt(0)
	, m_MaxBatt(0)
	, m_Parts(0)
	, m_MaxParts(0)
	, m_Ammo(0)
	, m_MaxAmmo(0)
	, m_Resist()
	, m_Status({ 0 })
	, m_SoundManager(nullptr)
	, m_UnitManager(nullptr)
	, m_TextManager(nullptr)
	, m_UIManager(nullptr)
	, m_MapObj(nullptr)
	, m_Position(aqua::CVector2::ZERO)
{
}

void IUnit::Initialize()
{
	m_SoundManager = aqua::FindGameObject("SoundManager");
	m_TextManager = aqua::FindGameObject("TextManager");
	m_UIManager = aqua::FindGameObject("UIManager");
	m_UnitManager = GetParent();
}

void IUnit::Update()
{
}

void IUnit::Draw()
{
	m_Sprite.Draw();
}

void IUnit::Finalize()
{
	m_Sprite.Delete();
}

void IUnit::Create(std::string file_name)
{
}

aqua::CVector2 IUnit::GetPosition()
{
	return m_Position;
}

void IUnit::SetPosition(aqua::CVector2 pos)
{
	m_Position = pos;

	m_Sprite.position = m_Position;
}

void IUnit::GetMap(cMap* map)
{
	m_MapObj = map;
}
