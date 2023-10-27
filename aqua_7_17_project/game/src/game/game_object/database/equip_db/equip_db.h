#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cEquipDataBase : public aqua::IGameObject
{
public:
	enum class EQUIPMENT_TYPE
	{
		DUMMY,		//��а
		WEAPON,		//����
		ARMOR,		//���b
		SUPPORT,	//�⏕
		UTIL,		//�����i
	};

	enum class EQUIPMENT_SLOT
	{
		DUMMY,		//��а
		HEAD,		//��
		ARM,		//�r
		CHEST,		//����
		BACK,		//�w��
		LEG,		//�r
		SHOULDER,	//��
		CARD,		//�g�����޽ۯ�
	};

	struct Equipment
	{
		uint16_t EquipmentID;	//�����iID(0�͋�)

		std::string Name;		//�����i�̖��O
		std::string Description;//������

		EQUIPMENT_TYPE Type;	//�����i�^�C�v
		EQUIPMENT_SLOT Slot;	//�����\����

		uint16_t	Durability;	//�����i�̑ϋv�l
		uint16_t	AttatchPart;//��t�ɕK�v�ȕ��i��
		uint8_t		Weight;		//�������d��
		uint8_t		Energy;		//�����ޯ�ذ
		uint8_t		Heat;		//���M��

		//======================����p========================
		//					Range;		//�˒�(0�̏ꍇ�A�ߐڍU������)
		IUnit::DAMAGE_TYPE	DamageType;	//��Ұ�ޑ���
		Dice::DiceRollData	DmgRollData;//��Ұ��۰��ް�
		uint8_t				EffectID;	//�U���G�t�F�N�gID
		uint8_t				Ammo;		//�e������

		//======================���b�p========================
		int16_t	Resist[3];	//�ϐ��l(%)
		int16_t	Protection;	//�h���

		//======================�ړ��p========================
		std::uint8_t  Support;		//�����d�ʏ��

		//======================���̑��p======================
		uint8_t		Power;		//�d�͋�����
		uint8_t		Range;		//���F�\����
		uint8_t		Cooling;	//��p�\��
		int16_t		BaseHeat;	//�M�����l������
		uint8_t		Inventory;	//������ؗe�ʑ�����
		uint16_t	MaxBatt;	//�ޯ�ذ�e�ʑ�����
		uint16_t	MaxAmmo;	//�e�򏊎����������
		uint16_t	MaxPart;	//���i�������������
	};

	//�R���X�g���N�^
	cEquipDataBase(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cEquipDataBase() = default;

	//������
	void Initialize() override;

	//���
	void Finalize() override;

	//�����i�f�[�^�擾
	Equipment GetData(int id);

private:
	//�����i�f�[�^�Ǎ�
	void Load();

	std::vector<Equipment> m_EquipmentDataList;
};