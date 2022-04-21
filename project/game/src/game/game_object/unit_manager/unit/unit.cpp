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
	, m_EnergyFlow(0)
	, m_Batt(0)
	, m_MaxBatt(0)
	, m_Parts(0)
	, m_MaxParts(0)
	, m_Ammo(0)
	, m_MaxAmmo(0)
	, m_Resist()
	, m_Protection(0)
	, m_SightRange(0)
	, m_Coverage(0)
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
	m_Status.WeaponCount = Data.WeaponCount;
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
			if (m_Weapon.size() >= m_Status.WeaponCount) break; 
			{
			WeaponStat Temp;
			Temp.ID = Equipment.EquipmentID;
			Temp.Name = Equipment.Name;
			Temp.Heat = Equipment.Heat;
			Temp.Ammo = Equipment.Ammo;
			Temp.Energy = Equipment.Energy;
			Temp.Range = Equipment.Range;
			Temp.DamageType = Equipment.DamageType;
			Temp.MinDamage = Equipment.MinDamage;
			Temp.MaxDamage = Equipment.MaxDamage;
			m_Weapon.push_back(Temp);
			}
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
	m_SightRange = 8;
	m_Coverage = 0;

	for (int i = 0; i < m_Weapon.size() && i < m_Status.WeaponCount; i++)
	{
		Equipment = EquipDB->GetData(m_Weapon[i].ID);
		if (Equipment.EquipmentID == 0) continue;

		//m_Coverage++;
		CalcBasicEquipmentStat(m_Weapon[i].ID);
	}
	for (int i = 0; i < m_Armor.size() && i < m_Status.ArmorCount; i++)
	{
		Equipment = EquipDB->GetData(m_Armor[i]);
		if (Equipment.EquipmentID == 0) continue;

		//m_Coverage += 4;
		CalcBasicEquipmentStat(m_Armor[i]);
		for (int j = 0; j < 3; j++)
			m_Resist[j] += Equipment.Resist[j];
		m_Protection += Equipment.Protection;
	}
	for (int i = 0; i < m_Transp.size() && i < m_Status.TranspCount; i++)
	{
		Equipment = EquipDB->GetData(m_Transp[i]);
		if (Equipment.EquipmentID == 0) continue; 

		//m_Coverage++;
		CalcBasicEquipmentStat(m_Transp[i]);
		m_Support += Equipment.Support;
	}
	for (int i = 0; i < m_Util.size() && i < m_Status.UtilCount; i++)
	{
		Equipment = EquipDB->GetData(m_Util[i]);
		if (Equipment.EquipmentID == 0) continue;

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

bool IUnit::TakeDamage(int damage, IUnit::DAMAGE_TYPE type)
{
	int Damage = damage;
	Damage *= (float)(100 - m_Resist[(int)type - 1]) / (100);
	if (type == DAMAGE_TYPE::KINETIC)
	{
		Damage *= 100.0f / (100 + m_Protection);
		Damage -= rand() % max(m_Protection / 4, 1);
	}
	Damage = max(Damage, 0);
	m_Life = max(m_Life - Damage, 0);
	return m_Life <= 0;
}

bool IUnit::DidAction()
{
	return m_DidAction;
}

void IUnit::SetActFlag(bool flag)
{
	m_DidAction = flag;
}

int IUnit::GetStatus(IUnit::STATUS stat)
{
	switch (stat)
	{
	case IUnit::STATUS::LIFE:
		return m_Life;
		break;
	case IUnit::STATUS::HEAT:
		return m_Heat;
		break;
	case IUnit::STATUS::BATT:
		return m_Batt;
		break;
	case IUnit::STATUS::PARTS:
		return m_Parts;
		break;
	case IUnit::STATUS::AMMO:
		return m_Ammo;
		break;
	}
	return 0;
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
	CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
	aqua::CVector2 Pos = m_OnMapPos;
	bool Moved = false;

	switch (m_MoveTo)
	{
	case IUnit::DIRECTION::DUMMY:
		return false;
		break;
	case IUnit::DIRECTION::NORTH:
		Pos.y -= 1;
		break;
	case IUnit::DIRECTION::SOUTH:
		Pos.y += 1;
		break;
	case IUnit::DIRECTION::EAST:
		Pos.x -= 1;
		break;
	case IUnit::DIRECTION::WEST:
		Pos.x += 1;
		break;
	}
	if (m_MapObj->IsWalkableTile(Pos.x, Pos.y) && UnitMgr->HasSpace(Pos))
	{
		m_OnMapPos = Pos;
		Moved = true;
	}
	if (Moved)
	{
		//m_DidAction = true;
	}
	return Moved;
}

bool IUnit::Attack(aqua::CVector2 pos)
{
	CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;

	if (m_MapObj->HitWall(m_OnMapPos, pos)) return false;

	aqua::CVector2 Diff = pos - m_OnMapPos;

	bool Attacked = false;

	for (int i = 0; i < m_Weapon.size(); i++)
	{
		if (m_Weapon[i].ID == 0) continue;
		if (m_Weapon[i].Range < Diff.Length())
			if (Diff.Length() > 1.42f)
				continue;

		if (m_Batt - m_Weapon[i].Energy < 0) continue;
		if (m_Ammo - m_Weapon[i].Ammo < 0) continue;
		if (m_Heat + m_Weapon[i].Heat < 0) continue;

		if (!UnitMgr->Attack(pos, aqua::Rand(m_Weapon[i].MinDamage, m_Weapon[i].MaxDamage), m_Weapon[i].DamageType)) return false;

		m_Batt = max(m_Batt - m_Weapon[i].Energy, 0);
		m_Ammo = max(m_Ammo - m_Weapon[i].Ammo, 0);
		m_Heat = min(m_Heat + m_Weapon[i].Heat, 999);

		Attacked = true;
	}
	return Attacked;
}

void IUnit::CalcBasicEquipmentStat(int id)
{
	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;
	cEquipDataBase::Equipment Equipment = EquipDB->GetData(id);

	if (Equipment.EquipmentID == 0) return;

	m_Weight += Equipment.Weight;
	if (Equipment.Type == cEquipDataBase::EQUIPMENT_TYPE::WEAPON) return;
	m_EnergyFlow -= Equipment.Energy;
	m_HeatFlow += Equipment.Heat;
}
