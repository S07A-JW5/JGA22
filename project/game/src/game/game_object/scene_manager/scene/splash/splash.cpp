#include "splash.h"

const float CSplashScene::m_wait_time = 1.0f;

//コンストラクタ
CSplashScene::CSplashScene(aqua::IGameObject* parent)
	:IScene(parent, "SplashScene")
{
}

//初期化
void CSplashScene::Initialize(void)
{
	//タイマー設定
	m_WaitTimer.Setup(m_wait_time);

	//ラベル生成
	m_Label.Create(50, 1);

	//m_Label.text = "スプラッシュ";
	m_Label.color = aqua::CColor::WHITE;
	m_Label.position.x = (aqua::GetWindowWidth() - m_Label.GetTextWidth()) / 2.0f;
	m_Label.position.y = (aqua::GetWindowHeight() - m_Label.GetFontHeight()) / 2.0f;

	//スプライト生成
	//m_Background.Create("data\\.png");
}

//更新
void CSplashScene::Update(void)
{
	Change(SCENE_ID::TITLE);
	return;

	//タイマー更新
	m_WaitTimer.Update();

	//設定した時間になったら
	if (m_WaitTimer.Finished())
	{
		//タイトルシーンに変更
		Change(SCENE_ID::TITLE);
	}
}

//描画
void CSplashScene::Draw(void)
{
	//背景描画
	//m_Background.Draw();

	//ラベル描画
	m_Label.Draw();
}

//解放
void CSplashScene::Finalize(void)
{
	//スプライトの解放
	//m_Background.Delete();

	//ラベル解放
	m_Label.Delete();
}
