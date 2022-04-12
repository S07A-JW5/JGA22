#pragma once
#include "aqua.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map_generator.h"

class IUnit : public aqua::IGameObject
{
public:
	enum DAMAGE_TYPE
	{
		KINETIC,
		THERMAL,
		ELECTRO,
	};

	IUnit(aqua::IGameObject* parent, std::string name);

	~IUnit() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	virtual void Create(std::string file_name);

	aqua::CVector2 GetPosition();

	void SetPosition(aqua::CVector2 pos);

	void GetMap(cMap* map);

protected:
	struct status
	{
		char		name[16];	//キャラ名

		std::uint16_t Life;		//基礎耐久力
		std::uint16_t Cooling;	//基礎冷却能力
		std::uint16_t Battery;	//基礎ﾊﾞｯﾃﾘｰ容量
		std::uint16_t Parts;	//基礎部品所持上限
		std::uint16_t Ammo;		//基礎弾薬所持上限
		std::int16_t  Resist[3];//基礎耐性値(%)
		std::uint8_t  Inventory;//基礎ｲﾝﾍﾞﾝﾄﾘ容量

		std::uint8_t CameraCount; //「ｶﾒﾗ」ｽﾛｯﾄ数
		std::uint8_t ArmSlotCount;//「腕」ｽﾛｯﾄ数
		std::uint8_t ArmorCount;  //「装甲」ｽﾛｯﾄ数
		std::uint8_t TranspCount; //「移動」ｽﾛｯﾄ数
		std::uint8_t UtilCount;   //「その他」ｽﾛｯﾄ数
	};

	aqua::IGameObject* m_SoundManager;	//ｻｳﾝﾄﾞﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_UnitManager;	//ﾕﾆｯﾄﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_TextManager;	//ﾃｷｽﾄﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ
	aqua::IGameObject* m_UIManager;		//UIﾏﾈｰｼﾞｬｰのﾎﾟｲﾝﾀ

	status m_Status;

	aqua::CVector2 m_OnMapPos;	//マップ上での位置
	aqua::CVector2 m_Position;	//ｽﾌﾟﾗｲﾄの位置
	aqua::CSprite m_Sprite;	//キャラスプライト

	std::uint16_t m_Life;		//現在耐久力
	std::uint16_t m_MaxLife;	//最大耐久力
	std::uint16_t m_Cooling;	//冷却能力
	std::int16_t  m_Heat;		//熱
	std::int16_t  m_BaseHeat;	//熱下限値
	std::uint8_t  m_Inventory;	//ｲﾝﾍﾞﾝﾄﾘ容量
	std::uint16_t m_Weight;	//装備重量
	std::uint16_t m_Support;	//装備重量上限(そうでもないけど)
	std::uint16_t m_Batt;		//ﾊﾞｯﾃﾘｰ残量
	std::uint16_t m_MaxBatt;	//ﾊﾞｯﾃﾘｰ容量
	std::uint16_t m_Parts;		//所持部品
	std::uint16_t m_MaxParts;	//部品所持上限
	std::uint16_t m_Ammo;		//所持弾薬
	std::uint16_t m_MaxAmmo;	//弾薬所持上限
	std::int16_t  m_Resist[3];	//耐性値(%)
	std::int16_t  m_DmgCut[3];	//ﾀﾞﾒｰｼﾞｶｯﾄ量

	std::vector<int16_t> m_Camera;	//装備しているカメラ
	std::vector<int16_t> m_Weapon;	//装備している武器
	std::vector<int16_t> m_Armor;	//装備している装甲
	std::vector<int16_t> m_Transp;	//装備している移動
	std::vector<int16_t> m_Util;	//装備している装備品

	cMap* m_MapObj;
	cCamera* m_CamObj;
};