#pragma once
#pragma once

#include "aqua.h"
#include "../scene.h"

class CResultScene : public IScene
{
public:
	//コンストラクタ
	CResultScene(aqua::IGameObject* parent);

	//デストラクタ
	~CResultScene(void) = default;

	//初期化
	void Initialize(void) override;

	//更新
	void Update(void) override;

	//描画
	void Draw(void) override;

	//解放
	void Finalize(void) override;

private:
	aqua::IGameObject*	 m_ResultText;		//
	aqua::IGameObject*	 m_ReturnTitleButton;	//
	aqua::CSprite		 m_ResultSprite;		//リザルトスプライト
	bool				 m_UIVisible;
};