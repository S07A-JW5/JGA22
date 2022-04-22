#pragma once
#include "aqua.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"

class IUnit : public aqua::IGameObject
{
public:
	enum class DAMAGE_TYPE
	{
		DUMMY,	//ﾀﾞﾐｰ
		KINETIC,	//物理
		THERMAL,	//熱
		ELECTRO,	//電気
	};
	enum class DIRECTION
	{
		NORTH,
		SOUTH,
		EAST,
		WEST,

		COUNT,
		DUMMY = 0xff
	};
	enum class STATUS
	{
		LIFE,
		HEAT,
		BATT,
		PARTS,
		AMMO,
	};

	IUnit(aqua::IGameObject* parent, std::string name);

	~IUnit() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void Create(int id, int unit_no);

	virtual void CalcStatus();

	aqua::CVector2 GetPosition();

	void SetPosition(aqua::CVector2 pos);

	void GetMap(cMap* map);

	bool TakeDamage(int damage, IUnit::DAMAGE_TYPE type);

	bool DidAction();

	void SetActFlag(bool flag);

	int GetStatus(IUnit::STATUS stat);

	virtual bool Action();

protected:
	enum class ACTION
	{
		DUMMY,
		WAIT,
		MOVE,
		ATTACK,
	};

	struct status
	{
		std::uint16_t Life;		//基礎耐久力
		std::uint16_t Cooling;		//基礎冷却能力
		std::uint16_t Battery;		//基礎ﾊﾞｯﾃﾘｰ容量
		std::uint16_t Parts;		//基礎部品所持上限
		std::uint16_t Ammo;		//基礎弾薬所持上限
		std::int16_t  Resist[3];	//基礎耐性値(%)
		std::uint8_t  Inventory;	//基礎ｲﾝﾍﾞﾝﾄﾘ容量

		std::uint8_t WeaponCount;	//「腕」ｽﾛｯﾄ数
		std::uint8_t ArmorCount;	//「装甲」ｽﾛｯﾄ数
		std::uint8_t TranspCount;	//「移動」ｽﾛｯﾄ数
		std::uint8_t UtilCount;	//「その他」ｽﾛｯﾄ数
	};

	struct WeaponStat
	{
		std::uint16_t	ID;				//装備品ID(0は空欄)
		std::string	Name;			//装備品の名前
		IUnit::DAMAGE_TYPE DamageType;	//ﾀﾞﾒｰｼﾞ属性
		std::uint8_t	MinDamage;		//最小ダメージ
		std::uint8_t	MaxDamage;		//最大ダメージ
		std::uint8_t	Range;			//射程
		std::uint8_t	Heat;			//発熱量
		std::uint8_t	Ammo;			//弾薬消費量
		std::uint8_t	Energy;			//消費ﾊﾞｯﾃﾘｰ
	};

	virtual bool Wait();

	virtual bool Move();

	virtual bool Attack(aqua::CVector2 pos);

	void CalcBasicEquipmentStat(int id);

	aqua::IGameObject* m_SoundManager;	//ｻｳﾝﾄﾞﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_UnitManager;	//ﾕﾆｯﾄﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_TextManager;	//ﾃｷｽﾄﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_UIManager;		//UIﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_EquipmentDB;	//装備品DBのﾎﾟｲﾝﾀ

	status m_Status;

	aqua::CVector2 m_OnMapPos;	//マップ上での位置
	aqua::CVector2 m_Position;	//ｽﾌﾟﾗｲﾄの位置
	aqua::CSprite m_Sprite;	//キャラスプライト

	std::string	m_Name;		//名前
	std::uint16_t	m_Life;		//現在耐久力
	std::uint16_t	m_MaxLife;	//最大耐久力
	std::int16_t	m_HeatFlow;	//発熱－冷却の総和
	std::int16_t	m_Heat;		//熱
	std::int16_t	m_BaseHeat;	//熱下限値
	std::uint8_t	m_Inventory;	//ｲﾝﾍﾞﾝﾄﾘ容量
	std::uint16_t	m_Weight;		//装備重量
	std::uint16_t	m_Support;	//装備重量上限(そうでもないけど)
	std::int16_t	m_EnergyFlow;	//電力の流出入量
	std::uint16_t	m_Batt;		//ﾊﾞｯﾃﾘｰ残量
	std::uint16_t	m_MaxBatt;	//ﾊﾞｯﾃﾘｰ容量
	std::uint16_t	m_Parts;		//所持部品
	std::uint16_t	m_MaxParts;	//部品所持上限
	std::uint16_t	m_Ammo;		//所持弾薬
	std::uint16_t	m_MaxAmmo;	//弾薬所持上限
	std::int16_t	m_Resist[3];	//耐性値(%)
	std::int16_t	m_Protection;	//防御力
	std::uint8_t	m_SightRange;	//視界半径

	std::uint8_t m_Coverage;

	std::vector<WeaponStat> m_Weapon;	//装備している武器
	std::vector<uint16_t>	 m_Armor;	//装備している装甲
	std::vector<uint16_t>	 m_Transp;	//装備している移動
	std::vector<uint16_t>	 m_Util;		//装備している装備品

	cMap* m_MapObj;
	IGameObject* m_Camera;
	int m_UnitNo;

	bool m_DidAction;
	ACTION m_DesiredAction;
	DIRECTION m_MoveTo;
};