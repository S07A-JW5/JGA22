#pragma once

#include "aqua.h"
#include "../unit.h"

class cBot :public IUnit
{
public:
	enum class AI_TYPE
	{
		FRIEND_AGGRO,	//����(�D��I)
		FRIENDRY,		//����
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
	bool Wait() override;

	//bool Move() override;

	bool Attack(aqua::CVector2 pos) override;

	AI_TYPE m_AIType;		//���i
	IUnit* m_Target;		//�U���Ώ�
	bool m_TargetVision;	//�Ώۂ����F�o���Ă��邩
	aqua::CVector2 m_LastSeenTargetPos;	//�Ō�Ɏ��F�����ʒu
};