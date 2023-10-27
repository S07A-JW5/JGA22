#pragma once
#pragma once

#include "aqua.h"
#include "../scene.h"

class cResultScene : public IScene
{
public:
	//コンストラクタ
	cResultScene(aqua::IGameObject* parent);

	//デストラクタ
	~cResultScene() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

private:
	IGameObject*	m_ResultText;		//リザルトテキスト
	IGameObject*	m_ReturnTitleButton;//「タイトルに戻る」ボタン
	aqua::CSprite	m_ResultSprite;		//リザルトスプライト
	bool			m_UIVisible;		//UI可視フラグ
};