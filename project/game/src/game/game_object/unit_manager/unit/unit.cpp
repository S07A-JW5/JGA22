#include "unit.h"
#include "../unit_manager.h"
#include "file_name.h"
#include "game/game_object/camera/camera.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

IUnit::IUnit(aqua::IGameObject* parent, std::string name)
	: aqua::IGameObject(parent, name, "Unit")
	, m_Life(0)
	, m_MaxLife(0)
	, m_Cooling(0)
	, m_Heat(0)
	, m_BaseHeat(0)
	, m_Inventory(0)
	, m_Weight(0)
	, m_Support(0)
	, m_Batt(0)
	, m_MaxBatt(0)
	, m_Parts(0)
	, m_MaxParts(0)
	, m_Ammo(0)
	, m_MaxAmmo(0)
	, m_Resist()
	, m_Protection(0)
	, m_Status({ 0 })
	, m_SoundManager(nullptr)
	, m_UnitManager(nullptr)
	, m_TextManager(nullptr)
	, m_UIManager(nullptr)
	, m_MapObj(nullptr)
	, m_Camera(nullptr)
	, m_DidAction(false)
	, m_DesiredAction(IUnit::ACTION::WAIT)
	, m_MoveTo(IUnit::DIRECTION::DUMMY)
	, m_OnMapPos(aqua::CVector2::ZERO)
	, m_Position(aqua::CVector2::ZERO)
{
}

void IUnit::Initialize()
{
	m_SoundManager = aqua::FindGameObject("SoundManager");
	m_TextManager = aqua::FindGameObject("TextManager");
	m_UIManager = aqua::FindGameObject("UIManager");
	m_Camera = aqua::FindGameObject("Camera");
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
	return m_OnMapPos;
}

void IUnit::SetPosition(aqua::CVector2 pos)
{
	m_OnMapPos = pos;
}

void IUnit::GetMap(cMap* map)
{
	m_MapObj = map;
}

bool IUnit::Action()
{
	return false;
}

bool IUnit::Wait()
{
	return false;
}

bool IUnit::Move()
{
	bool Moved = false;

	switch (m_MoveTo)
	{
	case IUnit::DIRECTION::DUMMY:
		return false;
		break;
	case IUnit::DIRECTION::NORTH:
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x, m_OnMapPos.y - 1))
		{
			m_OnMapPos.y -= 1;
			Moved = true;
		}
		break;
	case IUnit::DIRECTION::SOUTH:
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x, m_OnMapPos.y + 1))
		{
			m_OnMapPos.y += 1;
			Moved = true;
		}
		break;
	case IUnit::DIRECTION::EAST:
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x + 1, m_OnMapPos.y))
		{
			m_OnMapPos.x += 1;
			Moved = true;
		}
		break;
	case IUnit::DIRECTION::WEST:
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x - 1, m_OnMapPos.y))
		{
			m_OnMapPos.x -= 1;
			Moved = true;
		}
		break;
	}
	if (Moved)
	{
		//m_DidAction = true;
	}
	return Moved;
}

bool IUnit::Attack()
{
	return false;
}
