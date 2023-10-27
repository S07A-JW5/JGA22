#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cUnitDataBase : public aqua::IGameObject
{
public:
	struct UnitData
	{
		std::string	TexFilePath;//画像ファイルパス
		std::string	Name;		//キャラ名

		uint16_t Life;		//耐久力
		uint16_t Cooling;	//冷却能力
		uint16_t Battery;	//ﾊﾞｯﾃﾘｰ容量
		uint16_t Parts;		//部品所持上限
		uint16_t Ammo;		//弾薬所持上限
		int16_t  Resist[3];	//耐性値(%)
		uint8_t  Inventory;	//ｲﾝﾍﾞﾝﾄﾘ容量

		uint8_t HeadCount;	//「頭」ｽﾛｯﾄ数
		uint8_t ArmCount;	//「腕」ｽﾛｯﾄ数
		uint8_t ChestCount;	//「胸部」ｽﾛｯﾄ数
		uint8_t BackCount;	//「背中」ｽﾛｯﾄ数
		uint8_t LegCount;	//「脚」ｽﾛｯﾄ数
		uint8_t ShlderCount;//「肩」ｽﾛｯﾄ数
		uint8_t CardCount;	//「拡張ｶｰﾄﾞ」ｽﾛｯﾄ数

		uint16_t Equipped[16];	//装備している装備品ID
		uint16_t DropItemId[4];	//ドロップアイテムID
		uint8_t  DropRate[4];	//落とす確率(%)
	};

	//コンストラクタ
	cUnitDataBase(aqua::IGameObject* parent);

	//デストラクタ
	~cUnitDataBase() = default;

	//初期化
	void Initialize() override;

	//解放
	void Finalize() override;

	//キャラデータ取得
	UnitData GetData(int id);

private:
	//キャラデータ読込
	void Load();

	std::vector<UnitData> m_UnitDataList;
};