#include "button.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/text_manager/text/text.h"

const int cButton::m_space = 12;
const int cButton::m_size = 64;

cButton::cButton(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Button")
	, m_Position(aqua::CVector2::ZERO)
	, m_Height(0)
	, m_Width(0)
	, m_DescText()
	, m_DescObj(nullptr)
	, m_Timer(0)
	, m_Switch(false)
	, m_MouseOver(false)
	, m_IsDiscreteButton(false)
{
}

void cButton::Initialize(ButtonFunc button_function, const aqua::CVector2& pos, BUTTON_TYPE type, const std::string& name, const int& width, const int& height, const int& font_size, const std::string& description, const bool& select)
{
	m_Position.x = pos.x - width / 2;
	m_Position.y = pos.y - height / 2;

	m_Width = max(width, m_space * 2);
	m_Height = max(height, m_space * 2);

	m_ButtonFunction = button_function;

	m_ButtonType = type;

	m_IsDiscreteButton = !select;

	m_DescText = description;
	if (m_DescText != "")
	{
		cTextManager* TextMgr = (cTextManager*)aqua::FindGameObject("TextManager");
		if (!TextMgr) return;
		m_DescObj = TextMgr->CreateText(aqua::CVector2::ZERO, m_DescText, 16);

		cText* Text = (cText*)m_DescObj;
		Text->SetVisible(false);
	}

	m_Name.Create(font_size, 1);
	m_Name.text = name;
	m_Name.position.x = m_Position.x + (m_Width - m_Name.GetTextWidth()) / 2;
	m_Name.position.y = m_Position.y + (m_Height - m_Name.GetFontHeight()) / 2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_IsDiscreteButton)
				m_Sprite[i * 3 + j].Create("data\\texture\\ui\\button.png");
			else
			{
				m_Sprite[i * 3 + j].Create("data\\texture\\ui\\window_select.png");
				m_Sprite[i * 3 + j].blend_mode = aqua::ALPHABLEND::ADD;
			}
			m_Sprite[i * 3 + j].position = m_Position;

			switch (j)
			{
			case 0:
				m_Sprite[i * 3 + j].rect.left = 0;
				m_Sprite[i * 3 + j].rect.right = m_space;
				break;
			case 1:
				m_Sprite[i * 3 + j].rect.left = m_space;
				m_Sprite[i * 3 + j].rect.right = m_size - m_space;
				m_Sprite[i * 3 + j].position.x += m_space;
				m_Sprite[i * 3 + j].scale.x = (float)(m_Width - m_space * 2) / (m_size - m_space * 2);
				break;
			case 2:
				m_Sprite[i * 3 + j].rect.left = m_size - m_space;
				m_Sprite[i * 3 + j].rect.right = m_size;
				m_Sprite[i * 3 + j].position.x += m_Width - m_space;
				break;
			default:
				break;
			}
			switch (i)
			{
			case 0:
				m_Sprite[i * 3 + j].rect.top = 0;
				m_Sprite[i * 3 + j].rect.bottom = m_space;
				break;
			case 1:
				m_Sprite[i * 3 + j].rect.top = m_space;
				m_Sprite[i * 3 + j].rect.bottom = m_size - m_space;
				m_Sprite[i * 3 + j].position.y += m_space;
				m_Sprite[i * 3 + j].scale.y = (float)(m_Height - m_space * 2) / (m_size - m_space * 2);
				break;
			case 2:
				m_Sprite[i * 3 + j].rect.top = m_size - m_space;
				m_Sprite[i * 3 + j].rect.bottom = m_size;
				m_Sprite[i * 3 + j].position.y += m_Height - m_space;
				break;
			default:
				break;
			}
		}
	}
}

void cButton::Update()
{
	aqua::CPoint mouse = aqua::mouse::GetCursorPos();

	if (m_IsDiscreteButton)
		for (int i = 0; i < 9; i++)
			m_Sprite[i].color = 0xff0000ff;
	else
		for (int i = 0; i < 9; i++)
			m_Sprite[i].color = 0x00ffffff;

	if (m_Switch && m_ButtonType == BUTTON_TYPE::TOGGLE)
	{
		if (m_IsDiscreteButton)
			for (int i = 0; i < 9; i++)
				m_Sprite[i].color = 0xff00ffff;
		m_ButtonFunction();
	}
	else
	{
		m_Switch = false;
	}

	if (mouse.x < m_Position.x ||
		mouse.x >= m_Position.x + m_Width ||
		mouse.y < m_Position.y ||
		mouse.y >= m_Position.y + m_Height)
	{
		m_Timer = 0;
		m_MouseOver = false;
		if (m_DescText == "") return;
		cText* Text = (cText*)m_DescObj;
		Text->SetVisible(false);
		return;
	}

	m_MouseOver = true;

	if (m_DescText != "")
	{
		if (m_Timer > 2.0f)
		{
			cText* Text = (cText*)m_DescObj;
			Text->SetPosition(aqua::CVector2((float)mouse.x, (float)mouse.y));
			Text->SetVisible(true);
		}
	}
	m_Timer += aqua::GetDeltaTime();

	if (m_IsDiscreteButton)
	{
		for (int i = 0; i < 9; i++)
			m_Sprite[i].color = 0xffffff00;
	}
	else
	{
		std::uint8_t alpha = (uint8_t)(abs(cos(m_Timer * DX_PI)) * 255);
		for (int i = 0; i < 9; i++)
		{
			m_Sprite[i].color = 0xffffffff;
			m_Sprite[i].color.alpha = alpha;
		}
	}

	if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT))
	{
		if (m_IsDiscreteButton)
			for (int i = 0; i < 9; i++)
				m_Sprite[i].color = 0xffff0000;
		else
			for (int i = 0; i < 9; i++)
				m_Sprite[i].color = 0xffffff00;

		if (m_ButtonType == BUTTON_TYPE::BUTTON)
		{
			m_Switch = !m_Switch;
			m_ButtonFunction();
		}
	}
	else if (aqua::mouse::Released(aqua::mouse::BUTTON_ID::LEFT))
	{
		switch (m_ButtonType)
		{
		case cButton::BUTTON_TYPE::TOGGLE:
			m_Switch = !m_Switch;
			break;
		case cButton::BUTTON_TYPE::SWITCH:
			m_Switch = !m_Switch;
			m_ButtonFunction();
			break;
		default:
			break;
		}
	}
}

void cButton::Draw()
{
	if (m_GameObjectState != aqua::GAME_OBJECT_STATE::ACTIVE) return;
	for (int i = 0; i < 9; i++)
		m_Sprite[i].Draw();
	m_Name.Draw();
}

void cButton::Finalize()
{
	for (int i = 0; i < 9; i++)
		m_Sprite[i].Delete();
	m_Name.Delete();

	if (m_DescText != "")
		m_DescObj->DeleteObject();
}

bool cButton::MouseOvered()
{
	return m_MouseOver;
}

bool cButton::Pressed()
{
	return m_Switch;
}
