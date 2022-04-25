#pragma once
#include "aqua.h"

class cStatusUI :public aqua::IGameObject
{
public:
	cStatusUI(aqua::IGameObject* parent);

	~cStatusUI() = default;

	void Initialize(aqua::IGameObject* chr_obj, std::string name,
		std::uint16_t life, std::uint16_t maxLife,
		std::int16_t heatFlow, std::int16_t heat, std::int16_t baseHeat,
		std::uint16_t weight, std::uint16_t support,
		std::int16_t energyFlow, std::uint16_t batt, std::uint16_t maxBatt,
		std::uint16_t parts, std::uint16_t maxParts,
		std::uint16_t ammo, std::uint16_t maxAmmo,
		std::int16_t resist[3], std::int16_t protection);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetStat(std::string name, std::uint16_t maxLife,
		std::int16_t heatFlow, std::int16_t baseHeat,
		std::uint16_t weight, std::uint16_t support,
		std::int16_t energyFlow, std::uint16_t maxBatt,
		std::uint16_t maxParts, std::uint16_t maxAmmo,
		std::int16_t resist[3], std::int16_t protection);

private:
	std::string	m_Name;		//名前
	std::uint16_t	m_Life;		//現在耐久力
	std::uint16_t	m_MaxLife;	//最大耐久力
	std::int16_t	m_HeatFlow;	//発熱−冷却の総和
	std::int16_t	m_Heat;		//熱
	std::int16_t	m_BaseHeat;	//熱下限値
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

	aqua::CLabel	m_LifeText;
	aqua::CLabel	m_BattText;
	aqua::CLabel	m_AmmoText;
	aqua::CLabel	m_PartText;
	aqua::CLabel	m_HeatText;
	aqua::CLabel	m_ResistText;
	aqua::CLabel	m_ProtectionText;

	aqua::IGameObject* m_LifeGauge;
	aqua::IGameObject* m_BattGauge;
	aqua::IGameObject* m_AmmoGauge;
	aqua::IGameObject* m_PartGauge;

	aqua::IGameObject* m_Character;
};