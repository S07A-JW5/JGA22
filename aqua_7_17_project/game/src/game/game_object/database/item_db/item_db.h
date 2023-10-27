#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cItemDataBase : public aqua::IGameObject
{
public:
	enum class ITEM_TYPE
	{
		DUMMY,		//�_�~�[
		ITEM,		//�A�C�e��
		CONSUMABLE,	//�g�p�\
		INSTANT,	//�E�����u�ԏ�����
		EQUIPMENT,	//�����i
	};

	enum class CONSUME_TYPE
	{
		NOT_CONSUMABLE,	//�g�����Ƃ̏o���Ȃ��A�C�e��
		SELF,	//�������g
		ENEMY,	//�G
		THROW,	//������
	};

	enum class MATERIALS
	{
		DUMMY,	//�_�~�[
		AMMO,	//�e��
		PARTS,	//���i
		ENERGY,	//�d��(�o�b�e���[)

		COUNT
	};


	struct ItemData
	{
		uint16_t ItemID; //�A�C�e��ID(0�͋�)

		std::string Name;			//�A�C�e����
		std::string Description;	//������

		ITEM_TYPE		Type;		//�A�C�e���^�C�v
		CONSUME_TYPE	Consume;	//���Օi�^�C�v
		int16_t			Life;		//�g�p��HP�񕜗�
		int16_t			Energy;		//�g�p���d�͕⋋��
		int16_t			Parts;		//�g�p�����i�⋋��
		int16_t			Ammo;		//�g�p���e��⋋��
		int16_t			Cooling;	//�g�p����p��

		IUnit::DAMAGE_TYPE	DamageType;		//�_���[�W����
		Dice::DiceRollData	DmgRollData;	//�_���[�W���[���f�[�^
		uint8_t				Range;			//�˒�(0�̏ꍇ�A�ߐڍU��)
	};

	//�R���X�g���N�^
	cItemDataBase(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cItemDataBase() = default;

	//������
	void Initialize() override;

	//���
	void Finalize() override;

	//�����iID���A�C�e��ID�ɕϊ�
	uint16_t EquipmentItem(int id);

	//�A�C�e���f�[�^�擾
	ItemData GetData(int id, bool equipment = false);

private:
	//�A�C�e���f�[�^�Ǎ�
	void Load();

	std::vector<ItemData> m_ItemDataList;

	int m_ItemCount; //�A�C�e���̌�
};