#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cUnitDataBase : public aqua::IGameObject
{
public:
	struct UnitData
	{
		std::string	TexFilePath;	//画像ファイルパス
		std::string	Name;		//キャラ名

		std::uint16_t Life;		//耐久力
		std::uint16_t Cooling;		//冷却能力
		std::uint16_t Battery;		//ﾊﾞｯﾃﾘｰ容量
		std::uint16_t Parts;		//部品所持上限
		std::uint16_t Ammo;		//弾薬所持上限
		std::int16_t  Resist[3];	//耐性値(%)
		std::uint8_t  Inventory;	//ｲﾝﾍﾞﾝﾄﾘ容量

		std::uint8_t HeadCount;	//「頭」ｽﾛｯﾄ数
		std::uint8_t ArmCount;		//「腕」ｽﾛｯﾄ数
		std::uint8_t HandCount;	//「手」ｽﾛｯﾄ数
		std::uint8_t ChestCount;	//「胸部」ｽﾛｯﾄ数
		std::uint8_t BackCount;	//「背中」ｽﾛｯﾄ数
		std::uint8_t LegCount;		//「脚」ｽﾛｯﾄ数
		std::uint8_t ShlderCount;	//「肩」ｽﾛｯﾄ数
		std::uint8_t CardCount;	//「拡張ｶｰﾄﾞ」ｽﾛｯﾄ数

		std::uint16_t Equipped[16];	//装備している装備品ID
		std::uint16_t DropItemId[4];	//ドロップアイテムID
		std::uint8_t  DropRate[4];		//落とす確率(%)
	};

	cUnitDataBase(aqua::IGameObject* parent);

	~cUnitDataBase() = default;

	void Initialize() override;

	void Finalize() override;

	UnitData GetData(int id);

private:
	void Load();
	std::vector<UnitData> m_UnitDataList;
};