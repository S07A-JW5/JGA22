#pragma once
#include "aqua.h"
#include "effect_id.h"
#include "effect/effect.h"

class cEffectManager :public aqua::IGameObject
{
public:

	//コンストラクタ
	cEffectManager(aqua::IGameObject* parent);

	//デストラクタ
	~cEffectManager() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//エフェクト再生
	IEffect* CreateEffect(EFFECT_ID id, aqua::CVector2 posA, aqua::CVector2 posB);

private:
	IGameObject* m_SoundManager; //サウンドマネージャー
};