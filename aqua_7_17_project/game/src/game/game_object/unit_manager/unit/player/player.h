#pragma once

#include "aqua.h"
#include "../unit.h"

class cPlayer :public IUnit
{
public:

	//�R���X�g���N�^
	cPlayer(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cPlayer() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�J�����X�V
	void CameraUpdate();

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//�K�i�̈ʒu�ݒ�
	void SetStairPosition(aqua::CVector2 pos);

	//�X�e�[�^�X�v�Z
	void CalcStatus(bool reset_param = false) override;

	//���S������
	void Dead() override;

	//�s��
	bool Action() override;

private:
	//�ҋ@
	bool Wait() override;

	//�ړ�
	bool Move() override;

	//�U��
	bool Attack(aqua::CVector2 pos) override;

	//�A�C�e�����g�p
	bool Item(std::int8_t slot) override;

	//�����ύX
	bool EquipmentChange(std::uint16_t id);

	aqua::CVector2 m_TargetTile; //�s���Ώۃ}�X

	aqua::CVector2 m_StairPos; //�K�i�ʒu

	aqua::CBoxPrimitive m_Box; //�Ώۃ}�X�\��

	aqua::IGameObject* m_StatObj; //�X�e�[�^�XUI�̃|�C���^
};