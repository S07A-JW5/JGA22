#include "select.h"
#include "../../ui_manager.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/text_manager/text/text.h"

const int cSelection::m_selection_per_page = 8;
const int cSelection::m_width = 256;
const int cSelection::m_height = 34 * m_selection_per_page + cWindow::m_space * 2;

cSelection::cSelection(aqua::IGameObject* parent)
	: IGameObject(parent, "Selection")
	, m_Position(aqua::CVector2::ZERO)
	, m_PrevFramePage(0)
	, m_Page(0)
	, m_MaxPage(0)
	, m_ButtonPressed(false)
	, m_Number()
	, m_DescText()
	, m_CurNum(-1)
	, m_UIManager(nullptr)
	, m_PageTextWindow(nullptr)
	, m_PageTextObj(nullptr)
	, m_DescWindow(nullptr)
	, m_DescObj(nullptr)
	, m_Window(nullptr)
	, m_NextPage(nullptr)
	, m_PrevPage(nullptr)
	, m_ButtonList()
{
}

void cSelection::Initialize(std::vector<int> number, std::vector<std::string> name, std::vector<std::string> desc, aqua::CVector2 pos)
{
	m_UIManager = GetParent();
	cUIManager* UIMgr = (cUIManager*)m_UIManager;

	CTextManager* TextMgr = (CTextManager*)aqua::FindGameObject("TextManager");

	m_Number = number;

	m_PrevFramePage = -1;
	m_Page = 0;

	m_MaxPage = max((m_Number.size() - 1) / m_selection_per_page + 1, 1);

	m_Position = pos;
	m_Position.x -= m_width / 2;

	m_Window = UIMgr->CreateUIWindow(m_Position, m_width, m_height);

	m_PrevPage = UIMgr->CreateButton([=]() {m_Page = (m_Page + m_selection_per_page - 1) % m_MaxPage; }, aqua::CVector2(m_Position.x + 32, m_Position.y + m_height + 25), cButton::BUTTON_TYPE::SWITCH, "←", 64, 50, 24, "前のページへ");
	m_NextPage = UIMgr->CreateButton([=]() {++m_Page %= m_MaxPage; }, aqua::CVector2(m_Position.x + m_width - 32, m_Position.y + m_height + 25), cButton::BUTTON_TYPE::SWITCH, "→", 64, 50, 24, "次のページへ");

	m_PageTextWindow = UIMgr->CreateUIWindow(aqua::CVector2(m_Position.x + m_width / 4, m_Position.y + m_height), 128, 50);
	m_DescWindow = UIMgr->CreateUIWindow(aqua::CVector2(m_Position.x, m_Position.y + m_height + 50), 256, 24 * 3 + cWindow::m_space * 2);
	m_DescObj = TextMgr->CreateText(aqua::CVector2(m_Position.x + m_width / 2, m_Position.y + m_height + 62), "", cText::ANCHOR_POS::TOP, 16, false);
	m_PageTextObj = TextMgr->CreateText(aqua::CVector2(m_Position.x + m_width / 2, m_Position.y + m_height + 25), " ", cText::ANCHOR_POS::CENTER, 16, false);

	for (int i = 0; i < m_Number.size(); i++)
	{
		std::string Name = "";
		std::string Desc = "";
		if (i < name.size())
			Name = name[i];
		if (i < desc.size())
			Desc = desc[i];
		m_DescText.push_back(Desc);
		cButton* Button = UIMgr->CreateButton([=]() {m_ButtonPressed = true; }, aqua::CVector2(m_Position.x + m_width / 2, m_Position.y + 29 + 34 * (i % m_selection_per_page)), cButton::BUTTON_TYPE::SWITCH, Name, 240, 32, 24, "", true);
		Button->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
		m_ButtonList.push_back(Button);
	}

	//if(m_MaxPage<=1)
	//{
	//	m_NextPage->SetActive(false);
	//	m_PrevPage->SetActive(false);
	//}
}

void cSelection::Update()
{
	if (m_PrevFramePage != m_Page)
	{
		cText* PageText = (cText*)m_PageTextObj;
		PageText->SetText("ページ " + std::to_string(m_Page + 1) + "/" + std::to_string(m_MaxPage));

		for (int i = m_PrevFramePage * m_selection_per_page; i < m_PrevFramePage * m_selection_per_page + m_selection_per_page && i >= 0 && i < m_ButtonList.size(); i++)
		{
			m_ButtonList[i]->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
		}
		for (int i = m_Page * m_selection_per_page; i < m_Page * m_selection_per_page + m_selection_per_page && i >= 0 && i < m_ButtonList.size(); i++)
		{
			m_ButtonList[i]->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
		}
	}
	m_PrevFramePage = m_Page;

	cText* Description = (cText*)m_DescObj;
	Description->SetText("");

	for (int i = 0; i < m_ButtonList.size(); i++)
	{
		if (m_ButtonList[i]->Pressed())
		{
			m_CurNum = m_Number[i];
		}
		if (m_ButtonList[i]->MouseOvered())
		{
			Description->SetText(m_DescText[i]);
		}
	}
}

void cSelection::Draw()
{
}

void cSelection::Finalize()
{
	m_Number.clear();
	m_DescText.clear();
	m_PageTextWindow->DeleteObject();
	m_PageTextObj->DeleteObject();
	m_DescWindow->DeleteObject();
	m_DescObj->DeleteObject();
	m_Window->DeleteObject();
	m_NextPage->DeleteObject();
	m_PrevPage->DeleteObject();
	for (auto it : m_ButtonList)
		it->DeleteObject();
	m_ButtonList.clear();
}

bool cSelection::Pressed()
{
	return m_ButtonPressed;
}

int cSelection::GetNum()
{
	if (!m_ButtonPressed)
		return -1;
	return m_CurNum;
}
