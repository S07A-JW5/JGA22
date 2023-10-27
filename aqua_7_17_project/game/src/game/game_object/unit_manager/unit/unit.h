#pragma once
#include "aqua.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"
#include "game/tools/tools.h"

class IUnit : public aqua::IGameObject
{
public:
	enum class DAMAGE_TYPE
	{
		DUMMY,		//ダミー
		KINETIC,	//物理
		THERMAL,	//熱
		ELECTRO,	//電気
	};

	enum class DIRECTION
	{
		NORTH,	//上
		SOUTH,	//下
		EAST,	//右
		WEST,	//左

		NORTH_EAST,//右上
		NORTH_WEST,//左上
		SOUTH_EAST,//右下
		SOUTH_WEST,//左下

		COUNT,
		DUMMY = 0xff
	};

	enum class STATUS
	{
		LIFE,	//体力
		HEAT,	//熱
		BATT,	//電力（バッテリー）
		PARTS,	//部品
		AMMO,	//弾薬
	};

	struct EquippedStat
	{
		std::string	Equipment[16];	//装備品名
		uint8_t		Count;			//装備スロット数
	};

	struct InventoryStat
	{
		std::string	Item[16];	//アイテム名
		uint8_t		Count;		//インベントリ容量
	};

	//コンストラクタ
	IUnit(aqua::IGameObject* parent, std::string name);

	//デストラクタ
	~IUnit() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	/*!
	 *	@brief	キャラ生成
	 *
	 *	@param[in]	id		キャラDBから読み込むID
	 *	@param[in]	unit_no	ユニット番号
	 */
	void Create(int id, int unit_no);

	/*!
	 *	@brief	ステータス計算
	 *
	 *	@param[in]	reset_param	現在値をリセットするか
	 */
	virtual void CalcStatus(bool reset_param = false);

	//現在位置取得
	aqua::CVector2 GetPosition();

	//位置設定
	void SetPosition(aqua::CVector2 pos);

	//マップオブジェクト設定
	void SetMapObj(cMap* map);

	//ダメージを受ける
	bool TakeDamage(int damage, IUnit::DAMAGE_TYPE type);

	//行動済みかを確認
	bool DidAction();

	//行動済みフラグを設定
	void SetActFlag(bool flag);

	//ステータス値取得
	int GetStatus(IUnit::STATUS stat);

	//装備品内容取得
	EquippedStat GetEquipped();

	//インベントリ内容取得
	InventoryStat GetInventory();

	//耐久力が0になった時の処理
	virtual void Dead();

	//行動
	virtual bool Action();

protected:
	enum class ACTION
	{
		DUMMY,
		WAIT,	//待機
		MOVE,	//移動
		ATTACK,	//攻撃
		ITEM,	//ｱｲﾃﾑ使用
	};

	enum class ITEM_USE_MODE
	{
		DUMMY,
		USE,		//消費
		DISCARD,	//破棄（その場に落とす）
		SWITCH,		//入替（一番後ろに移動）
	};

	struct status
	{
		uint16_t ID;		//ユニットID
		uint16_t Life;		//基礎耐久力
		uint16_t Cooling;	//基礎冷却能力
		uint16_t Battery;	//基礎電力容量
		uint16_t Parts;		//基礎部品所持上限
		uint16_t Ammo;		//基礎弾薬所持上限
		int16_t  Resist[3];	//基礎耐性値(%)
		uint8_t  Inventory;	//基礎インベントリ容量

		uint8_t HeadCount;	//「頭」スロット数
		uint8_t ArmCount;	//「腕」スロット数
		uint8_t ChestCount;	//「胸部」スロット数
		uint8_t BackCount;	//「背中」スロット数
		uint8_t LegCount;	//「脚」スロット数
		uint8_t ShlderCount;//「肩」スロット数
		uint8_t CardCount;	//「拡張」スロット数
		uint8_t EquipCount;	//総装備スロット数
	};

	struct WeaponStat
	{
		uint16_t	ID;			//装備品ID(0は空欄)
		std::string	Name;		//装備品の名前
		DAMAGE_TYPE	DamageType;	//ダメージ属性
		Dice::DiceRollData DmgRollData;//ダメージロールデータ
		uint8_t		EffectID;	//攻撃エフェクトID
		uint8_t		Range;		//射程
		uint8_t		Heat;		//発熱量
		uint8_t		Ammo;		//弾薬消費量
		uint8_t		Energy;		//消費電力
	};

