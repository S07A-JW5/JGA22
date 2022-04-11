#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum EQUIPMENT_TYPE
	{
		CAMERA,	//J
		WEAPON,	//í
		ARMOR,	//b
		TRANSP,	//Ú®
		UTIL,	//õi
	};

	struct Equipment
	{
		std::int16_t EquipmentID; //õiID(-1ÈºÍó)

		char Name[24]; //õiÌ¼O

		EQUIPMENT_TYPE Type; //õi^Cv

		std::uint16_t Durability;	//õiÌÏvl
		std::uint16_t AttatchPart;	//ætÉKvÈi
		std::uint8_t Weight;		//õdÊ
		std::uint8_t Energy;		//ÁïÊÞ¯ÃØ°
		std::uint8_t Heat;			//­MÊ

		//======================Jp======================
		std::uint8_t Range;	//FÂ\£

		//======================íp========================
		IUnit::DAMAGE_TYPE DamageType;	//ÀÞÒ°¼Þ®«
		std::uint8_t MinDamage;			//Å¬_[W
		std::uint8_t MaxDamage;			//Åå_[W
		//   uint8_t Range;				//Ëö(0ÌêAßÚUí)(JpÆ¤pÆ·é)
		std::uint8_t Ammo;				//eòÁïÊ

		//======================bp========================
		std::int16_t  Resist[3];//Ï«l(%)
		std::int16_t  DmgCut[3];//ÀÞÒ°¼Þ¶¯ÄÊ

		//======================Ú®p========================
		std::uint8_t  Support;//õdÊãÀ

		//======================»Ì¼p======================
		std::uint16_t BaseHeat;	//MºÀl¸Ê
		std::uint8_t  Inventory;//²ÝÍÞÝÄØeÊ¸Ê
		std::uint16_t MaxBatt;	//ÊÞ¯ÃØ°eÊ¸Ê
		std::uint16_t MaxAmmo;	//eòãÀ¸Ê

	};
};