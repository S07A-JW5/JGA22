#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum EQUIPMENT_TYPE
	{
		CAMERA,	//カメラ
		WEAPON,	//武器
		ARMOR,	//装甲
		TRANSP,	//移動
		UTIL,	//装備品
	};

	struct Equipment
	{
		std::int16_t EquipmentID; //装備品ID(-1以下は空欄)

		char Name[24]; //装備品の名前

		EQUIPMENT_TYPE Type; //装備品タイプ

		std::uint16_t Durability;	//装備品の耐久値
		std::uint16_t AttatchPart;	//取付に必要な部品数
		std::uint8_t Weight;		//装備時重量
		std::uint8_t Energy;		//消費ﾊﾞｯﾃﾘｰ
		std::uint8_t Heat;			//発熱量

		//======================カメラ用======================
		std::uint8_t Range;	//視認可能距離

		//======================武器用========================
		IUnit::DAMAGE_TYPE DamageType;	//ﾀﾞﾒｰｼﾞ属性
		std::uint8_t MinDamage;			//最小ダメージ
		std::uint8_t MaxDamage;			//最大ダメージ
		//   uint8_t Range;				//射程(0の場合、近接攻撃武器)(カメラ用と共用とする)
		std::uint8_t Ammo;				//弾薬消費量

		//======================装甲用========================
		std::int16_t  Resist[3];//耐性値(%)
		std::int16_t  DmgCut[3];//ﾀﾞﾒｰｼﾞｶｯﾄ量

		//======================移動用========================
		std::uint8_t  Support;//装備重量上限

		//======================その他用======================
		std::uint16_t BaseHeat;	//熱下限値増減量
		std::uint8_t  Inventory;//ｲﾝﾍﾞﾝﾄﾘ容量増減量
		std::uint16_t MaxBatt;	//ﾊﾞｯﾃﾘｰ容量増減量
		std::uint16_t MaxAmmo;	//弾薬所持上限増減量

	};
};