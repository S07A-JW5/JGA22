#pragma once

#include "aqua.h"
#include "..\scene.h"

class CTitleScene
	:public IScene
{
public:

	//コンストラクタ
	CTitleScene(aqua::IGameObject* parent);

	//デストラクタ
	~CTitleScene(void) = default;

	//初期化
	void Initialize(void) override;

	//更新
	void Update(void) override;

	//描画
	void Draw(void) override;

	//解放
	void Finalize(void) override;

private:
	aqua::CLabel m_Label;
	aqua::CLabel m_Text;

	aqua::IGameObject* m_SoundManager;
};