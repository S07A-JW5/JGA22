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
		Temp.WeaponCount	= UnitDataCSV.GetInteger(i, 12);
		Temp.ArmorCount	= UnitDataCSV.GetInteger(i, 13);
		Temp.TranspCount	= UnitDataCSV.GetInteger(i, 14);
		Temp.UtilCount	= UnitDataCSV.GetInteger(i, 15);
		for (int j = 0; j < 20; j++)
			Temp.Equipped[j] = UnitDataCSV.GetInteger(i, j + 16);
		for (int j = 0; j < 5; j++)
		{
			Temp.DropItemId[j]	= UnitDataCSV.GetInteger(i, j + 36);
			Temp.DropRate[j]	= UnitDataCSV.GetInteger(i, j + 41);
		}
		m_UnitDataList.push_back(Temp);
	}
	UnitDataCSV.Unload();
}
