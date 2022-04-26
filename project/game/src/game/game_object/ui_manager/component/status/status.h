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
	std::string	m_Name;		//–¼‘O
	std::uint16_t	m_Life;		//Œ»İ‘Ï‹v—Í
	std::uint16_t	m_MaxLife;	//Å‘å‘Ï‹v—Í
	std::int16_t	m_HeatFlow;	//”­”M|—â‹p‚Ì‘˜a
	std::int16_t	m_Heat;		//”M
	std::int16_t	m_BaseHeat;	//”M‰ºŒÀ’l
	std::uint16_t	m_Weight;		//‘•”õd—Ê
	std::uint16_t	m_Support;	//‘•”õd—ÊãŒÀ(‚»‚¤‚Å‚à‚È‚¢‚¯‚Ç)
	std::int16_t	m_EnergyFlow;	//“d—Í‚Ì—¬o“ü—Ê
	std::uint16_t	m_Batt;		//ÊŞ¯ÃØ°c—Ê
	std::uint16_t	m_MaxBatt;	//ÊŞ¯ÃØ°—e—Ê
	std::uint16_t	m_Parts;		//Š•”•i
	std::uint16_t	m_MaxParts;	//•”•iŠãŒÀ
	std::uint16_t	m_Ammo;		//Š’e–ò
	std::uint16_t	m_MaxAmmo;	//’e–òŠãŒÀ
	std::int16_t	m_Resist[3];	//‘Ï«’l(%)
	std::int16_t	m_Protection;	//–hŒä—Í

	aqua::CLabel	m_LifeText;
	aqua::CLabel	m_BattText;
	aqua::CLabel	m_AmmoText;
	aqua::CLabel	m_PartText;
	aqua::CLabel	m_HeatText;
	aqua::CLabel	m_ResistText;
	aqua::CLabel	m_ProtectionText;
	aqua::CLabel	m_EquipmentText[17];

	aqua::IGameObject* m_LifeGauge;
	aqua::IGameObject* m_BattGauge;
	aqua::IGameObject* m_AmmoGauge;
	aqua::IGameObject* m_PartGauge;

	aqua::IGameObject* m_Character;
};