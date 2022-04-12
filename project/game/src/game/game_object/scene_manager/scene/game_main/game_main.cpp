#include "game_main.h"
#include"game/game_object/text_manager/text_manager.h"

CGameMainScene::CGameMainScene(aqua::IGameObject* parent)
	: IScene(parent, "GameMainScene")
	, m_MapGen(nullptr)
	, m_UnitMgr(nullptr)
{
}

CGameMainScene::~CGameMainScene(void)
{
}

void CGameMainScene::Initialize(void)
{
	m_State = STATE_GAME_PLAY;

	m_UnitMgr = aqua::CreateGameObject<CUnitManager>(this);
	m_MapGen = aqua::CreateGameObject<cMapGenerator>(this);

	IGameObject::Initialize();
}

void CGameMainScene::Update(void)
{
	switch (m_State)
	{
	case STATE_GAME_START:  GameStart();   break;
	case STATE_GAME_PLAY:   GamePlay();    break;
	case STATE_GAME_FINISH: GameFinish();  break;
	}

	IGameObject::Update();
}


void CGameMainScene::Draw(void)
{
	IGameObject::Draw();
}

cMapGenerator* CGameMainScene::GetMapGenerator()
{
	return m_MapGen;
}

void CGameMainScene::GameStart(void)
{
}

void CGameMainScene::GamePlay(void)
{
}

void CGameMainScene::GameFinish(void)
{
}
