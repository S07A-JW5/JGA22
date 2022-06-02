#include "title.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../ui_manager/ui_manager.h"

CTitleScene::CTitleScene(aqua::IGameObject* parent)
	: IScene(parent,"TitleScene")
	, m_SoundManager(nullptr)
	, m_UIManager(nullptr)
	, m_GameStartButton(nullptr)
	, m_ManualOpenButton(nullptr)
	, m_ManualCloseButton(nullptr)
{
}

void CTitleScene::Initialize(void)
{
	m_SoundManager = aqua::FindGameObject("SoundManager");
	m_UIManager = aqua::FindGameObject("UIManager");

	m_Label.Create(48, 2);
	m_Label.color = aqua::CColor::WHITE;
	m_Label.text = "";
	m_Label.position.x = (aqua::GetWindowWidth() - m_Label.GetTextWidth()) / 2.0f;
	m_Label.position.y = (aqua::GetWindowHeight() - m_Label.GetFontHeight()) / 2.0f;

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
		ButtonPos, cButton::BUTTON_TYPE::SWITCH, "ゲームスタート", 240, 48, 24);
	ButtonPos.y += 64;
	m_ManualOpenButton = UIMgr->CreateButton(
		[&] {
			m_GameStartButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
			m_ManualOpenButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
			m_ManualCloseButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
			m_Manual.visible = true;
		},
		ButtonPos, cButton::BUTTON_TYPE::SWITCH, "ゲーム説明", 240, 48, 24);
	ButtonPos.y += 64;
	m_ManualCloseButton = UIMgr->CreateButton(
		[&] {
			m_GameStartButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
			m_ManualOpenButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
			m_ManualCloseButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
			m_Manual.visible = false;
		},
		ButtonPos, cButton::BUTTON_TYPE::SWITCH, "閉じる", 120, 48, 24);

	m_ManualCloseButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
}

void CTitleScene::Update(void)
{
}

void CTitleScene::Draw(void)
{
	m_Label.Draw();
	m_Manual.Draw();
}

void CTitleScene::Finalize(void)
{
	m_Label.Delete();
	m_Manual.Delete();
}
