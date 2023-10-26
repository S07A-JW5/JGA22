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
		FIGHT_BACK,	//����(�U�������Ɖ��킷��)
		HOSTILE,		//�G
	};

	cBot(aqua::IGameObject* parent);

	~cBot() = default;

	void Initialize() override;

	void Update() override;

	bool Action() override;

private:
	void CameraUpdate();

	//bool Wait() override;

	bool Move() override;

	bool Attack(aqua::CVector2 pos) override;

	AI_TYPE m_AIType;		//���i
	bool m_TargetVision;	//�Ώۂ����F�o���Ă��邩
	aqua::CVector2 m_LastSeenTargetPos;	//�Ō�Ɏ��F�����ʒu
};