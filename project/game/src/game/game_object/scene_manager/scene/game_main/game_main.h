#pragma once
#include "aqua.h"
#include "..\scene.h"
#include "map_generator/map_generator.h"

class CGameMainScene
	: public IScene
{
public:

	//コンストラクタ
	CGameMainScene(aqua::IGameObject* parent);

	//デストラクタ
	~CGameMainScene(void);

	//初期化
	void Initialize(void);

	//更新
	void Update(void);

	// 描画
	void Draw(void);

	//void Finalize() override;

	cMapGenerator* GetMapGenerator();
private:

	//ゲーム開始
	void GameStart(void);

	//ゲーム中
	void GamePlay(void);

	//ゲーム終了
	void GameFinish(void);

	//状態ID
	enum STATE
	{
		STATE_GAME_START,		//!ゲーム開始
		STATE_GAME_PLAY,		//!ゲーム中
		STATE_GAME_FINISH,		//!ゲーム終了
	};

	STATE  m_State;		//! 状態ID

	IGameObject* m_UIMgr;
	IGameObject* m_UnitMgr;
	cMapGenerator* m_MapGen;
	aqua::CBoxPrimitive m_Black;
};