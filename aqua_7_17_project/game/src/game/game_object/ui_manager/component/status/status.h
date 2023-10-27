#pragma once
#include "aqua.h"

class cStatusUI :public aqua::IGameObject
{
public:

	//コンストラクタ
	cStatusUI(aqua::IGameObject* parent);

	//デストラクタ
	~cStatusUI() = default;

	//初期化
	void Initialize(IGameObject* chr_obj, std::string name,
		uint16_t life, uint16_t maxLife, int16_t heatFlow, int16_t heat,
		int16_t energyFlow, uint16_t batt, uint16_t maxBatt,
		uint16_t parts, uint16_t maxParts, uint16_t ammo, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	void SetStat(std::string name, uint16_t maxLife, int16_t heatFlow, 
		int16_t energyFlow,uint16_t maxBatt, uint16_t maxParts, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

private:
	std::string	m_Name;		//名前
	uint16_t	m_Life;		//現在耐久力
	uint16_t	m_MaxLife;	//最大耐久力
	int16_t		m_HeatFlow;	//発熱－冷却の総和
	int16_t		m_Heat;		//熱
	int16_t		m_EnergyFlow;	//電力の流出入量
	uint16_t	m_Batt;			//ﾊﾞｯﾃﾘｰ残量
	uint16_t	m_MaxBatt;		//ﾊﾞｯﾃﾘｰ容量
	uint16_t	m_Parts;		//所持部品
	uint16_t	m_MaxParts;		//部品所持上限
	uint16_t	m_Ammo;			//所持弾薬
	uint16_t	m_MaxAmmo;		//弾薬所持上限
	int16_t		m_Resist[3];	//耐性値(%)
	int16_t		m_Protection;	//防御力

	aqua::CLabel m_LifeText;
	aqua::CLabel m_BattText;
	aqua::CLabel m_AmmoText;
	aqua::CLabel m_PartText;
	aqua::CLabel m_HeatText;
	aqua::CLabel m_ResistText;
	aqua::CLabel m_ProtectionText;
	aqua::CLabel m_EquipmentText[17];
	aqua::CLabel m_InventoryText[5];

	IGameObject* m_LifeGauge;
	IGameObject* m_BattGauge;
	IGameObject* m_AmmoGauge;
	IGameObject* m_PartGauge;

	IGameObject* m_Character;
};