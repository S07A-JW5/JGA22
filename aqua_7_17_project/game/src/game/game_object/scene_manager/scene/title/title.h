#pragma once

#include "aqua.h"
#include "..\scene.h"

class cTitleScene : public IScene
{
public:
	//コンストラクタ
	cTitleScene(aqua::IGameObject* parent);

	//デストラクタ
	~cTitleScene() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

private:
	aqua::CSprite m_Manual;	//操作説明

	aqua::IGameObject* m_SoundManager;	//サウンドマネージャのポインタ
	aqua::IGameObject* m_UIManager;		//UIマネージャのポインタ

	aqua::IGameObject* m_GameStartButton;	//「ゲームスタート」ボタン
	aqua::IGameObject* m_ManualOpenButton;	//「ゲーム説明」ボタン
	aqua::IGameObject* m_ManualCloseButton;	//「閉じる」ボタン
};