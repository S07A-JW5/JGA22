#pragma once
#include "aqua.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"
#include "game/tools/tools.h"

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

	struct EquippedStat
	{
		std::string	Equipment[16];
		std::uint8_t	Count;
	};

	struct InventoryStat
	{
		std::string	Item[16];
		std::uint8_t	Count;
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

	EquippedStat GetEquipped();

	InventoryStat GetInventory();

	void Dead();

	virtual bool Action();

protected:
	enum class ACTION
	{
		DUMMY,
		WAIT,
		MOVE,
		ATTACK,
		ITEM,
	};

	enum class ITEM_USE_MODE
	{
		DUMMY,
		USE,
		DISCARD,
		SWITCH,
	};

	struct status
	{
		std::uint16_t	ID;			//ﾕﾆｯﾄID
		std::uint16_t	Life;		//基礎耐久力
		std::uint16_t	Cooling;		//基礎冷却能力
		std::uint16_t	Battery;		//基礎ﾊﾞｯﾃﾘｰ容量
		std::uint16_t	Parts;		//基礎部品所持上限
		std::uint16_t	Ammo;		//基礎弾薬所持上限
		std::int16_t	Resist[3];	//基礎耐性値(%)
		std::uint8_t	Inventory;	//基礎ｲﾝﾍﾞﾝﾄﾘ容量

		std::uint8_t HeadCount;	//「頭」ｽﾛｯﾄ数
		std::uint8_t ArmCount;		//「腕」ｽﾛｯﾄ数
		std::uint8_t HandCount;	//「手」ｽﾛｯﾄ数
		std::uint8_t ChestCount;	//「胸部」ｽﾛｯﾄ数
		std::uint8_t BackCount;	//「背中」ｽﾛｯﾄ数
		std::uint8_t LegCount;		//「脚」ｽﾛｯﾄ数
		std::uint8_t ShlderCount;	//「肩」ｽﾛｯﾄ数
		std::uint8_t CardCount;	//「拡張ｶｰﾄﾞ」ｽﾛｯﾄ数
		std::uint8_t EquipCount;	//総装備スロット数
	};

	struct WeaponStat
	{
		std::uint16_t	ID;			//装備品ID(0は空欄)
		std::string	Name;		//装備品の名前
		DAMAGE_TYPE	DamageType;	//ﾀﾞﾒｰｼﾞ属性
		Dice::DiceRollData DmgRollData;//ﾀﾞﾒｰｼﾞﾛｰﾙﾃﾞｰﾀ
		std::uint8_t	Range;		//射程
		std::uint8_t	Heat;		//発熱量
		std::uint8_t	Ammo;		//弾薬消費量
		std::uint8_t	Energy;		//消費ﾊﾞｯﾃﾘｰ
	};

	struct ItemStat
	{
		std::uint16_t	ID;			//アイテムID(0は空欄)
		std::string	Name;		//アイテム名
		std::uint8_t	Amount;		//アイテムの数
		bool			IsEquipment;	//装備品であるか
	};

	virtual bool Wait();

	virtual bool Move();

	virtual bool Attack(aqua::CVector2 pos);

	virtual bool Item(std::int8_t slot, ITEM_USE_MODE mode = ITEM_USE_MODE::USE);

	virtual bool PlayEffect();

	void CalcEquipmentStat(int id);

	aqua::IGameObject* m_EffectManager;	//ｴﾌｪｸﾄﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_SoundManager;	//ｻｳﾝﾄﾞﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_UnitManager;	//ﾕﾆｯﾄﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_TextManager;	//ﾃｷｽﾄﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_UIManager;		//UIﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_EquipmentDB;	//装備品DBのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_ItemDataBase;	//ｱｲﾃﾑDBのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_UnitDataBase;	//ﾕﾆｯﾄDBのﾎﾟｲﾝﾀ

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

	std::uint8_t	m_Coverage;

	std::list<ItemStat> m_ItemList;

	std::uint8_t	m_WeaponCount;
	std::uint8_t	m_AttackingWPN;
	WeaponStat	m_Weapon[16];			//装備している武器
	std::uint16_t	m_Equipment[16];		//装備している装備品
	std::vector<uint16_t>	 m_Head;		//
	std::vector<uint16_t>	 m_Arm;		//
	std::vector<uint16_t>	 m_Hand;		//
	std::vector<uint16_t>	 m_Chest;	//
	std::vector<uint16_t>	 m_Back;		//
	std::vector<uint16_t>	 m_Leg;		//
	std::vector<uint16_t>	 m_Shlder;	//
	std::vector<uint16_t>	 m_Card;		//

	cMap* m_MapObj;
	IGameObject* m_Camera;
	int m_UnitNo;

	IGameObject* m_PlayingEffect;

	bool m_DidAction;
	ACTION m_DesiredAction;
	DIRECTION m_MoveTo;
	std::int8_t m_UseItemSlot;
	ITEM_USE_MODE m_ItemMode;
};