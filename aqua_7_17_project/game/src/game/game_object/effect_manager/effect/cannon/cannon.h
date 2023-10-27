#pragma once
#include "../effect.h"

class cEffectCannon :public IEffect
{
public:

	//コンストラクタ
	cEffectCannon(aqua::IGameObject* parent);

	//デストラクタ
	~cEffectCannon() = default;

	//初期化
	void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

private:
	aqua::CBoxPrimitive m_Box;
	aqua::CVector2 m_Velocity;
	aqua::CVector2 m_BoxPos;
	aqua::CVector2 m_PrevPos;
};