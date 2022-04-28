#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cItemDataBase : public aqua::IGameObject
{
public:
	enum class ITEM_TYPE
	{
		DUMMY,		//ÀÞÐ°
		ITEM,		//ACe
		CONSUMABLE,	//gpÂ\
		INSTANT,		//EÁ½uÔÁï³êé
		EQUIPMENT,	//õi
	};

	enum class CONSUME_TYPE
	{
		NOT_CONSUMABLE,
		SELF,	//©ª©g
		ENEMY,	//G
		THROW,	//°¨
	};

	enum class MATERIALS
	{
		DUMMY,
		AMMO,	//eò
		PARTS,	//i
		ENERGY,	//ÊÞ¯ÃØ°

		COUNT
	};


	struct ItemData
	{
		std::uint16_t ItemID; //ACeID(0Íó)

		std::string Name;			//ACe¼
		std::string Description;	//à¾¶

		ITEM_TYPE		Type;	//ACe^Cv
		CONSUME_TYPE	Consume;	//ÁÕi^Cv
		std::int16_t	Life;	//gpHPñÊ
		std::int16_t	Energy;	//gpÊÞ¯ÃØ°ñÊ
		std::int16_t	Parts;	//gpiâÊ
		std::int16_t	Ammo;	//gpeòâÊ
		std::int16_t	Cooling;	//gpâpÊ

		IUnit::DAMAGE_TYPE DamageType;	//ÀÞÒ°¼Þ®«
		Dice::DiceRollData DmgRollData;	//ÀÞÒ°¼ÞÛ°ÙÃÞ°À
		std::uint8_t Range;			//Ëö(0ÌêAßÚU)
	};

	cItemDataBase(aqua::IGameObject* parent);

	~cItemDataBase() = default;

	void Initialize() override;

	void Finalize() override;

	ItemData GetData(int id, bool equipment = false);

private:
	void Load();

	std::vector<ItemData> m_ItemDataList;

	int m_ItemCount;
};