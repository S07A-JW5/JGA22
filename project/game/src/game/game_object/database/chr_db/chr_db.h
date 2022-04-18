#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cUnitDataBase : public aqua::IGameObject
{
public:
	struct UnitData
	{
		std::string	TexFilePath;	//�摜�t�@�C���p�X
		std::string	Name;		//�L������

		std::uint16_t Life;		//�ϋv��
		std::uint16_t Cooling;		//��p�\��
		std::uint16_t Battery;		//�ޯ�ذ�e��
		std::uint16_t Parts;		//���i�������
		std::uint16_t Ammo;		//�e�򏊎����
		std::int16_t  Resist[3];	//�ϐ��l(%)
		std::uint8_t  Inventory;	//������ؗe��

		std::uint8_t ArmSlotCount;	//�u�r�v�ۯĐ�
		std::uint8_t ArmorCount;	//�u���b�v�ۯĐ�
		std::uint8_t TranspCount;	//�u�ړ��v�ۯĐ�
		std::uint8_t UtilCount;	//�u���̑��v�ۯĐ�

		std::uint16_t Equipped[20];	//�������Ă��鑕���iID
		std::uint16_t DropItemId[5];	//�h���b�v�A�C�e��ID
		std::uint8_t  DropRate[5];		//���Ƃ��m��(%)
	};

	cUnitDataBase(aqua::IGameObject* parent);

	~cUnitDataBase() = default;

	void Initialize() override;

	void Finalize() override;

	UnitData GetData(int id);

private:
	void Load();
	std::vector<UnitData> m_UnitDataList;
};