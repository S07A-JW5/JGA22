#include "chr_db.h"

cUnitDataBase::cUnitDataBase(aqua::IGameObject* parent)
	:IGameObject(parent, "UnitDataBase")
{
}

void cUnitDataBase::Initialize()
{
	Load();
}

void cUnitDataBase::Finalize()
{
	m_UnitDataList.clear();
}

cUnitDataBase::UnitData cUnitDataBase::GetData(int id)
{
	if (id >= m_UnitDataList.size()) return UnitData();
	return m_UnitDataList[id];
}

void cUnitDataBase::Load()
{
	m_UnitDataList.clear();
	UnitData Temp;
	aqua::CCSVLoader UnitDataCSV;
	UnitDataCSV.Load("data\\data\\unit.csv");
	for (int i = 1; i < UnitDataCSV.GetRows(); i++)
	{
		Temp.TexFilePath	= UnitDataCSV.GetString(i, 1);
		Temp.Name			= UnitDataCSV.GetString(i, 2);
		Temp.Life			= UnitDataCSV.GetInteger(i, 3);
		Temp.Cooling		= UnitDataCSV.GetInteger(i, 4);
		Temp.Battery		= UnitDataCSV.GetInteger(i, 5);
		Temp.Parts		= UnitDataCSV.GetInteger(i, 6);
		Temp.Ammo			= UnitDataCSV.GetInteger(i, 7);
		Temp.Resist[0]	= UnitDataCSV.GetInteger(i, 8);
		Temp.Resist[1]	= UnitDataCSV.GetInteger(i, 9);
		Temp.Resist[2]	= UnitDataCSV.GetInteger(i, 10);
		Temp.Inventory	= UnitDataCSV.GetInteger(i, 11);
		Temp.HeadCount	= UnitDataCSV.GetInteger(i, 12);
		Temp.ArmCount		= UnitDataCSV.GetInteger(i, 13);
		Temp.ChestCount	= UnitDataCSV.GetInteger(i, 14);
		Temp.BackCount	= UnitDataCSV.GetInteger(i, 15);
		Temp.LegCount		= UnitDataCSV.GetInteger(i, 16);
		Temp.ShlderCount	= UnitDataCSV.GetInteger(i, 17);
		Temp.CardCount	= UnitDataCSV.GetInteger(i, 18);
		for (int j = 0; j < 16; j++)
			Temp.Equipped[j] = UnitDataCSV.GetInteger(i, j + 19);
		for (int j = 0; j < 4; j++)
		{
			Temp.DropItemId[j]	= UnitDataCSV.GetInteger(i, j * 2 + 35);
			Temp.DropRate[j]	= UnitDataCSV.GetInteger(i, j * 2 + 1 + 35);
		}
		m_UnitDataList.push_back(Temp);
	}
	UnitDataCSV.Unload();
}
