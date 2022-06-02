#include "equip_db.h"

cEquipDataBase::cEquipDataBase(aqua::IGameObject* parent)
	: IGameObject(parent, "EquipmentDB")
{
}

void cEquipDataBase::Initialize()
{
	Load();
}

void cEquipDataBase::Finalize()
{
	m_EquipmentDataList.clear();
}

cEquipDataBase::Equipment cEquipDataBase::GetData(int id)
{
	if (id >= m_EquipmentDataList.size()) return Equipment();
	return m_EquipmentDataList[id];
}

void cEquipDataBase::Load()
{
	m_EquipmentDataList.clear();
	Equipment Temp;
	aqua::CCSVLoader EquipmentCSV;
	EquipmentCSV.Load("data\\data\\equipment.csv");
	for (int i = 1; i < EquipmentCSV.GetRows(); i++)
	{
		Temp.EquipmentID	= (uint16_t)EquipmentCSV.GetInteger(i, 0);
		Temp.Name			= EquipmentCSV.GetString(i, 1);
		Temp.Description	= EquipmentCSV.GetString(i, 2);
		Temp.Type			= (EQUIPMENT_TYPE)EquipmentCSV.GetInteger(i, 3);
		Temp.Slot			= (EQUIPMENT_SLOT)EquipmentCSV.GetInteger(i, 4);
		Temp.Durability	= (uint16_t)EquipmentCSV.GetInteger(i, 5);
		Temp.AttatchPart	= (uint16_t)EquipmentCSV.GetInteger(i, 6);
		Temp.Weight		= (uint8_t)EquipmentCSV.GetInteger(i, 7);
		Temp.Energy		= (uint8_t)EquipmentCSV.GetInteger(i, 8);
		Temp.Heat			= (uint8_t)EquipmentCSV.GetInteger(i, 9);
		Temp.Range		= (uint8_t)EquipmentCSV.GetInteger(i, 10);
		Temp.DamageType	= (IUnit::DAMAGE_TYPE)EquipmentCSV.GetInteger(i, 11);
		Temp.DmgRollData	= Dice::GetDiceRollData(EquipmentCSV.GetString(i, 12));
		Temp.Ammo			= (uint8_t)EquipmentCSV.GetInteger(i, 13);
		Temp.Resist[0]	= (int16_t)EquipmentCSV.GetInteger(i, 14);
		Temp.Resist[1]	= (int16_t)EquipmentCSV.GetInteger(i, 15);
		Temp.Resist[2]	= (int16_t)EquipmentCSV.GetInteger(i, 16);
		Temp.Protection	= (int16_t)EquipmentCSV.GetInteger(i, 17);
		Temp.Support		= (uint8_t)EquipmentCSV.GetInteger(i, 18);
		Temp.BaseHeat		= (int16_t)EquipmentCSV.GetInteger(i, 19);
		Temp.Inventory	= (uint8_t)EquipmentCSV.GetInteger(i, 20);
		Temp.MaxBatt		= (uint16_t)EquipmentCSV.GetInteger(i, 21);
		Temp.MaxAmmo		= (uint16_t)EquipmentCSV.GetInteger(i, 22);
		Temp.MaxPart		= (uint16_t)EquipmentCSV.GetInteger(i, 23);
		Temp.Power		= (uint8_t)EquipmentCSV.GetInteger(i, 24);
		Temp.Cooling		= (uint8_t)EquipmentCSV.GetInteger(i, 25);
		m_EquipmentDataList.push_back(Temp);
	}
	EquipmentCSV.Unload();
}
