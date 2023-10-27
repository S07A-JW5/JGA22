#pragma once
#include "aqua.h"

class cStatusUI :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cStatusUI(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cStatusUI() = default;

	//������
	void Initialize(IGameObject* chr_obj, std::string name,
		uint16_t life, uint16_t maxLife, int16_t heatFlow, int16_t heat,
		int16_t energyFlow, uint16_t batt, uint16_t maxBatt,
		uint16_t parts, uint16_t maxParts, uint16_t ammo, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	void SetStat(std::string name, uint16_t maxLife, int16_t heatFlow, 
		int16_t energyFlow,uint16_t maxBatt, uint16_t maxParts, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

private:
	std::string	m_Name;		//���O
	uint16_t	m_Life;		//���ݑϋv��
	uint16_t	m_MaxLife;	//�ő�ϋv��
	int16_t		m_HeatFlow;	//���M�|��p�̑��a
	int16_t		m_Heat;		//�M
	int16_t		m_EnergyFlow;	//�d�̗͂��o����
	uint16_t	m_Batt;			//�ޯ�ذ�c��
	uint16_t	m_MaxBatt;		//�ޯ�ذ�e��
	uint16_t	m_Parts;		//�������i
	uint16_t	m_MaxParts;		//���i�������
	uint16_t	m_Ammo;			//�����e��
	uint16_t	m_MaxAmmo;		//�e�򏊎����
	int16_t		m_Resist[3];	//�ϐ��l(%)
	int16_t		m_Protection;	//�h���

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