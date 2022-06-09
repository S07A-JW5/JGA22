#include "text.h"
#include "game/game_object/ui_manager/component/window/window.h"
#include "game/game_object/ui_manager/ui_manager.h"
#include <vector>

cText::cText(aqua::IGameObject* parent)
	: IGameObject(parent, "Text")
	, m_Rows(0)
	, m_String()
	, m_Text(nullptr)
	, m_Window(nullptr)
	, m_Width(0)
	, m_Height(0)
	, m_FontSize(0)
{
}

void cText::Initialize(const aqua::CVector2& pos, const std::string& text, const ANCHOR_POS& anchor, const int& font_size, bool with_window)
{
	m_String = text;
	aqua::CVector2 Position = m_Position = pos;
	std::vector<std::string> Text = SeparateText();
	m_Anchor = anchor;
	m_FontSize = font_size;

	m_Text = AQUA_NEW aqua::CLabel[m_Rows];

	int Height = m_Rows * m_FontSize;
	int Width = 0;
	int MaximumWidth = 0;

	for (int i = 0; i < m_Rows && i < Text.size(); i++)
	{
		if (Text[i].empty()) continue;
		m_Text[i].Create(m_FontSize, 1);
		m_Text[i].text = Text[i];
		Width = m_Text[i].GetTextWidth();
		MaximumWidth = max(MaximumWidth, Width);
		m_Text[i].position.x = Position.x;
		m_Text[i].position.y = Position.y + i * font_size;

		switch (((int)m_Anchor) % 3)
		{
		case 0:
			if (with_window)
				m_Text[i].position.x += cWindow::m_space;
			break;
		case 1:
			m_Text[i].position.x -= Width / 2;
			break;
		case 2:
			m_Text[i].position.x -= Width;
			if (with_window)
				m_Text[i].position.x -= cWindow::m_space;
			break;
		default:
			break;
		}

		switch (((int)m_Anchor) / 3)
		{
		case 0:
			if (with_window)
				m_Text[i].position.y += cWindow::m_space;
			break;
		case 1:
			m_Text[i].position.y -= Height / 2;
			break;
		case 2:
			m_Text[i].position.y -= Height;
			if (with_window)
				m_Text[i].position.y -= cWindow::m_space;
			break;
		default:
			break;
		}
	}
	m_Width = MaximumWidth;
	m_Height = Height;

	if (with_window)
	{
		cUIManager* UIMgr = (cUIManager*)aqua::FindGameObject("UIManager");
		if (!UIMgr) return;
		int WinWidth = m_Width = MaximumWidth + cWindow::m_space * 2;
		int WinHeight = m_Height = Height + cWindow::m_space * 2;

		switch (((int)m_Anchor) % 3)
		{
		case 1:
			Position.x -= WinWidth / 2;
			break;
		case 2:
			Position.x -= WinWidth;
			break;
		default:
			break;
		}

		switch (((int)m_Anchor) / 3)
		{
		case 1:
			Position.y -= WinHeight / 2;
			break;
		case 2:
			Position.y -= WinHeight;
			break;
		default:
			break;
		}
		m_Window = UIMgr->CreateUIWindow(this, Position, WinWidth, WinHeight);
		m_Width = WinWidth;
		m_Height = WinHeight;
	}
}

void cText::Update()
{
	IGameObject::Update();
}

void cText::Draw()
{
	IGameObject::Draw();

	for (int i = 0; i < m_Rows; i++)
		m_Text[i].Draw();
}

void cText::Finalize()
{
	for (int i = 0; i < m_Rows; i++)
		m_Text[i].Delete();
	AQUA_SAFE_DELETE_ARRAY(m_Text);

	IGameObject::Finalize();
}

void cText::SetVisible(bool visible)
{
	for (int i = 0; i < m_Rows; i++)
		m_Text[i].visible = visible;

	if (!m_Window) return;

	cWindow* Window = (cWindow*)m_Window;
	Window->SetVisible(visible);
}

