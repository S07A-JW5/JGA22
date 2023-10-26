#include"scene_manager.h"
#include"scene/scene.h"
#include"scene/game_main/game_main.h"
#include"scene/title/title.h"
#include"scene/result/result.h"
#include"scene/splash/splash.h"

const float CSceneManager::m_fade_speed = 255.0f;

// コンストラクタ
CSceneManager::
CSceneManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"SceneManager")
	, m_CurrentSceneID(SCENE_ID::DUMMY)
	, m_NextSceneID(SCENE_ID::DUMMY)
	, m_PushSceneID(SCENE_ID::DUMMY)
	, m_State(STATE::SCENE_IN)
	, m_PushFlag(false)

{
}

// 初期化
void CSceneManager::Initialize(void)
{
	m_FadeSprite.Create("data\\texture\\white.png");

	m_FadeSprite.color = aqua::CColor::BLACK;


	// スプラッシュシーンをはじめに生成
	Create(SCENE_ID::TITLE);

	// シーン状態を維持
	m_State = STATE::SCENE_IN;

	// プッシュフラグOFF
	m_PushFlag = false;

}

// 更新
void CSceneManager::Update(void)
{
	switch (m_State)
	{
	case STATE::SCENE_IN:		SceneIn();
		break;
	case STATE::SCENE_UPDATE:	SceneUpdate();
		break;
	case STATE::SCENE_OUT:		SceneOut();
		break;
	case STATE::SCENE_CHANGE:	SceneChange();
		break;
	}
}

 // 描画
void CSceneManager::Draw(void)
{
	IGameObject::Draw();

	m_FadeSprite.Draw();

}

// 解放
void CSceneManager::Finalize(void)
{
	IGameObject::Finalize();

	m_FadeSprite.Delete();
}

// シーンの変更
void CSceneManager::Change(SCENE_ID id)
{
	//次のシーンID
	m_NextSceneID = id;
}

// シーンスタック
void CSceneManager::Push(SCENE_ID id)
{
	//同フレームのプッシュ判定
	if (m_PushFlag || m_PushSceneID != SCENE_ID::DUMMY) return;

	//プッシュフラグON
	m_PushFlag = true;

	//スタックするシーンID保存
	m_PushSceneID = id;
}

// スタックシーン取り出し
void CSceneManager::pop(void)
{
	//子のシーンが1つならポップできない
	if (m_ChildObjectList.size() <= 1) return;

	//末尾のシーンのイテレータ取得
	aqua::GAME_OBJECT_LIST::reverse_iterator it = m_ChildObjectList.rbegin();

	//シーンクラスにキャスト
	IScene* scene = (IScene*)(*it);

	//末尾のシーンを削除対象にする
	scene->DeleteObject();

	//ひとつ前のシーン取得
	scene = (IScene*)(*(++it));

	//ひとつ前のシーンをアクティブ状態にする
	scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
}

// リセット
void CSceneManager::Reset(void)
{
	m_NextSceneID = m_CurrentSceneID;

	m_CurrentSceneID = SCENE_ID::DUMMY;
}

// シーンの生成
void CSceneManager::Create(SCENE_ID id)
{
	IScene* scene = nullptr;

	//idごとに新たなシーン生成
	switch (id)
	{
	case SCENE_ID::SPLASH:		scene = aqua::CreateGameObject<CSplashScene>(this);	break;
	case SCENE_ID::TITLE:		scene = aqua::CreateGameObject<CTitleScene>(this);	break;
	case SCENE_ID::GAMEMAIN:	scene = aqua::CreateGameObject<CGameMainScene>(this);	break;
	//case SCENE_ID::MENU:		scene = aqua::CreateGameObject<CMenuScene>(this);		break;
	case SCENE_ID::RESULT:		scene = aqua::CreateGameObject<CResultScene>(this);	break;
	}

	AQUA_ASSERT(scene, "シーンが生成できませんでした。");

	//シーンを初期化
	scene->Initialize();
}

// シーン削除
void CSceneManager::Delete(void)
{
	IGameObject::Finalize();
}

// シーン開始
void CSceneManager::SceneIn(void)
{
	float alpha = (float)m_FadeSprite.color.alpha;

	alpha -= m_fade_speed * aqua::GetDeltaTime();

	if (alpha < 0.0f)
	{
		alpha = 0.0f;

		m_State = STATE::SCENE_UPDATE;
	}

	m_FadeSprite.color.alpha = (unsigned char)alpha;
}

// シーン更新
void CSceneManager::SceneUpdate(void)
{
	//プッシュ処理しているかの判定
	if (m_PushFlag)
	{
		//新たなシーンを生成してスタック
		Create(m_PushSceneID);

		//未使用時はダミーIDを入れる
		m_PushSceneID = SCENE_ID::DUMMY;

		//シーンのプッシュが終了
		m_PushFlag = false;
	}

	IGameObject::Update();

	//シーン変更の検知
	if (m_CurrentSceneID != m_NextSceneID)
		m_State = STATE::SCENE_OUT;
}
// シーン終了
void CSceneManager::SceneOut(void)
{
	float alpha = (float)m_FadeSprite.color.alpha;

	alpha += m_fade_speed * aqua::GetDeltaTime();

	if (alpha > (float)aqua::CColor::MAX_COLOR)
	{
		alpha = (float)aqua::CColor::MAX_COLOR;

		m_State = STATE::SCENE_CHANGE;
	}

	m_FadeSprite.color.alpha = (unsigned char)alpha;
}

// シーン変更
void CSceneManager::SceneChange(void)
{
	//現在シーン削除
	Delete();

	//次のシーン生成
	Create(m_NextSceneID);

	//シーンIDを保存
	m_CurrentSceneID = m_NextSceneID;

	//状態を移行
	m_State = STATE::SCENE_IN;
}
