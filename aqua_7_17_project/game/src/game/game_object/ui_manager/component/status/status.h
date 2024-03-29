#pragma once
#include "aqua.h"

class cStatusUI :public aqua::IGameObject
{
public:

	//RXgN^
	cStatusUI(aqua::IGameObject* parent);

	//fXgN^
	~cStatusUI() = default;

	//ϊ»
	void Initialize(IGameObject* chr_obj, std::string name,
		uint16_t life, uint16_t maxLife, int16_t heatFlow, int16_t heat,
		int16_t energyFlow, uint16_t batt, uint16_t maxBatt,
		uint16_t parts, uint16_t maxParts, uint16_t ammo, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

	//XV
	void Update() override;

	//`ζ
	void Draw() override;

	//πϊ
	void Finalize() override;

	void SetStat(std::string name, uint16_t maxLife, int16_t heatFlow, 
		int16_t energyFlow,uint16_t maxBatt, uint16_t maxParts, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

private:
	std::string	m_Name;		//ΌO
	uint16_t	m_Life;		//»έΟvΝ
	uint16_t	m_MaxLife;	//ΕεΟvΝ
	int16_t		m_HeatFlow;	//­M|βpΜa
	int16_t		m_Heat;		//M
	int16_t		m_EnergyFlow;	//dΝΜ¬oόΚ
	uint16_t	m_Batt;			//Κή―ΓΨ°cΚ
	uint16_t	m_MaxBatt;		//Κή―ΓΨ°eΚ
	uint16_t	m_Parts;		//i
	uint16_t	m_MaxParts;		//iγΐ
	uint16_t	m_Ammo;			//eς
	uint16_t	m_MaxAmmo;		//eςγΐ
	int16_t		m_Resist[3];	//Ο«l(%)
	int16_t		m_Protection;	//hδΝ

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