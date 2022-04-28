#include "unit.h"
#include "../unit_manager.h"
#include "file_name.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/database/chr_db/chr_db.h"
#include "game/game_object/database/item_db/item_db.h"
#include "game/game_object/database/equip_db/equip_db.h"
#include "game/game_object/text_manager/text_manager.h"
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
	, m_WeaponCount(0)
	, m_UnitNo(0)
	, m_Status({ 0 })
	, m_SoundManager(nullptr)
	, m_UnitManager(nullptr)
	, m_TextManager(nullptr)
	, m_UIManager(nullptr)
	, m_EquipmentDB(nullptr)
	, m_ItemDataBase(nullptr)
	, m_UnitDataBase(nullptr)
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
	m_UnitDataBase = aqua::FindGameObject("UnitDataBase");
	m_ItemDataBase = aqua::FindGameObject("ItemDataBase");
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
	m_Status.ID = id;
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

	m_Status.EquipCount = m_Status.HeadCount + m_Status.ArmCount +
		m_Status.HandCount + m_Status.ChestCount + m_Status.BackCount +
		m_Status.LegCount + m_Status.ShlderCount + m_Status.CardCount;

	for (int i = 0; i < 16; i++)
	{
		m_Weapon[i] = WeaponStat{ 0 };
		m_Equipment[i] = 0;
	}
	m_ItemList.clear();
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
	m_WeaponCount = 0;
	std::uint8_t Count = 0;

	for (int i = 0; i < m_Status.HeadCount; i++, Count++)
	{
		if (i >= m_Head.size()) m_Head.push_back(0);
		m_Equipment[Count] = m_Head[i];
		CalcEquipmentStat(m_Head[i]);
	}
	for (int i = 0; i < m_Status.ArmCount; i++, Count++)
	{
		if (i >= m_Arm.size()) m_Arm.push_back(0);
		m_Equipment[Count] = m_Arm[i];
		CalcEquipmentStat(m_Arm[i]);
	}
	for (int i = 0; i < m_Status.HandCount; i++, Count++)
	{
		if (i >= m_Hand.size()) m_Hand.push_back(0);
		m_Equipment[Count] = m_Hand[i];
		CalcEquipmentStat(m_Hand[i]);
	}
	for (int i = 0; i < m_Status.ChestCount; i++, Count++)
	{
		if (i >= m_Chest.size()) m_Chest.push_back(0);
		m_Equipment[Count] = m_Chest[i];
		CalcEquipmentStat(m_Chest[i]);
	}
	for (int i = 0; i < m_Status.BackCount; i++, Count++)
	{
		if (i >= m_Back.size()) m_Back.push_back(0);
		m_Equipment[Count] = m_Back[i];
		CalcEquipmentStat(m_Back[i]);
	}
	for (int i = 0; i < m_Status.LegCount; i++, Count++)
	{
		if (i >= m_Leg.size()) m_Leg.push_back(0);
		m_Equipment[Count] = m_Leg[i];
		CalcEquipmentStat(m_Leg[i]);
	}
	for (int i = 0; i < m_Status.ShlderCount; i++, Count++)
	{
		if (i >= m_Shlder.size()) m_Shlder.push_back(0);
		m_Equipment[Count] = m_Shlder[i];
		CalcEquipmentStat(m_Shlder[i]);
	}
	for (int i = 0; i < m_Status.CardCount; i++, Count++)
	{
		if (i >= m_Card.size()) m_Card.push_back(0);
		m_Equipment[Count] = m_Card[i];
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
	bool Defeated = false;
	std::string Text = m_Name;
	if (m_UnitNo != 0)
		Text += "(" + std::to_string(m_UnitNo) + ")";

	Damage *= (float)(100 - m_Resist[(int)type - 1]) / (100);
	if (type == DAMAGE_TYPE::KINETIC)
	{
		Damage *= 100.0f / (100 + m_Protection);
		Damage -= Dice::DiceRoll(m_Protection / 4);
	}
	Damage = max(Damage, 0);

	if (Damage == 0)
		((CTextManager*)m_TextManager)->EnterText("  Hit - " + Text);
	else
		((CTextManager*)m_TextManager)->EnterText("  Hit - " + Text);

	m_Life = max(m_Life - Damage, 0);

	if (m_Life <= 0)
	{
		((CTextManager*)m_TextManager)->EnterText("  " + Text + " destroyed");
		Defeated = true;
	}
	return Defeated;
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

IUnit::EquippedStat IUnit::GetEquipped()
{
	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;
	EquippedStat Stat = {};
	std::uint8_t Count = 0;
	cEquipDataBase::Equipment temp;

	for (int i = 0; i < m_Status.HeadCount; i++, Count++)
	{
		Stat.Equipment[Count]= "Head  :";
	}
	for (int i = 0; i < m_Status.ArmCount; i++, Count++)
	{
		Stat.Equipment[Count] = "Arm   :";
	}
	for (int i = 0; i < m_Status.HandCount; i++, Count++)
	{
		Stat.Equipment[Count] = "Hand  :";
	}
	for (int i = 0; i < m_Status.ChestCount; i++, Count++)
	{
		Stat.Equipment[Count] = "Chest :";
	}
	for (int i = 0; i < m_Status.BackCount; i++, Count++)
	{
		Stat.Equipment[Count] = "Back  :";
	}
	for (int i = 0; i < m_Status.LegCount; i++, Count++)
	{
		Stat.Equipment[Count] = "Leg   :";
	}
	for (int i = 0; i < m_Status.ShlderCount; i++, Count++)
	{
		Stat.Equipment[Count] = "Shlder:";
	}
	for (int i = 0; i < m_Status.CardCount; i++, Count++)
	{
		Stat.Equipment[Count] = "Card  :";
	}

	for (int i = 0; i < 16; i++)
	{
		if (i >= m_Status.EquipCount)
		{
			Stat.Equipment[i] = "---------------------------------------";
			continue;
		}
		if (m_Equipment[i] == 0)
		{
			Stat.Equipment[i] += "--------------------------------";
			continue;
		}
		temp = EquipDB->GetData(m_Equipment[i]);

		Stat.Equipment[i] += temp.Name;
		if (temp.Type == cEquipDataBase::EQUIPMENT_TYPE::WEAPON)
		{
			Stat.Equipment[i] +=
				"(" + std::to_string(temp.DmgRollData.DiceCount) + 'd' +
				std::to_string(temp.DmgRollData.DiceFaces);
			if (temp.DmgRollData.ModValue != 0)
			{
				if (temp.DmgRollData.ModValue > 0)
					Stat.Equipment[i] += "+";
				Stat.Equipment[i] += std::to_string(temp.DmgRollData.ModValue);
			}
			Stat.Equipment[i] += " ";
			switch (temp.DamageType)
			{
			case IUnit::DAMAGE_TYPE::KINETIC:
				Stat.Equipment[i] += "KI)";
				break;
			case IUnit::DAMAGE_TYPE::THERMAL:
				Stat.Equipment[i] += "TH)";
				break;
			case IUnit::DAMAGE_TYPE::ELECTRO:
				Stat.Equipment[i] += "EL)";
				break;
			default:
				break;
			}
		}
	}
	Stat.Count = m_Status.EquipCount;

	return Stat;
}

IUnit::InventoryStat IUnit::GetInventory()
{
	cItemDataBase* ItemDB = (cItemDataBase*)m_ItemDataBase;
	InventoryStat Stat = {};
	cItemDataBase::ItemData temp;

	auto it = m_ItemList.begin();
	auto end = m_ItemList.end();

	for (int i = 0; i < m_Inventory;i++)
	{
		Stat.Item[i] = std::to_string(i) + ": ";

		if(it == end)
		{
			Stat.Item[i] += "--------------------------------";
			continue;
		}
		if ((*it).ID == 0 || (*it).Amount == 0)
		{
			Stat.Item[i] += "--------------------------------";
			continue;
		}
		temp = ItemDB->GetData((*it).ID, (*it).IsEquipment);

		Stat.Item[i] += std::to_string((*it).Amount) + "x ";
		Stat.Item[i] += temp.Name;
		it++;
	}
	Stat.Count = m_Status.EquipCount;

	return Stat;
}

void IUnit::Dead()
{
	m_MapObj->PutItem(m_OnMapPos.x, m_OnMapPos.y, (int)cItemDataBase::MATERIALS::AMMO, m_Status.Ammo / aqua::Rand(5, 10));

	cUnitDataBase::UnitData Data=((cUnitDataBase*)m_UnitDataBase)->GetData(m_Status.ID);
	int DropXpos = m_OnMapPos.x;
	int DropYpos = m_OnMapPos.y;

	for (int i = 0; i < 4; i++)
	{
		if (Data.DropItemId[i] == 0) continue;

		DropXpos = m_OnMapPos.x;
		DropYpos = m_OnMapPos.y;
		switch (i)
		{
		case 0:
			DropXpos--;
			break;
		case 1:
			DropXpos++;
			break;
		case 2:
			DropYpos--;
			break;
		case 3:
			DropYpos++;
			break;
		}
		if (Dice::PercentRoll(Data.DropRate[i]))
			m_MapObj->PutItem(DropXpos, DropYpos, Data.DropItemId[i], 1);
	}
	DeleteObject();
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
	if (UnitMgr->HasSpace(pos)) return false;

	aqua::CVector2 Diff = pos - m_OnMapPos;
	std::string Text = m_Name;
	if (m_UnitNo != 0)
		Text += "(" + std::to_string(m_UnitNo) + ")";

	bool Attacked = false;

	for (int i = 0; i < 16; i++)
	{
		if (m_Weapon[i].ID == 0) continue;
		if (m_Weapon[i].Range < Diff.Length())
			if (Diff.Length() > 1.42f)
				continue;

		if (m_Batt - m_Weapon[i].Energy < 0) continue;
		if (m_Ammo - m_Weapon[i].Ammo < 0) continue;

		((CTextManager*)m_TextManager)->EnterText(Text + ":" + m_Weapon[i].Name);

		if (!UnitMgr->Attack(pos, Dice::DiceRoll(m_Weapon[i].DmgRollData), m_Weapon[i].DamageType)){
			((CTextManager*)m_TextManager)->EnterText("  Target not found");
			return false;
		}
		m_Batt = max(m_Batt - m_Weapon[i].Energy, 0);
		m_Ammo = max(m_Ammo - m_Weapon[i].Ammo, 0);
		m_Heat = min(m_Heat + m_Weapon[i].Heat, 999);

		Attacked = true;
	}
	return Attacked;
}

void IUnit::CalcEquipmentStat(int id)
{
	if (id <= 0) return;

	cEquipDataBase* EquipDB = (cEquipDataBase*)m_EquipmentDB;
	cEquipDataBase::Equipment Equipment = EquipDB->GetData(id);

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
		m_Weapon[m_WeaponCount] = Temp;
		m_WeaponCount++;
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
