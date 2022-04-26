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
	std::string	m_Name;		//���O
	std::uint16_t	m_Life;		//���ݑϋv��
	std::uint16_t	m_MaxLife;	//�ő�ϋv��
	std::int16_t	m_HeatFlow;	//���M�|��p�̑��a
	std::int16_t	m_Heat;		//�M
	std::int16_t	m_BaseHeat;	//�M�����l
	std::uint16_t	m_Weight;		//�����d��
	std::uint16_t	m_Support;	//�����d�ʏ��(�����ł��Ȃ�����)
	std::int16_t	m_EnergyFlow;	//�d�̗͂��o����
	std::uint16_t	m_Batt;		//�ޯ�ذ�c��
	std::uint16_t	m_MaxBatt;	//�ޯ�ذ�e��
	std::uint16_t	m_Parts;		//�������i
	std::uint16_t	m_MaxParts;	//���i�������
	std::uint16_t	m_Ammo;		//�����e��
	std::uint16_t	m_MaxAmmo;	//�e�򏊎����
	std::int16_t	m_Resist[3];	//�ϐ��l(%)
	std::int16_t	m_Protection;	//�h���

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