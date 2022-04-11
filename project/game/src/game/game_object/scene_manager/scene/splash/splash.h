#pragma once

#include "aqua.h"
#include "..\scene.h"

class CSplashScene : public IScene
{
public:
	//コンストラクタ
	CSplashScene(aqua::IGameObject* parent);

	//デストラクタ
	~CSplashScene(void) = default;

	//初期化
	void Initialize(void) override;

	//更新
	void Update(void) override;

	//描画
	void Draw(void) override;

	//解放
	void Finalize(void) override;

private:
	static const float		m_wait_time;			//待機時間
	aqua::CTimer			m_WaitTimer;			//タイマー
	aqua::CLabel			m_Label;				//ラベル
	aqua::CSprite			m_Background;			//背景
};