#include "game_main.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/unit_manager/unit_manager.h"
#include "game/game_object/ui_manager/ui_manager.h"

cGameMainScene::cGameMainScene(aqua::IGameObject* parent)
	: IScene(parent, "GameMainScene")
	, m_MapGenerator(nullptr)
	, m_UnitManager(nullptr)
	, m_TextManager(nullptr)
{
}

cGameMainScene::~cGameMainScene()
{
}

void cGameMainScene::Initialize()
{
	m_State = STATE_GAME_START;

	m_MapGenerator = aqua::CreateGameObject<cMapGenerator>(this);
	m_UnitManager = aqua::CreateGameObject<cUnitManager>(this);
	m_UIManager = aqua::FindGameObject("UIManager");
	m_TextManager = aqua::FindGameObject("TextManager");
	((cUIManager*)m_UIManager)->SetUIBGVisible(true);
	((cTextManager*)m_TextManager)->SetVisible(true);

	m_Black.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), (float)aqua::GetWindowHeight(), 0xff010101);

	IGameObject::Initialize();
}

void cGameMainScene::Update()
{
	switch (m_State)
	{
	case STATE_GAME_START:	GameStart();	break;
	case STATE_GAME_PLAY:	GamePlay();		break;
	case STATE_GAME_FINISH:	GameFinish();	break;
	}

	IGameObject::Update();
}

void cGameMainScene::Draw()
{
	m_Black.Draw();
	IGameObject::Draw();
}

void cGameMainScene::Finalize()
{
	((cTextManager*)m_TextManager)->ClearText();
	((cTextManager*)m_TextManager)->SetVisible(false);
	((cUIManager*)m_UIManager)->SetUIBGVisible(false);
	IGameObject::Finalize();
}

cMapGenerator* cGameMainScene::GetMapGenerator()
{
	return m_MapGenerator;
}

void cGameMainScene::GameStart()
{
	m_Black.visible = false;
	m_State = STATE_GAME_PLAY;
}

void cGameMainScene::GamePlay()
{
}

void cGameMainScene::GameFinish()
{
	cUIManager* UIMgr = (cUIManager*)m_UIManager;
	UIMgr->SetUIBGVisible(false);
}
