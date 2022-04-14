#include "game_main.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/unit_manager/unit_manager.h"
#include "game/game_object/ui_manager/ui_manager.h"

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
	m_State = STATE_GAME_START;

	m_MapGen = aqua::CreateGameObject<cMapGenerator>(this);
	m_UnitMgr = aqua::CreateGameObject<CUnitManager>(this);
	m_UIMgr = aqua::FindGameObject("UIManager");
	//cUIManager* UIMgr = (cUIManager*)m_UIMgr;
	//UIMgr->SetUIBGVisible(true);

	m_Black.Setup(aqua::CVector2::ZERO, aqua::GetWindowWidth(), aqua::GetWindowHeight(), 0xff010101);


	IGameObject::Initialize();
}

void CGameMainScene::Update(void)
{
	switch (m_State)
	{
	case STATE_GAME_START:		GameStart();	break;
	case STATE_GAME_PLAY:		GamePlay();	break;
	case STATE_GAME_FINISH:	GameFinish();	break;
	}

	IGameObject::Update();
}


void CGameMainScene::Draw(void)
{
	m_Black.Draw();
	IGameObject::Draw();
}

cMapGenerator* CGameMainScene::GetMapGenerator()
{
	return m_MapGen;
}

void CGameMainScene::GameStart(void)
{
	m_Black.visible = false;
	m_State = STATE_GAME_PLAY;
}

void CGameMainScene::GamePlay(void)
{
}

void CGameMainScene::GameFinish(void)
{
	cUIManager* UIMgr = (cUIManager*)m_UIMgr;
	UIMgr->SetUIBGVisible(false);
}
