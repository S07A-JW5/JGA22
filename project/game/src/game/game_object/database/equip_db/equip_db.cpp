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
		Temp.EquipmentID = EquipmentCSV.GetInteger(i, 0);
		Temp.Name = EquipmentCSV.GetString(i, 1);
		Temp.Type = (EQUIPMENT_TYPE)EquipmentCSV.GetInteger(i, 2);
		Temp.Durability = EquipmentCSV.GetInteger(i, 3);
		Temp.AttatchPart = EquipmentCSV.GetInteger(i, 4);
		Temp.Weight = EquipmentCSV.GetInteger(i, 5);
		Temp.Energy = EquipmentCSV.GetInteger(i, 6);
		Temp.Heat = EquipmentCSV.GetInteger(i, 7);
		Temp.Range = EquipmentCSV.GetInteger(i, 8);
		Temp.DamageType = (IUnit::DAMAGE_TYPE)EquipmentCSV.GetInteger(i, 9);
		Temp.MinDamage = EquipmentCSV.GetInteger(i, 10);
		Temp.MaxDamage = EquipmentCSV.GetInteger(i, 11);
		Temp.Ammo = EquipmentCSV.GetInteger(i, 12);
		Temp.Resist[0] = EquipmentCSV.GetInteger(i, 13);
		Temp.Resist[1] = EquipmentCSV.GetInteger(i, 14);
		Temp.Resist[2] = EquipmentCSV.GetInteger(i, 15);
		Temp.Protection = EquipmentCSV.GetInteger(i, 16);
		Temp.Support = EquipmentCSV.GetInteger(i, 17);
		Temp.BaseHeat = EquipmentCSV.GetInteger(i, 18);
		Temp.Inventory = EquipmentCSV.GetInteger(i, 19);
		Temp.MaxBatt = EquipmentCSV.GetInteger(i, 20);
		Temp.MaxAmmo = EquipmentCSV.GetInteger(i, 21);
		Temp.MaxPart = EquipmentCSV.GetInteger(i, 22);

		m_EquipmentDataList.push_back(Temp);
	}
	EquipmentCSV.Unload();
}
