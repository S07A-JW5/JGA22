#pragma once

#include"aqua.h"
#pragma once

#include "aqua.h"
#include "scene\scene_id.h"

class CSceneManager
	: public aqua::IGameObject
{
public:

	//コンストラクタ
	CSceneManager(aqua::IGameObject* parent);

	//デストラクタ
	~CSceneManager(void) = default;

	//初期化
	void Initialize(void) override;

	//更新
	void Update(void) override;

	//描画
	void Draw(void) override;

	//解放
	void Finalize(void) override;

	//シーン変更
	void Change(SCENE_ID id);

	//シーンスタック
	void Push(SCENE_ID id);

	//スタックシーン取り出し
	void pop(void);

	//シーンリセット
	void Reset(void);

private:

	//状態ID
	enum class STATE
	{
		SCENE_IN,		//開始
		SCENE_UPDATE,	//更新
		SCENE_OUT,		//終了
		SCENE_CHANGE,	//変更
	};

	//シーン生成
	void Create(SCENE_ID id);

	//シーン削除
	void Delete(void);

	//シーン開始
	void SceneIn(void);

	//シーン更新
	void SceneUpdate(void);

	//シーン終了
	void SceneOut(void);

	//シーン変更
	void SceneChange(void);

	static const float	m_fade_speed;		//フェードスピード
	SCENE_ID			m_CurrentSceneID;	//現在のシーンID
	SCENE_ID			m_NextSceneID;		//次のシーンID
	SCENE_ID			m_PushSceneID;		//プッシュするシーンID
	STATE				m_State;			//状態ID
	bool				m_PushFlag;			//シーンのプッシュしたフラグ
	aqua::CSprite		m_FadeSprite;		//フェード用スプライト
};








