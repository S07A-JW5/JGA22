#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum class EQUIPMENT_TYPE
	{
		DUMMY,	//ÀÞÐ°
		WEAPON,	//í
		ARMOR,	//b
		SUPPORT,	//â
		UTIL,	//õi
	};

	enum class EQUIPMENT_SLOT
	{
		DUMMY,	//ÀÞÐ°
		HEAD,	//ª
		ARM,		//r
		CHEST,	//¹
		BACK,	//w
		LEG,		//r
		SHOULDER,	//¨
		CARD,	//g£¶°ÄÞ½Û¯Ä
	};

	struct Equipment
	{
		std::uint16_t EquipmentID; //õiID(0Íó)

		std::string Name;			//õiÌ¼O
		std::string Description;	//à¾¶

		EQUIPMENT_TYPE Type;		//õi^Cv
		EQUIPMENT_SLOT Slot;		//õÂ\Ê

		std::uint16_t	Durability;	//õiÌÏvl
		std::uint16_t	AttatchPart;	//ætÉKvÈi
		std::uint8_t	Weight;		//õdÊ
		std::uint8_t	Energy;		//ÁïÊÞ¯ÃØ°
		std::uint8_t	Heat;		//­MÊ

		//======================íp========================
		IUnit::DAMAGE_TYPE DamageType;	//ÀÞÒ°¼Þ®«
		Dice::DiceRollData DmgRollData;	//ÀÞÒ°¼ÞÛ°ÙÃÞ°À
		//   uint8_t Range;		//Ëö(0ÌêAßÚUí)
		std::uint8_t Ammo;			//eòÁïÊ

		//======================bp========================
		std::int16_t  Resist[3];	//Ï«l(%)
		std::int16_t  Protection;	//häÍ

		//======================Ú®p========================
		std::uint8_t  Support;		//õdÊãÀ

		//======================»Ì¼p======================
		std::uint8_t	Power;		//dÍÊ
		std::uint8_t	Range;		//FÂ\£
		std::uint8_t	Cooling;		//âp\Í
		std::int16_t	BaseHeat;		//MºÀl¸Ê
		std::uint8_t	Inventory;	//²ÝÍÞÝÄØeÊ¸Ê
		std::uint16_t	MaxBatt;		//ÊÞ¯ÃØ°eÊ¸Ê
		std::uint16_t	MaxAmmo;		//eòãÀ¸Ê
		std::uint16_t	MaxPart;		//iãÀ¸Ê
	};

	cEquipDataBase(aqua::IGameObject* parent);

	~cEquipDataBase() = default;

	void Initialize() override;

	void Finalize() override;

	Equipment GetData(int id);

private:
	void Load();
	std::vector<Equipment> m_EquipmentDataList;
};