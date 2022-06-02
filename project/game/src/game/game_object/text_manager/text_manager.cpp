#include "text_manager.h"
#include "../ui_manager/ui_manager.h"
#include "../ui_manager/component/window/window.h"

const int CTextManager::m_rows = 10;
const int CTextManager::m_font_size = 16;
const int CTextManager::m_text_window_width = 1280 - 720;
const int CTextManager::m_text_window_height = 720 - 546;
const aqua::CVector2 CTextManager::m_text_window_pos = aqua::CVector2(720, 546);

CTextManager::CTextManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "TextManager")
	, m_DisplayText()
	, m_Text(nullptr)
	, m_TextDisplay(false)
	, m_TextIndex(0)
	, m_Rows(0)
	, m_Timer(0.0f)
	, m_Window(nullptr)
	, m_UIManager(nullptr)
{
}

void CTextManager::Initialize()
{
	m_Text = AQUA_NEW aqua::CLabel[m_rows];

	m_UIManager = aqua::FindGameObject("UIManager");

	m_DisplayText = "";

	for (int i = 0; i < m_rows; i++)
	{
		m_Text[i].Create(m_font_size);
		m_Text[i].position = m_text_window_pos;
		m_Text[i].position.x += 10;
		m_Text[i].position.y += 8 + i * m_font_size;
		m_Text[i].color = 0xffffffff;
		m_Text[i].text = "";
	}
	WindowCheck();

	SetVisible(false);
}

void CTextManager::Update()
{
	IGameObject::Update();

	if (m_TextDisplay)
	{
		m_Timer += aqua::GetDeltaTime();
		if (m_Timer >= 0.015f)
		{
			m_Timer = 0;
			if (m_TextIndex >= m_DisplayText.size())
			{
				if (m_DisplayText == "" && m_Rows == 0)
				{
					if (m_TextList.size() <= 0) return;
					m_TextIndex = 0;
				}
				else
				{
					if (m_TextList.size() <= 1) return;
					m_TextIndex = 0;
					if (++m_Rows >= m_rows)
					{
						m_Rows = m_rows - 1;
						for (int i = 0; i < m_rows - 1; i++)
							m_Text[i].text = m_Text[i + 1].text;
						m_Text[m_rows - 1].text = "";
					}
					m_TextList.pop_front();
				}
				auto it = m_TextList.begin();
				m_DisplayText = (*it);
			}
			std::string Char = m_DisplayText.substr(m_TextIndex, 1);
			if ((Char[0] >= 0x80i8 && Char[0] <= 0x9Fi8) ||
				(Char[0] >= 0xE0i8 && Char[0] <= 0xFFi8))
			{
				Char += m_DisplayText.substr(++m_TextIndex, 1);
			}
			m_TextIndex++;

			AQUA_DEBUG_LOG(Char);
			m_Text[m_Rows].text += Char;
		}
	}
}

void CTextManager::Draw()
{
	IGameObject::Draw();

	for (int i = 0; i < m_rows; i++)
		m_Text[i].Draw();
}

void CTextManager::Finalize()
{
	for (int i = 0; i < m_rows; i++)
		m_Text[i].Delete();
	AQUA_SAFE_DELETE_ARRAY(m_Text);

	m_Window = nullptr;
	IGameObject::Finalize();
}

void CTextManager::SetVisible(bool visible)
{
	WindowCheck();
	((cWindow*)m_Window)->SetVisible(visible);
	for (int i = 0; i < m_rows; i++)
		m_Text[i].visible = visible;
}

void CTextManager::EnterText(std::string text)
{
	m_TextDisplay = true;

	bool NewLine = false;
	std::string Char = "";
	std::string Text = "";
	std::string EnteredText = text;

	for (int Index = 0; Index < EnteredText.size(); Index++)
	{
		NewLine = false;
		Char = EnteredText.substr(Index, 1);
		if ((Char[0] >= 0x80i8 && Char[0] <= 0x9Fi8) ||
			(Char[0] >= 0xE0i8 && Char[0] <= 0xFFi8))
		{
			Char += EnteredText.substr(++Index, 1);
		}
		else
		{
			std::string Temp = "";
			if (Char[0] == '\\')
			{
				Temp = '\\' + EnteredText.substr(Index + 1, 1);
			}
			if (Char[0] == '\n' || Temp == "\\n")
			{
				if (Temp == "\\n")
					Index++;
				NewLine = true;
			}
		}
		if (NewLine)
			m_TextList.push_back(Text);
		else
			Text += Char;
	}
	m_TextList.push_back(Text);
}

void CTextManager::ClearText()
{
	for (int i = 0; i < m_rows; i++)
		m_Text[i].text = "";

	m_TextIndex = 0;
	m_Rows = 0;

	m_DisplayText = "";
	m_TextList.clear();
}

void CTextManager::WindowCheck()
{
	if (!m_Window)
	{
		cUIManager* UIMgr = (cUIManager*)m_UIManager;
		m_Window = UIMgr->CreateUIWindow(this, m_text_window_pos, m_text_window_width, m_text_window_height, 0xff00c000);
	}
}

cText* CTextManager::CreateText(const aqua::CVector2& pos, const std::string& text, const int& font_size, bool with_window)
{
	return CreateText(pos, text, cText::ANCHOR_POS::LEFT_TOP, font_size, with_window);
}

cText* CTextManager::CreateText(const aqua::CVector2& pos, const std::string& text, const cText::ANCHOR_POS& anchor, const int& font_size, bool with_window)
{
	cText* Text = aqua::CreateGameObject<cText>(this);
	Text->Initialize(pos, text, anchor, font_size, with_window);
	return Text;
}
