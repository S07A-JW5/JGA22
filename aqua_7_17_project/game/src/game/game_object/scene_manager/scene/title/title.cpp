#include "title.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../ui_manager/ui_manager.h"

cTitleScene::cTitleScene(aqua::IGameObject* parent)
	: IScene(parent,"TitleScene")
	, m_SoundManager(nullptr)
	, m_UIManager(nullptr)
	, m_GameStartButton(nullptr)
	, m_ManualOpenButton(nullptr)
	, m_ManualCloseButton(nullptr)
{
}

void cTitleScene::Initialize()
{
	m_SoundManager = aqua::FindGameObject("SoundManager");
	m_UIManager = aqua::FindGameObject("UIManager");

	aqua::CVector2 ButtonPos = aqua::CVector2::ZERO;
	ButtonPos.x = aqua::GetWindowWidth() / 2.0f;
	ButtonPos.y = aqua::GetWindowHeight() - 160.0f;

	m_Manual.Create("data\\texture\\manual.png");
	m_Manual.position.x = (aqua::GetWindowWidth() - m_Manual.GetTextureWidth()) / 2.0f;
	m_Manual.position.y = (664 - m_Manual.GetTextureHeight()) / 2.0f;
	m_Manual.visible = false;

	//cSoundManager* SoundMgr = (cSoundManager*)m_SoundManager;
	//SoundMgr->PlayBGM(BGM_LIST::0);

	cUIManager* UIMgr = (cUIManager*)m_UIManager;

	m_GameStartButton = UIMgr->CreateButton(
		[&] {
			cSoundManager* SoundMgr = (cSoundManager*)m_SoundManager;
			SoundMgr->StopBGM();
			//SoundMgr->Play(SE_LIST::0);

			Change(SCENE_ID::GAMEMAIN);
			m_GameStartButton->DeleteObject();
			m_ManualOpenButton->DeleteObject();
			m_ManualCloseButton->DeleteObject();
		},
		ButtonPos, cButton::BUTTON_TYPE::SWITCH, "�Q�[���X�^�[�g", 240, 48, 24);

	ButtonPos.y += 64;

	m_ManualOpenButton = UIMgr->CreateButton(
		[&] {
			m_GameStartButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
			m_ManualOpenButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
			m_ManualCloseButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
			m_Manual.visible = true;
		},
		ButtonPos, cButton::BUTTON_TYPE::SWITCH, "�Q�[������", 240, 48, 24);

	ButtonPos.y += 64;

	m_ManualCloseButton = UIMgr->CreateButton(
		[&] {
			m_GameStartButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
			m_ManualOpenButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
			m_ManualCloseButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
			m_Manual.visible = false;
		},
		ButtonPos, cButton::BUTTON_TYPE::SWITCH, "����", 120, 48, 24);

	m_ManualCloseButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
}

void cTitleScene::Update()
{
}

void cTitleScene::Draw()
{
	m_Manual.Draw();
}

void cTitleScene::Finalize()
{
	m_Manual.Delete();
}
