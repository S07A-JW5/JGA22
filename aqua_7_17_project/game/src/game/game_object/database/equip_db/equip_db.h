#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum class EQUIPMENT_TYPE
	{
		DUMMY,		//ﾀﾞﾐｰ
		WEAPON,		//武器
		ARMOR,		//装甲
		SUPPORT,	//補助
		UTIL,		//装備品
	};

	enum class EQUIPMENT_SLOT
	{
		DUMMY,		//ﾀﾞﾐｰ
		HEAD,		//頭
		ARM,		//腕
		CHEST,		//胸部
		BACK,		//背中
		LEG,		//脚
		SHOULDER,	//肩
		CARD,		//拡張ｶｰﾄﾞｽﾛｯﾄ
	};

	struct Equipment
	{
		uint16_t EquipmentID;	//装備品ID(0は空欄)

		std::string Name;		//装備品の名前
		std::string Description;//説明文

		EQUIPMENT_TYPE Type;	//装備品タイプ
		EQUIPMENT_SLOT Slot;	//装備可能部位

		uint16_t	Durability;	//装備品の耐久値
		uint16_t	AttatchPart;//取付に必要な部品数
		uint8_t		Weight;		//装備時重量
		uint8_t		Energy;		//消費ﾊﾞｯﾃﾘｰ
		uint8_t		Heat;		//発熱量

		//======================武器用========================
		//					Range;		//射程(0の場合、近接攻撃武器)
		IUnit::DAMAGE_TYPE	DamageType;	//ﾀﾞﾒｰｼﾞ属性
		Dice::DiceRollData	DmgRollData;//ﾀﾞﾒｰｼﾞﾛｰﾙﾃﾞｰﾀ
		uint8_t				EffectID;	//攻撃エフェクトID
		uint8_t				Ammo;		//弾薬消費量

		//======================装甲用========================
		int16_t	Resist[3];	//耐性値(%)
		int16_t	Protection;	//防御力

		//======================移動用========================
		std::uint8_t  Support;		//装備重量上限

		//======================その他用======================
		uint8_t		Power;		//電力供給量
		uint8_t		Range;		//視認可能距離
		uint8_t		Cooling;	//冷却能力
		int16_t		BaseHeat;	//熱下限値増減量
		uint8_t		Inventory;	//ｲﾝﾍﾞﾝﾄﾘ容量増減量
		uint16_t	MaxBatt;	//ﾊﾞｯﾃﾘｰ容量増減量
		uint16_t	MaxAmmo;	//弾薬所持上限増減量
		uint16_t	MaxPart;	//部品所持上限増減量
	};

	//コンストラクタ
	cEquipDataBase(aqua::IGameObject* parent);

	//デストラクタ
	~cEquipDataBase() = default;

	//初期化
	void Initialize() override;

	//解放
	void Finalize() override;

	//装備品データ取得
	Equipment GetData(int id);

private:
	//装備品データ読込
	void Load();

	std::vector<Equipment> m_EquipmentDataList;
};