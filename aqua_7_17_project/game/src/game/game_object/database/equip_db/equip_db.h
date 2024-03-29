#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum class EQUIPMENT_TYPE
	{
		DUMMY,		//ÀÞÐ°
		WEAPON,		//í
		ARMOR,		//b
		SUPPORT,	//â
		UTIL,		//õi
	};

	enum class EQUIPMENT_SLOT
	{
		DUMMY,		//ÀÞÐ°
		HEAD,		//ª
		ARM,		//r
		CHEST,		//¹
		BACK,		//w
		LEG,		//r
		SHOULDER,	//¨
		CARD,		//g£¶°ÄÞ½Û¯Ä
	};

	struct Equipment
	{
		uint16_t EquipmentID;	//õiID(0Íó)

		std::string Name;		//õiÌ¼O
		std::string Description;//à¾¶

		EQUIPMENT_TYPE Type;	//õi^Cv
		EQUIPMENT_SLOT Slot;	//õÂ\Ê

		uint16_t	Durability;	//õiÌÏvl
		uint16_t	AttatchPart;//ætÉKvÈi
		uint8_t		Weight;		//õdÊ
		uint8_t		Energy;		//ÁïÊÞ¯ÃØ°
		uint8_t		Heat;		//­MÊ

		//======================íp========================
		//					Range;		//Ëö(0ÌêAßÚUí)
		IUnit::DAMAGE_TYPE	DamageType;	//ÀÞÒ°¼Þ®«
		Dice::DiceRollData	DmgRollData;//ÀÞÒ°¼ÞÛ°ÙÃÞ°À
		uint8_t				EffectID;	//UGtFNgID
		uint8_t				Ammo;		//eòÁïÊ

		//======================bp========================
		int16_t	Resist[3];	//Ï«l(%)
		int16_t	Protection;	//häÍ

		//======================Ú®p========================
		std::uint8_t  Support;		//õdÊãÀ

		//======================»Ì¼p======================
		uint8_t		Power;		//dÍÊ
		uint8_t		Range;		//FÂ\£
		uint8_t		Cooling;	//âp\Í
		int16_t		BaseHeat;	//MºÀl¸Ê
		uint8_t		Inventory;	//²ÝÍÞÝÄØeÊ¸Ê
		uint16_t	MaxBatt;	//ÊÞ¯ÃØ°eÊ¸Ê
		uint16_t	MaxAmmo;	//eòãÀ¸Ê
		uint16_t	MaxPart;	//iãÀ¸Ê
	};

	//RXgN^
	cEquipDataBase(aqua::IGameObject* parent);

	//fXgN^
	~cEquipDataBase() = default;

	//ú»
	void Initialize() override;

	//ðú
	void Finalize() override;

	//õif[^æ¾
	Equipment GetData(int id);

private:
	//õif[^Ç
	void Load();

	std::vector<Equipment> m_EquipmentDataList;
};