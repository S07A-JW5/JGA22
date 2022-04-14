#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum class EQUIPMENT_TYPE
	{
		DUMMY,	//��а
		WEAPON,	//����
		ARMOR,	//���b
		TRANSP,	//�ړ�
		UTIL,	//�����i
	};

	struct Equipment
	{
		std::int16_t EquipmentID; //�����iID(-1�ȉ��͋�)

		std::string Name; //�����i�̖��O

		EQUIPMENT_TYPE Type; //�����i�^�C�v

		std::uint16_t Durability;	//�����i�̑ϋv�l
		std::uint16_t AttatchPart;	//��t�ɕK�v�ȕ��i��
		std::uint8_t Weight;		//�������d��
		std::uint8_t Energy;		//�����ޯ�ذ
		std::uint8_t Heat;			//���M��

		//======================�J�����p======================
		std::uint8_t Range;	//���F�\����

		//======================����p========================
		IUnit::DAMAGE_TYPE DamageType;	//��Ұ�ޑ���
		std::uint8_t MinDamage;			//�ŏ��_���[�W
		std::uint8_t MaxDamage;			//�ő�_���[�W
		//   uint8_t Range;				//�˒�(0�̏ꍇ�A�ߐڍU������)(�J�����p�Ƌ��p�Ƃ���)
		std::uint8_t Ammo;				//�e������

		//======================���b�p========================
		std::int16_t  Resist[3];//�ϐ��l(%)
		std::int16_t  Protection;//�h���

		//======================�ړ��p========================
		std::uint8_t  Support;//�����d�ʏ��

		//======================���̑��p======================
		std::uint16_t BaseHeat;	//�M�����l������
		std::uint8_t  Inventory;//������ؗe�ʑ�����
		std::uint16_t MaxBatt;	//�ޯ�ذ�e�ʑ�����
		std::uint16_t MaxAmmo;	//�e�򏊎����������
		std::uint16_t MaxPart;	//���i�������������
	};

	cEquipDataBase(aqua::IGameObject* parent);

	~cEquipDataBase() = default;

	void Initialize() override;

	void Finalize() override;

	Equipment GetData(int id);

private:
	void Load();
	std::vector<Equipment> m_EquipmentDataList;
};