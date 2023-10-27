#pragma once

#include "aqua.h"
#include "../unit.h"

class cBot :public IUnit
{
public:
	enum class AI_TYPE
	{
		ALLY	,		//����(�D��I)
		FRIENDRY,		//�F�D�I
		RUNAWAY,		//�v���C���[�����m�����擦���o��
		NEUTRAL_RUN,	//����(�U�������Ɠ�����)
		FIGHT_BACK,		//����(�U�������Ɖ��킷��)
		HOSTILE,		//�G
	};

	//�R���X�g���N�^
	cBot(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cBot() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�s��
	bool Action() override;

private:
	//�J�����X�V
	void CameraUpdate();

	//�ҋ@
	//bool Wait() override;

	//�ړ�
	bool Move() override;

	//�U��
	bool Attack(aqua::CVector2 pos) override;

	AI_TYPE m_AIType;		//���i
	bool m_TargetVision;	//�Ώۂ����F�o���Ă��邩
	aqua::CVector2 m_LastSeenTargetPos;	//�Ō�Ƀv���C���[�����F�����ʒu
};