int cText::GetWidth()
{
	return m_Width;
}

int cText::GetHeight()
{
	return m_Height;
}

void cText::SetPosition(const aqua::CVector2& pos)
{
	aqua::CVector2 PrevPos = m_Position;
	aqua::CVector2 TargetPos = pos;

	int w = aqua::GetWindowWidth() - m_Width;
	int h = aqua::GetWindowHeight() - m_Height;

	if (TargetPos.x < 0)
		TargetPos.x = 0;
	if (TargetPos.x > w)
		TargetPos.x = (float)w;
	if (TargetPos.y < 0)
		TargetPos.y = 0;
	if (TargetPos.y > h)
		TargetPos.y = (float)h;

	aqua::CVector2 Mov = TargetPos - PrevPos;
	m_Position = TargetPos;
	for (int i = 0; i < m_Rows; i++)
		m_Text[i].position += Mov;

	if (!m_Window) return;
	cWindow* Window = (cWindow*)m_Window;
	Window->SetPosition(TargetPos);
}

void cText::SetText(std::string text)
{
	aqua::CVector2 Position = m_Position;
	m_String = text;
	std::vector<std::string> Text = SeparateText();

	m_Text = AQUA_NEW aqua::CLabel[m_Rows];

	int Height = m_Rows * m_FontSize;
	int Width = 0;
	int MaximumWidth = 0;

	for (int i = 0; i < m_Rows && i < Text.size(); i++)
	{
		if (Text[i].empty()) continue;
		m_Text[i].Create(m_FontSize, 1);
		m_Text[i].text = Text[i];
		Width = m_Text[i].GetTextWidth();
		MaximumWidth = max(MaximumWidth, Width);
		m_Text[i].position.x = Position.x;
		m_Text[i].position.y = Position.y + i * m_FontSize;

		switch (((int)m_Anchor) % 3)
		{
		case 0:
			if (m_Window)
				m_Text[i].position.x += cWindow::m_space;
			break;
		case 1:
			m_Text[i].position.x -= Width / 2;
			break;
		case 2:
			m_Text[i].position.x -= Width;
			if (m_Window)
				m_Text[i].position.x -= cWindow::m_space;
			break;
		default:
			break;
		}

		switch (((int)m_Anchor) / 3)
		{
		case 0:
			if (m_Window)
				m_Text[i].position.y += cWindow::m_space;
			break;
		case 1:
			m_Text[i].position.y -= Height / 2;
			break;
		case 2:
			m_Text[i].position.y -= Height;
			if (m_Window)
				m_Text[i].position.y -= cWindow::m_space;
			break;
		default:
			break;
		}
	}
	m_Width = MaximumWidth;
	m_Height = Height;
}

std::vector<std::string> cText::SeparateText()
{
	std::vector<std::string> Text;
	Text.clear();
	int TextIndex = 0;
	m_Rows = 1;
	std::string Temp = "";

	while (TextIndex < m_String.size())
	{
		bool NewLine = false;
		std::string Char = m_String.substr(TextIndex, 1);
		if ((Char[0] >= 0x80i8 && Char[0] <= 0x9Fi8) ||
			(Char[0] >= 0xE0i8 && Char[0] <= 0xFFi8))
		{
			Char += m_String.substr(++TextIndex, 1);
		}
		else
		{
			std::string Temp2 = "";
			if (Char[0] == '\\')
			{
				Temp2 = '\\' + m_String.substr(TextIndex + 1, 1);
			}
			if (Char[0] == '\n' || Temp2 == "\\n")
			{
				if (Temp2 == "\\n")
					TextIndex++;
				NewLine = true;
			}
		}
		TextIndex++;

		if (NewLine)
		{
			m_Rows++;
			Text.push_back(Temp);
			Temp = "";
			continue;
		}
		Temp += Char;
	}
	Text.push_back(Temp);

	return Text;
}
