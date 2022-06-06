#include "result.h"
#include "../../../text_manager/text_manager.h"
#include "../../../ui_manager/ui_manager.h"

CResultScene::CResultScene(aqua::IGameObject* parent)
	: IScene(parent, "Result")
	, m_ResultText(nullptr)
	, m_ReturnTitleButton(nullptr)
	, m_UIVisible(false)
{
}

void CResultScene::Initialize(void)
{
	CTextManager* TextMgr = (CTextManager*)aqua::FindGameObject("TextManager");
	cUIManager* UIMgr = (cUIManager*)aqua::FindGameObject("UIManager");

	aqua::CVector2 ButtonPos = aqua::CVector2::ZERO;
	ButtonPos.x = aqua::GetWindowWidth() / 2.0f;
	ButtonPos.y = aqua::GetWindowHeight() - 128.0f;

	m_ResultText = TextMgr->CreateText(aqua::CVector2(aqua::GetWindowWidth() / 2.0f, 480.0f),
		TextMgr->m_Temp, cText::ANCHOR_POS::CENTER, 24, false);
	((cText*)m_ResultText)->SetVisible(false);

	m_ReturnTitleButton = UIMgr->CreateButton(
		[&] {
			Change(SCENE_ID::TITLE);
			m_ResultText->DeleteObject();
			m_ReturnTitleButton->DeleteObject();
		},
		ButtonPos, cButton::BUTTON_TYPE::SWITCH, "ƒ^ƒCƒgƒ‹‚É–ß‚é", 240, 48, 24);
	m_ReturnTitleButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
}

void CResultScene::Update(void)
{
	if (!m_UIVisible)
	{
		((cText*)m_ResultText)->SetVisible(true);
		m_ReturnTitleButton->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
		m_UIVisible = true;
	}
}

void CResultScene::Draw(void)
{
	m_ResultSprite.Draw();
}

void CResultScene::Finalize(void)
{
	m_ResultSprite.Delete();
}
