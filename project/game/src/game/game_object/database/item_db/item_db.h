#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cItemDataBase : public aqua::IGameObject
{
public:
	enum class ITEM_TYPE
	{
		DUMMY,		//ﾀﾞﾐｰ
		ITEM,		//アイテム
		CONSUMABLE,	//使用可能
		INSTANT,		//拾った瞬間消費される
		EQUIPMENT,	//装備品
	};

	enum class CONSUME_TYPE
	{
		NOT_CONSUMABLE,
		SELF,	//自分自身
		ENEMY,	//敵
		THROW,	//投げ物
	};

	enum class MATERIALS
	{
		DUMMY,
		AMMO,	//弾薬
		PARTS,	//部品
		ENERGY,	//ﾊﾞｯﾃﾘｰ

		COUNT
	};


	struct ItemData
	{
		std::uint16_t ItemID; //アイテムID(0は空欄)

		std::string Name;			//アイテム名
		std::string Description;	//説明文

		ITEM_TYPE		Type;	//アイテムタイプ
		CONSUME_TYPE	Consume;	//消耗品タイプ
		std::int16_t	Life;	//使用時HP回復量
		std::int16_t	Energy;	//使用時ﾊﾞｯﾃﾘｰ回復量
		std::int16_t	Parts;	//使用時部品補給量
		std::int16_t	Ammo;	//使用時弾薬補給量
		std::int16_t	Cooling;	//使用時冷却量

		IUnit::DAMAGE_TYPE DamageType;	//ﾀﾞﾒｰｼﾞ属性
		Dice::DiceRollData DmgRollData;	//ﾀﾞﾒｰｼﾞﾛｰﾙﾃﾞｰﾀ
		std::uint8_t Range;			//射程(0の場合、近接攻撃)
	};

	cItemDataBase(aqua::IGameObject* parent);

	~cItemDataBase() = default;

	void Initialize() override;

	void Finalize() override;

	std::uint16_t EquipmentItem(int id);

	ItemData GetData(int id, bool equipment = false);

private:
	void Load();

	std::vector<ItemData> m_ItemDataList;

	int m_ItemCount;
};