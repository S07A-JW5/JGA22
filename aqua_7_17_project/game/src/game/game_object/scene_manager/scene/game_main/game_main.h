#pragma once
#include "aqua.h"
#include "..\scene.h"
#include "map_generator/map_generator.h"

class cGameMainScene : public IScene
{
public:

	//コンストラクタ
	cGameMainScene(aqua::IGameObject* parent);

	//デストラクタ
	~cGameMainScene();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Finalize() override;

	//マップ生成器取得
	cMapGenerator* GetMapGenerator();

private:

	//ゲーム開始
	void GameStart();

	//ゲーム中
	void GamePlay();

	//ゲーム終了
	void GameFinish();

	//状態ID
	enum STATE
	{
		STATE_GAME_START,	//ゲーム開始
		STATE_GAME_PLAY,	//ゲーム中
		STATE_GAME_FINISH,	//ゲーム終了
	};

	STATE  m_State; //状態ID

	IGameObject*	m_UIManager;	//UIマネージャのポインタ
	IGameObject*	m_UnitManager;	//ユニットマネージャのポインタ
	IGameObject*	m_TextManager;	//テキストマネージャのポインタ
	cMapGenerator*	m_MapGenerator;	//マップ生成器のポインタ

	aqua::CBoxPrimitive m_Black;	//トランジション用
};