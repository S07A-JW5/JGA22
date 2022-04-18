#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum class EQUIPMENT_TYPE
	{
		DUMMY,	//ﾀﾞﾐｰ
		WEAPON,	//武器
		ARMOR,	//装甲
		TRANSP,	//移動
		UTIL,	//装備品
	};

	struct Equipment
	{
		std::uint16_t EquipmentID; //装備品ID(0は空欄)

		std::string Name;			//装備品の名前
		std::string Description;	//説明文

		EQUIPMENT_TYPE Type;		//装備品タイプ

		std::uint16_t	Durability;	//装備品の耐久値
		std::uint16_t	AttatchPart;	//取付に必要な部品数
		std::uint8_t	Weight;		//装備時重量
		std::uint8_t	Energy;		//消費ﾊﾞｯﾃﾘｰ
		std::uint8_t	Heat;		//発熱量

		//======================武器用========================
		IUnit::DAMAGE_TYPE DamageType;	//ﾀﾞﾒｰｼﾞ属性
		std::uint8_t MinDamage;		//最小ダメージ
		std::uint8_t MaxDamage;		//最大ダメージ
		//   uint8_t Range;			//射程(0の場合、近接攻撃武器)
		std::uint8_t Ammo;				//弾薬消費量

		//======================装甲用========================
		std::int16_t  Resist[3];	//耐性値(%)
		std::int16_t  Protection;	//防御力

		//======================移動用========================
		std::uint8_t  Support;		//装備重量上限

		//======================その他用======================
		std::uint8_t	Power;		//電力供給量
		std::uint8_t	Range;		//視認可能距離
		std::uint8_t	Cooling;		//冷却能力
		std::int16_t	BaseHeat;		//熱下限値増減量
		std::uint8_t	Inventory;	//ｲﾝﾍﾞﾝﾄﾘ容量増減量
		std::uint16_t	MaxBatt;		//ﾊﾞｯﾃﾘｰ容量増減量
		std::uint16_t	MaxAmmo;		//弾薬所持上限増減量
		std::uint16_t	MaxPart;		//部品所持上限増減量
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