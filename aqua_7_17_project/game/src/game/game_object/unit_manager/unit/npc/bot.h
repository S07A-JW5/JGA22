#pragma once

#include "aqua.h"
#include "../unit.h"

class cBot :public IUnit
{
public:
	enum class AI_TYPE
	{
		ALLY	,		//味方(好戦的)
		FRIENDRY,		//友好的
		RUNAWAY,		//プレイヤーを感知し次第逃げ出す
		NEUTRAL_RUN,	//中立(攻撃されると逃げる)
		FIGHT_BACK,		//中立(攻撃されると応戦する)
		HOSTILE,		//敵
	};

	//コンストラクタ
	cBot(aqua::IGameObject* parent);

	//デストラクタ
	~cBot() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//行動
	bool Action() override;

private:
	//カメラ更新
	void CameraUpdate();

	//待機
	//bool Wait() override;

	//移動
	bool Move() override;

	//攻撃
	bool Attack(aqua::CVector2 pos) override;

	AI_TYPE m_AIType;		//性格
	bool m_TargetVision;	//対象を視認出来ているか
	aqua::CVector2 m_LastSeenTargetPos;	//最後にプレイヤーを視認した位置
};