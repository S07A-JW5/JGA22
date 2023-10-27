#pragma once
#include "aqua.h"
#include "..\effect_id.h"

class IEffect :public aqua::IGameObject
{
public:

	//コンストラクタ
	IEffect(aqua::IGameObject* parent, std::string name);

	//デストラクタ
	~IEffect() = default;

	//初期化
	virtual void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	//更新
	virtual void Update() override;

	//描画
	virtual void Draw() override;

	//解放
	virtual void Finalize() override;

	//エフェクト再生中かどうか
	bool EffectPlaying();

protected:
	aqua::CVector2 m_PositionA;
	aqua::CVector2 m_PositionB;
	IGameObject* m_Camera;
	aqua::CLinePrimitive m_Line;
	float m_Timer;
};