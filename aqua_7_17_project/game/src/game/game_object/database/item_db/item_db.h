#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cItemDataBase : public aqua::IGameObject
{
public:
	enum class ITEM_TYPE
	{
		DUMMY,		//ダミー
		ITEM,		//アイテム
		CONSUMABLE,	//使用可能
		INSTANT,	//拾った瞬間消費される
		EQUIPMENT,	//装備品
	};

	enum class CONSUME_TYPE
	{
		NOT_CONSUMABLE,	//使うことの出来ないアイテム
		SELF,	//自分自身
		ENEMY,	//敵
		THROW,	//投げ物
	};

	enum class MATERIALS
	{
		DUMMY,	//ダミー
		AMMO,	//弾薬
		PARTS,	//部品
		ENERGY,	//電力(バッテリー)

		COUNT
	};


	struct ItemData
	{
		uint16_t ItemID; //アイテムID(0は空欄)

		std::string Name;			//アイテム名
		std::string Description;	//説明文

		ITEM_TYPE		Type;		//アイテムタイプ
		CONSUME_TYPE	Consume;	//消耗品タイプ
		int16_t			Life;		//使用時HP回復量
		int16_t			Energy;		//使用時電力補給量
		int16_t			Parts;		//使用時部品補給量
		int16_t			Ammo;		//使用時弾薬補給量
		int16_t			Cooling;	//使用時冷却量

		IUnit::DAMAGE_TYPE	DamageType;		//ダメージ属性
		Dice::DiceRollData	DmgRollData;	//ダメージロールデータ
		uint8_t				Range;			//射程(0の場合、近接攻撃)
	};

	//コンストラクタ
	cItemDataBase(aqua::IGameObject* parent);

	//デストラクタ
	~cItemDataBase() = default;

	//初期化
	void Initialize() override;

	//解放
	void Finalize() override;

	//装備品IDをアイテムIDに変換
	uint16_t EquipmentItem(int id);

	//アイテムデータ取得
	ItemData GetData(int id, bool equipment = false);

private:
	//アイテムデータ読込
	void Load();

	std::vector<ItemData> m_ItemDataList;

	int m_ItemCount; //アイテムの個数
};