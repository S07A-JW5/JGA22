#include "text_manager.h"
#include "../ui_manager/ui_manager.h"
#include "../ui_manager/component/window/window.h"

const int CTextManager::m_rows = 5;
const int CTextManager::m_font_size = 24;
const int CTextManager::m_text_window_height = m_font_size * m_rows + 12 * 2;
const aqua::CVector2 CTextManager::m_text_window_pos = aqua::CVector2(0, aqua::GetWindowHeight() - m_text_window_height);

CTextManager::CTextManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "TextManager")
	, m_String()
	, m_Text(nullptr)
	, m_TextDisplay(false)
	, m_TextIndex(0)
	, m_Rows(0)
	, m_Timer(0.0f)
	, m_DisplayMode(DISPLAY_MODE::NO_WINDOW)
	, m_Window(nullptr)
	, m_UIManager(nullptr)
{
}

void CTextManager::Initialize()
{
	m_Text = AQUA_NEW aqua::CLabel[m_rows];

	m_UIManager = aqua::FindGameObject("UIManager");

	m_String = "";

	for (int i = 0; i < m_rows; i++)
	{
		m_Text[i].Create(m_font_size, 1);
		m_Text[i].position.y = aqua::GetWindowHeight() - m_text_window_height + 12 + i * m_font_size;
		m_Text[i].color = 0xffffffff;
		m_Text[i].edge_color = 0xff010101;
		m_Text[i].text = "";
	}
	WindowCheck();
}

void CTextManager::Update()
{
	if (m_String == "")
	{
		cWindow* Window = (cWindow*)m_Window;
		Window->SetPosition(aqua::CVector2(0, aqua::GetWindowHeight()));
	}
	else
	{
		m_TextDisplay = true;
		switch (m_DisplayMode)
		{
		case CTextManager::DISPLAY_MODE::STANDARD:
		{
			cWindow* Window = (cWindow*)m_Window;
			m_TextDisplay = Window->GetPosition() == m_text_window_pos;
		}
		case CTextManager::DISPLAY_MODE::NO_WINDOW:
			m_Timer += aqua::GetDeltaTime();
			if (m_Timer >= 0.030f && m_TextIndex < m_String.size() && m_Rows <= m_rows)
			{
				m_Timer = 0;
				bool NewLine = false;
				std::string Char = m_String.substr(m_TextIndex, 1);
				if ((Char[0] >= (char)0x80 && Char[0] <= (char)0x9F) ||
					(Char[0] >= (char)0xE0 && Char[0] <= (char)0xFF))
				{
					Char += m_String.substr(++m_TextIndex, 1);
				}
				else
				{
					std::string Temp2 = "";
					if (Char[0] == '\\')
					{
						Temp2 = '\\' + m_String.substr(m_TextIndex + 1, 1);
					}
					if (Char[0] == '\n' || Temp2 == "\\n")
					{
						if (Temp2 == "\\n")
							m_TextIndex++;
						m_Rows++;
						NewLine = true;
					}
				}
				m_TextIndex++;

				if (!NewLine)
				{
					m_Text[m_Rows].text += Char;
					AQUA_DEBUG_LOG(Char);
				}
			}
			break;
		case CTextManager::DISPLAY_MODE::BATTLE:
			break;
		default:
			break;
		}
	}

	IGameObject::Update();
}

void CTextManager::Draw()
{
	IGameObject::Draw();

	cWindow* Window = (cWindow*)m_Window;
	if (Window->GetPosition() == m_text_window_pos)
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

void CTextManager::SetText(int rows, std::string text)
{
	m_Text[rows].text = text;
	m_Text[rows].position.x = (aqua::GetWindowWidth() - m_Text[rows].GetTextWidth()) / 2;

	m_String = "m9(^„D^)";

	WindowCheck();
}

void CTextManager::SetText(std::string text)
{
	ClearText();
	m_Timer = 0;
	m_String = text;
	for (int i = 0; i < m_rows; i++)
		m_Text[i].position.x = aqua::GetWindowWidth() / 4;

	WindowCheck();
}

void CTextManager::ClearText()
{
	for (int i = 0; i < m_rows; i++)
		m_Text[i].text = "";

	m_TextIndex = 0;
	m_Rows = 0;

	m_String = "";
}

void CTextManager::SetMode(DISPLAY_MODE mode)
{
	if (m_DisplayMode == mode) return;

	m_DisplayMode = mode;
	switch (m_DisplayMode)
	{
	case CTextManager::DISPLAY_MODE::STANDARD:
		WindowCheck();
		break;
	case CTextManager::DISPLAY_MODE::NO_WINDOW:
	case CTextManager::DISPLAY_MODE::BATTLE:
		{
			cWindow* Window = (cWindow*)m_Window;
			Window->SetPosition(aqua::CVector2(0, aqua::GetWindowHeight()));
			Window->SetVisible(false);
		}
		break;
	default:
		break;
	}
}

void CTextManager::WindowCheck()
{
	if (!m_Window)
	{
		cUIManager* UIMgr = (cUIManager*)m_UIManager;
		m_Window = UIMgr->CreateUIWindow(aqua::CVector2(0, aqua::GetWindowHeight()), aqua::GetWindowWidth(), m_text_window_height, this);
	}
	cWindow* Window = (cWindow*)m_Window;
		
	if (m_DisplayMode == DISPLAY_MODE::STANDARD)
		Window->SetVisible(true);

	if (m_String != "")
		Window->SetPosition(m_text_window_pos);
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
