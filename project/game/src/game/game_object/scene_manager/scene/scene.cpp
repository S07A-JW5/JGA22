#include "scene.h"
#include"../scene_manager.h"

const std::string   IScene::m_scene_category = "Scene";


// コンストラクタ
IScene::IScene(aqua::IGameObject* parent, const
	std::string& object_name)
	:aqua::IGameObject(parent, object_name,m_scene_category)
{
}

// シーン変更
void IScene::Change(SCENE_ID id)
{
	// 親のシーンマネージャー呼び出し
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Change(id);
}

// シーンのスタック
void IScene::Push(SCENE_ID id)
{
	//親のシーンマネージャー呼び出し
	CSceneManager* sm = (CSceneManager*)GetParent();

	//シーンスタック
	sm->Push(id);

	//更新停止して描画のみ行う
	m_GameObjectState = aqua::GAME_OBJECT_STATE::WAIT;
}

// スタックシーン取り出し
void IScene::Pop(void)
{
	//親のシーンマネージャー呼び出し
	CSceneManager* sm = (CSceneManager*)GetParent();

	//スタックシーン取り出し
	sm->pop();
}

// シーンリセット
void IScene::Reset(void)
{
	// 親のシーンマネージャー呼び出し
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Reset();
}
