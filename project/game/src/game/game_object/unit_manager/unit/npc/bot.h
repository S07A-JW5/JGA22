#pragma once

#include "aqua.h"
#include "../unit.h"

class cBot :public IUnit
{
public:
	enum class AI_TYPE
	{
		FRIEND_AGGRO,	//味方(好戦的)
		FRIENDRY,		//味方
		RUNAWAY,		//プレイヤーを感知し次第逃げ出す
		NEUTRAL_RUN,	//中立(攻撃されると逃げる)
		FIGHT_BACK,	//中立(攻撃されると応戦する)
		HOSTILE,		//敵
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

	AI_TYPE m_AIType;		//性格
	IUnit* m_Target;		//攻撃対象
	bool m_TargetVision;	//対象を視認出来ているか
	aqua::CVector2 m_LastSeenTargetPos;	//最後に視認した位置
};