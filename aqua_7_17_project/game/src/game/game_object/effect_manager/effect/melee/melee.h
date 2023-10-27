#pragma once
#include "../effect.h"

class cEffectMelee :public IEffect
{
public:

	//コンストラクタ
	cEffectMelee(aqua::IGameObject* parent);

	//デストラクタ
	~cEffectMelee() = default;

	//初期化
	void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

private:
};