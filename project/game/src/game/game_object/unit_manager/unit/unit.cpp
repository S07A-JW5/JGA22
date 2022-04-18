#include "unit.h"
#include "../unit_manager.h"
#include "file_name.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/database/chr_db/chr_db.h"
#include "game/game_object/database/equip_db/equip_db.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

IUnit::IUnit(aqua::IGameObject* parent, std::string name)
	: aqua::IGameObject(parent, name, "Unit")
	, m_Life(0)
	, m_MaxLife(0)
	, m_HeatFlow(0)
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
	m_EquipmentDB = aqua::FindGameObject("EquipmentDB");
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

void IUnit::Create(int id)
{
	cUnitDataBase* UnitDB = (cUnitDataBase*)aqua::FindGameObject("UnitDataBase");
	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;

	cUnitDataBase::UnitData Data = UnitDB->GetData(id);

	m_Sprite.Create(Data.TexFilePath);

	m_Name = Data.Name;
	m_Status.Life = Data.Life;
	m_Status.Cooling = Data.Cooling;
	m_Status.Battery = Data.Battery;
	m_Status.Parts = Data.Parts;
	m_Status.Ammo = Data.Ammo;
	for (int i = 0; i < 3; i++)
		m_Status.Resist[i] = Data.Resist[i];
	m_Status.Inventory = Data.Inventory;
	m_Status.ArmSlotCount = Data.ArmSlotCount;
	m_Status.ArmorCount = Data.ArmorCount;
	m_Status.TranspCount = Data.TranspCount;
	m_Status.UtilCount = Data.UtilCount;

	m_Weapon.clear();
	m_Armor.clear();
	m_Transp.clear();
	m_Util.clear();

	cEquipDataBase::Equipment Equipment;

	for (int i = 0; i < 20; i++)
	{
		Equipment = EquipDB->GetData(Data.Equipped[i]);
		switch (Equipment.Type)
		{
		case cEquipDataBase::EQUIPMENT_TYPE::WEAPON:
			if (m_Weapon.size() >= m_Status.ArmSlotCount) break;
			m_Weapon.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_TYPE::ARMOR:
			if (m_Armor.size() >= m_Status.ArmorCount) break;
			m_Armor.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_TYPE::TRANSP:
			if (m_Transp.size() >= m_Status.TranspCount) break;
			m_Transp.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_TYPE::UTIL:
			if (m_Util.size() >= m_Status.UtilCount) break;
			m_Util.push_back(Equipment.EquipmentID);
			break;
		default:
			break;
		}
	}
	CalcStatus();
}

void IUnit::CalcStatus()
{
	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;
	cEquipDataBase::Equipment Equipment;

	m_Life = m_MaxLife = m_Status.Life;
	m_Heat = m_BaseHeat = 0;
	m_HeatFlow = -m_Status.Cooling;
	m_Batt = m_MaxBatt = m_Status.Battery;
	m_EnergyFlow = 0;
	m_Parts = m_MaxParts = m_Status.Parts;
	m_Ammo = m_MaxAmmo = m_Status.Ammo;
	m_Inventory = m_Status.Inventory;
	for (int i = 0; i < 3; i++)
		m_Resist[i] = m_Status.Resist[i];
	m_Weight = 0;
	m_Support = 0;
	m_Protection = 0;

	for (int i = 0; i < m_Weapon.size() && i < m_Status.ArmSlotCount; i++)
	{
		Equipment = EquipDB->GetData(m_Weapon[i]);
		CalcBasicEquipmentStat(m_Weapon[i]);
	}
	for (int i = 0; i < m_Armor.size() && i < m_Status.ArmorCount; i++)
	{
		Equipment = EquipDB->GetData(m_Armor[i]);
		CalcBasicEquipmentStat(m_Armor[i]);
		for (int i = 0; i < 3; i++)
			m_Resist[i] += Equipment.Resist[i];
		m_Protection += Equipment.Protection;
	}
	for (int i = 0; i < m_Transp.size() && i < m_Status.TranspCount; i++)
	{
		Equipment = EquipDB->GetData(m_Transp[i]);
		CalcBasicEquipmentStat(m_Transp[i]);
		m_Support += Equipment.Support;
	}
	for (int i = 0; i < m_Util.size() && i < m_Status.UtilCount; i++)
	{
		Equipment = EquipDB->GetData(m_Util[i]);
		CalcBasicEquipmentStat(m_Util[i]);
		m_EnergyFlow += Equipment.Power;
		m_HeatFlow -= Equipment.Cooling;
		m_SightRange += Equipment.Range;
		m_BaseHeat += Equipment.BaseHeat;
		m_Inventory += Equipment.Inventory;
		m_MaxBatt += Equipment.MaxBatt;
		m_MaxParts += Equipment.MaxPart;
		m_MaxAmmo += Equipment.MaxAmmo;
	}
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

void IUnit::CalcBasicEquipmentStat(int id)
{
	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;
	cEquipDataBase::Equipment Equipment = EquipDB->GetData(id);

	m_Weight += Equipment.Weight;
	m_EnergyFlow -= Equipment.Energy;
	m_HeatFlow += Equipment.Heat;
}
