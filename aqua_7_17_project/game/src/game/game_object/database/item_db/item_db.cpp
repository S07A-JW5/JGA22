#include "item_db.h"

cItemDataBase::cItemDataBase(aqua::IGameObject* parent)
	: IGameObject(parent, "ItemDataBase")
{
}

void cItemDataBase::Initialize()
{
	Load();
}

void cItemDataBase::Finalize()
{
	m_ItemDataList.clear();
}

uint16_t cItemDataBase::EquipmentItem(int id)
{
	if (id <= 0) return 0;
	return (uint16_t)(id + m_ItemCount);
}

cItemDataBase::ItemData cItemDataBase::GetData(int id, bool equipment)
{
	int ID = id;
	if (equipment)
		ID += m_ItemCount;

	if (ID >= m_ItemDataList.size()) return ItemData();
	return m_ItemDataList[ID];
}

void cItemDataBase::Load()
{
	m_ItemDataList.clear();
	ItemData Temp;
	aqua::CCSVLoader ItemDataCSV;
	ItemDataCSV.Load("data\\data\\item.csv");
	for (int i = 1; i < ItemDataCSV.GetRows(); i++)
	{
		Temp.ItemID			= (uint16_t)ItemDataCSV.GetInteger(i, 0);
		Temp.Name			= ItemDataCSV.GetString(i, 1);
		Temp.Description	= ItemDataCSV.GetString(i, 2);
		Temp.Type			= (ITEM_TYPE)ItemDataCSV.GetInteger(i, 3);
		Temp.Consume		= (CONSUME_TYPE)ItemDataCSV.GetInteger(i, 4);
		Temp.Life			= (int16_t)ItemDataCSV.GetInteger(i, 5);
		Temp.Energy			= (int16_t)ItemDataCSV.GetInteger(i, 6);
		Temp.Parts			= (int16_t)ItemDataCSV.GetInteger(i, 7);
		Temp.Ammo			= (int16_t)ItemDataCSV.GetInteger(i, 8);
		Temp.Cooling		= (int16_t)ItemDataCSV.GetInteger(i, 9);
		Temp.DamageType		= (IUnit::DAMAGE_TYPE)ItemDataCSV.GetInteger(i, 10);
		Temp.DmgRollData	= Dice::GetDiceRollData(ItemDataCSV.GetString(i, 11));
		Temp.Range			= (uint8_t)ItemDataCSV.GetInteger(i, 12);
		m_ItemDataList.push_back(Temp);
	}
	m_ItemCount = (int)m_ItemDataList.size();
	ItemDataCSV.Unload();

	aqua::CCSVLoader EquipmentCSV;
	EquipmentCSV.Load("data\\data\\equipment.csv");
	for (int i = 1; i < EquipmentCSV.GetRows(); i++)
	{
		Temp.ItemID			= (uint16_t)EquipmentCSV.GetInteger(i, 0);
		Temp.Name			= EquipmentCSV.GetString(i, 1);
		Temp.Description	= EquipmentCSV.GetString(i, 2);
		Temp.Type			= ITEM_TYPE::EQUIPMENT;
		Temp.Consume		= CONSUME_TYPE::NOT_CONSUMABLE;
		Temp.Life			= 0;
		Temp.Energy			= 0;
		Temp.Ammo			= 0;
		Temp.Cooling		= 0;
		Temp.DamageType		= (IUnit::DAMAGE_TYPE)EquipmentCSV.GetInteger(i, 11);
		Temp.DmgRollData	= Dice::GetDiceRollData(EquipmentCSV.GetString(i, 12));
		Temp.Range			= 0;

		if (EquipmentCSV.GetInteger(i, 3) == 1)
		{
			Temp.Name += " (" + Dice::GetDiceRollText(Temp.DmgRollData);
			switch (Temp.DamageType)
			{
			case IUnit::DAMAGE_TYPE::KINETIC:
				Temp.Name += " KI)";
				break;
			case IUnit::DAMAGE_TYPE::THERMAL:
				Temp.Name += " TH)";
				break;
			case IUnit::DAMAGE_TYPE::ELECTRO:
				Temp.Name += " EL)";
				break;
			default:
				break;
			}
		}
		m_ItemDataList.push_back(Temp);
	}
	EquipmentCSV.Unload();
}
