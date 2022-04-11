#include "title.h"
#include "../../../sound_manager/sound_manager.h"
#include "game/game_object/text_manager/text/text.h"

CTitleScene::CTitleScene(aqua::IGameObject* parent)
	: IScene(parent,"TitleScene")
	, m_SoundManager(nullptr)
{
}

void CTitleScene::Initialize(void)
{
	m_SoundManager = aqua::FindGameObject("SoundManager");

	m_Label.Create(50, 2);
	m_Label.color = aqua::CColor::WHITE;
	m_Label.text = "タイトル";
	m_Label.position.x = (aqua::GetWindowWidth() - m_Label.GetTextWidth()) / 2.0f;
	m_Label.position.y = (aqua::GetWindowHeight() - m_Label.GetFontHeight()) / 2.0f;

	m_Text.Create(30, 2);
	m_Text.color = aqua::CColor::WHITE;
	m_Text.text = "スペースキーを押して開始";
	m_Text.position.x = (aqua::GetWindowWidth() - m_Text.GetTextWidth()) / 2.0f;
	m_Text.position.y = aqua::GetWindowHeight() - m_Text.GetFontHeight() * 2.0f;

	//cSoundManager* SoundMgr = (cSoundManager*)m_SoundManager;
	//SoundMgr->PlayBGM(BGM_LIST::OVERTURE);
}

void CTitleScene::Update(void)
{
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
	{
		//cSoundManager* SoundMgr = (cSoundManager*)m_SoundManager;
		//SoundMgr->StopBGM();
		//SoundMgr->Play(SE_LIST::MOJA);

		Change(SCENE_ID::GAMEMAIN);
	}
}

void CTitleScene::Draw(void)
{
	m_Label.Draw();
	m_Text.Draw();
}

void CTitleScene::Finalize(void)
{
	m_Label.Delete();
	m_Text.Delete();
}
