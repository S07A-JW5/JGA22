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
	, m_UnitNo(0)
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
	m_UnitNo = -1;
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

void IUnit::Create(int id, int unit_no)
{
	cUnitDataBase* UnitDB = (cUnitDataBase*)aqua::FindGameObject("UnitDataBase");
	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;

	cUnitDataBase::UnitData Data = UnitDB->GetData(id);

	m_Sprite.Create(Data.TexFilePath);

	m_UnitNo = unit_no;

	m_Name = Data.Name;
	m_Status.Life = Data.Life;
	m_Status.Cooling = Data.Cooling;
	m_Status.Battery = Data.Battery;
	m_Status.Parts = Data.Parts;
	m_Status.Ammo = Data.Ammo;
	for (int i = 0; i < 3; i++)
		m_Status.Resist[i] = Data.Resist[i];
	m_Status.Inventory = Data.Inventory;
	m_Status.HeadCount = Data.HeadCount;
	m_Status.ArmCount = Data.ArmCount;
	m_Status.HandCount = Data.HandCount;
	m_Status.ChestCount = Data.ChestCount;
	m_Status.BackCount = Data.BackCount;
	m_Status.LegCount = Data.LegCount;
	m_Status.ShlderCount = Data.ShlderCount;
	m_Status.CardCount = Data.CardCount;

	m_Weapon.clear();
	m_Head.clear();
	m_Arm.clear();
	m_Hand.clear();
	m_Chest.clear();
	m_Back.clear();
	m_Leg.clear();
	m_Shlder.clear();
	m_Card.clear();

	cEquipDataBase::Equipment Equipment;

	for (int i = 0; i < 16; i++)
	{
		Equipment = EquipDB->GetData(Data.Equipped[i]);

		switch (Equipment.Slot)
		{
		case cEquipDataBase::EQUIPMENT_SLOT::HEAD:
			if (m_Head.size() >= m_Status.HeadCount) break;
			m_Head.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_SLOT::ARM:
			if (m_Arm.size() >= m_Status.ArmCount) break;
			m_Arm.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_SLOT::HAND:
			if (m_Hand.size() >= m_Status.HandCount) break;
			m_Hand.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_SLOT::CHEST:
			if (m_Chest.size() >= m_Status.ChestCount) break;
			m_Chest.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_SLOT::BACK:
			if (m_Back.size() >= m_Status.BackCount) break;
			m_Back.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_SLOT::LEG:
			if (m_Leg.size() >= m_Status.LegCount) break;
			m_Leg.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_SLOT::SHOULDER:
			if (m_Shlder.size() >= m_Status.ShlderCount) break;
			m_Shlder.push_back(Equipment.EquipmentID);
			break;
		case cEquipDataBase::EQUIPMENT_SLOT::CARD:
			if (m_Card.size() >= m_Status.CardCount) break;
			m_Card.push_back(Equipment.EquipmentID);
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

	for (int i = 0; i < m_Head.size() && i < m_Status.HeadCount; i++)
	{
		CalcEquipmentStat(m_Head[i]);
	}
	for (int i = 0; i < m_Arm.size() && i < m_Status.ArmCount; i++)
	{
		CalcEquipmentStat(m_Arm[i]);
	}
	for (int i = 0; i < m_Hand.size() && i < m_Status.HandCount; i++)
	{
		CalcEquipmentStat(m_Hand[i]);
	}
	for (int i = 0; i < m_Chest.size() && i < m_Status.ChestCount; i++)
	{
		CalcEquipmentStat(m_Chest[i]);
	}
	for (int i = 0; i < m_Back.size() && i < m_Status.BackCount; i++)
	{
		CalcEquipmentStat(m_Back[i]);
	}
	for (int i = 0; i < m_Leg.size() && i < m_Status.LegCount; i++)
	{
		CalcEquipmentStat(m_Leg[i]);
	}
	for (int i = 0; i < m_Shlder.size() && i < m_Status.ShlderCount; i++)
	{
		CalcEquipmentStat(m_Shlder[i]);
	}
	for (int i = 0; i < m_Card.size() && i < m_Status.CardCount; i++)
	{
		CalcEquipmentStat(m_Card[i]);
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
		Damage -= Dice::DiceRoll(m_Protection / 4);
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

		if (!UnitMgr->Attack(pos, Dice::DiceRoll(m_Weapon[i].DmgRollData), m_Weapon[i].DamageType)) return false;

		m_Batt = max(m_Batt - m_Weapon[i].Energy, 0);
		m_Ammo = max(m_Ammo - m_Weapon[i].Ammo, 0);
		m_Heat = min(m_Heat + m_Weapon[i].Heat, 999);

		Attacked = true;
	}
	return Attacked;
}

void IUnit::CalcEquipmentStat(int id)
{
	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;
	cEquipDataBase::Equipment Equipment = EquipDB->GetData(id);

	if (Equipment.EquipmentID == 0) return;

	m_Weight += Equipment.Weight;
	if (Equipment.Type != cEquipDataBase::EQUIPMENT_TYPE::WEAPON)
	{
		m_EnergyFlow -= Equipment.Energy;
		m_HeatFlow += Equipment.Heat;
	}
	switch (Equipment.Type)
	{
	case cEquipDataBase::EQUIPMENT_TYPE::WEAPON: {
		WeaponStat Temp;
		Temp.ID = Equipment.EquipmentID;
		Temp.Name = Equipment.Name;
		Temp.DamageType = Equipment.DamageType;
		Temp.DmgRollData = Equipment.DmgRollData;
		Temp.Range = Equipment.Range;
		Temp.Heat = Equipment.Heat;
		Temp.Ammo = Equipment.Ammo;
		Temp.Energy = Equipment.Energy;
		m_Weapon.push_back(Temp);
	}	break;
	case cEquipDataBase::EQUIPMENT_TYPE::ARMOR:
		for (int j = 0; j < 3; j++)
			m_Resist[j] += Equipment.Resist[j];
		m_Protection += Equipment.Protection;
		break;
	case cEquipDataBase::EQUIPMENT_TYPE::SUPPORT:
		m_Support += Equipment.Support;
		break;
	case cEquipDataBase::EQUIPMENT_TYPE::UTIL:
		m_EnergyFlow += Equipment.Power;
		m_HeatFlow -= Equipment.Cooling;
		m_SightRange += Equipment.Range;
		m_BaseHeat += Equipment.BaseHeat;
		m_Inventory += Equipment.Inventory;
		m_MaxBatt += Equipment.MaxBatt;
		m_MaxParts += Equipment.MaxPart;
		m_MaxAmmo += Equipment.MaxAmmo;
		break;
	default:
		break;
	}
}
