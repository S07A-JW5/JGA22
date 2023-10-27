#pragma once
#include "aqua.h"
#include "../../unit_manager/unit/unit.h"

class cUnitDataBase : public aqua::IGameObject
{
public:
	struct UnitData
	{
		std::string	TexFilePath;//�摜�t�@�C���p�X
		std::string	Name;		//�L������

		uint16_t Life;		//�ϋv��
		uint16_t Cooling;	//��p�\��
		uint16_t Battery;	//�ޯ�ذ�e��
		uint16_t Parts;		//���i�������
		uint16_t Ammo;		//�e�򏊎����
		int16_t  Resist[3];	//�ϐ��l(%)
		uint8_t  Inventory;	//������ؗe��

		uint8_t HeadCount;	//�u���v�ۯĐ�
		uint8_t ArmCount;	//�u�r�v�ۯĐ�
		uint8_t ChestCount;	//�u�����v�ۯĐ�
		uint8_t BackCount;	//�u�w���v�ۯĐ�
		uint8_t LegCount;	//�u�r�v�ۯĐ�
		uint8_t ShlderCount;//�u���v�ۯĐ�
		uint8_t CardCount;	//�u�g�����ށv�ۯĐ�

		uint16_t Equipped[16];	//�������Ă��鑕���iID
		uint16_t DropItemId[4];	//�h���b�v�A�C�e��ID
		uint8_t  DropRate[4];	//���Ƃ��m��(%)
	};

	//�R���X�g���N�^
	cUnitDataBase(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cUnitDataBase() = default;

	//������
	void Initialize() override;

	//���
	void Finalize() override;

	//�L�����f�[�^�擾
	UnitData GetData(int id);

private:
	//�L�����f�[�^�Ǎ�
	void Load();

	std::vector<UnitData> m_UnitDataList;
};