	struct ItemStat
	{
		uint16_t	ID;		//アイテムID(0は空欄)
		std::string	Name;	//アイテム名
		uint8_t		Amount;	//アイテムの数
		bool		IsEquipment;	//装備品であるか
	};

	//待機
	virtual bool Wait();

	//移動
	virtual bool Move();

	//攻撃
	virtual bool Attack(aqua::CVector2 pos);

	//アイテム使用
	virtual bool Item(std::int8_t slot);

	//エフェクト再生中か調べる
	virtual bool EffectPlaying();

	//移動可能か調べる
	bool CanMove();

	//移動後の位置取得
	aqua::CVector2 GetMovedPos();

	//装備品の能力をステータスに加算
	void CalcEquipmentStat(int id);

	IGameObject* m_EffectManager;	//エフェクトマネージャのポインタ
	IGameObject* m_SoundManager;	//サウンドマネージャのポインタ
	IGameObject* m_UnitManager;		//ユニットマネージャのポインタ
	IGameObject* m_TextManager;		//テキストマネージャのポインタ
	IGameObject* m_UIManager;		//UIマネージャのポインタ
	IGameObject* m_EquipmentDB;		//装備品DBのポインタ
	IGameObject* m_ItemDataBase;	//アイテムDBのポインタ
	IGameObject* m_UnitDataBase;	//ユニットDBのポインタ

	status m_Status;	//ステータス

	aqua::CVector2 m_OnMapPos;	//マップ上での位置
	aqua::CVector2 m_Position;	//スプライト位置
	aqua::CSprite m_Sprite;		//キャラスプライト

	std::string	m_Name;			//名前
	uint16_t	m_Life;			//現在耐久力
	uint16_t	m_MaxLife;		//最大耐久力
	int16_t		m_HeatFlow;		//発熱－冷却の総和
	int16_t		m_Heat;			//熱
	int16_t		m_BaseHeat;		//熱下限値
	uint8_t		m_Inventory;	//インベントリ容量
	uint16_t	m_Weight;		//装備重量
	uint16_t	m_Support;		//装備重量上限
	int16_t		m_EnergyFlow;	//電力の流出入量
	uint16_t	m_Batt;			//電力残量
	uint16_t	m_MaxBatt;		//電力容量
	uint16_t	m_Parts;		//所持部品
	uint16_t	m_MaxParts;		//部品所持上限
	uint16_t	m_Ammo;			//所持弾薬
	uint16_t	m_MaxAmmo;		//弾薬所持上限
	int16_t		m_Resist[3];	//耐性値(%)
	int16_t		m_Protection;	//防御力
	uint8_t		m_SightRange;	//視界半径

	std::list<ItemStat> m_ItemList;	//所持品

	uint8_t			m_WeaponCount;		//装備している武器の数
	uint8_t			m_AttackingWPN;		//現在攻撃している武器
	WeaponStat		m_Weapon[16];		//装備している武器
	uint16_t		m_Equipment[16];	//装備している装備品
	std::vector<uint16_t>	 m_Head;	//頭装備
	std::vector<uint16_t>	 m_Arm;		//ウデ装備
	std::vector<uint16_t>	 m_Chest;	//胸部装備
	std::vector<uint16_t>	 m_Back;	//背中装備
	std::vector<uint16_t>	 m_Leg;		//脚装備
	std::vector<uint16_t>	 m_Shlder;	//肩装備
	std::vector<uint16_t>	 m_Card;	//拡張装備

	cMap*			m_MapObj;	//マップ
	IGameObject*	m_Camera;	//カメラ
	int				m_UnitNo;	//ユニット番号（生成順連番）

	IGameObject* m_PlayingEffect;	//再生中の攻撃エフェクト

	bool m_DidAction;			//行動済みフラグ
	ACTION m_DesiredAction;	//行う予定の行動
	DIRECTION m_MoveTo;		//移動方向
	std::int8_t m_UseItemSlot;	//これから使うアイテムスロット番号
	ITEM_USE_MODE m_ItemMode;	//アイテム使用モード
};
