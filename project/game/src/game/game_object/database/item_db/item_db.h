#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"
#include "game/tools/tools.h"

class cItemDataBase : public aqua::IGameObject
{
public:
	enum class ITEM_TYPE
	{
		DUMMY,		//��а
		ITEM,		//�A�C�e��
		CONSUMABLE,	//�g�p�\
		INSTANT,		//�E�����u�ԏ�����
		EQUIPMENT,	//�����i
	};

	enum class CONSUME_TYPE
	{
		DUMMY,	//��а
		SELF,	//�������g
		ENEMY,	//�G
		THROW,	//������
	};

	struct ItemData
	{
		std::uint16_t ItemID; //�A�C�e��ID(0�͋�)

		std::string Name;			//�A�C�e����
		std::string Description;	//������

		ITEM_TYPE		Type;	//�A�C�e���^�C�v
		CONSUME_TYPE	Consume;	//���Օi�^�C�v
		std::int16_t	Life;	//�g�p��HP�񕜗�
		std::int16_t	Energy;	//�g�p���ޯ�ذ�񕜗�
		std::int16_t	Ammo;	//�g�p���e��⋋��
		std::int16_t	Cooling;	//�g�p����p��

		IUnit::DAMAGE_TYPE DamageType;	//��Ұ�ޑ���
		Dice::DiceRollData DmgRollData;	//��Ұ��۰��ް�
		std::uint8_t Range;			//�˒�(0�̏ꍇ�A�ߐڍU��)
	};

	cItemDataBase(aqua::IGameObject* parent);

	~cItemDataBase() = default;

	void Initialize() override;

	void Finalize() override;

	ItemData GetData(int id);

private:
	void Load();
	std::vector<ItemData> m_ItemDataList;
};