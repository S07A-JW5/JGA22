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

cItemDataBase::ItemData cItemDataBase::GetData(int id)
{
	if (id >= m_ItemDataList.size()) return ItemData();
	return m_ItemDataList[id];
}

void cItemDataBase::Load()
{
	m_ItemDataList.clear();
	ItemData Temp;
	aqua::CCSVLoader ItemDataCSV;
	ItemDataCSV.Load("data\\data\\item.csv");
	for (int i = 1; i < ItemDataCSV.GetRows(); i++)
	{
		Temp.ItemID		= ItemDataCSV.GetInteger(i, 0);
		Temp.Name			= ItemDataCSV.GetString(i, 1);
		Temp.Description	= ItemDataCSV.GetString(i, 2);
		Temp.Type			= (ITEM_TYPE)ItemDataCSV.GetInteger(i, 3);
		Temp.Consume		= (CONSUME_TYPE)ItemDataCSV.GetInteger(i, 4);
		Temp.Life			= ItemDataCSV.GetInteger(i, 5);
		Temp.Energy		= ItemDataCSV.GetInteger(i, 6);
		Temp.Ammo			= ItemDataCSV.GetInteger(i, 7);
		Temp.Cooling		= ItemDataCSV.GetInteger(i, 8);
		Temp.DamageType	= (IUnit::DAMAGE_TYPE)ItemDataCSV.GetInteger(i, 9);
		Temp.DmgRollData	= Dice::GetDiceRollData(ItemDataCSV.GetString(i, 10));
		Temp.Range		= ItemDataCSV.GetInteger(i, 11);
		m_ItemDataList.push_back(Temp);
	}
	ItemDataCSV.Unload();
}
