#include "window.h"

const int cWindow::m_space = 4;
const int cWindow::m_size = 12;

cWindow::cWindow(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Window")
	, m_Position(aqua::CVector2::ZERO)
	, m_Height(0)
	, m_Width(0)
{
}

void cWindow::Initialize(const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color)
{
	m_Position = pos;
	m_Width = max(width, m_space * 2);
	m_Height = max(height, m_space * 2);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_Sprite[i * 3 + j].Create("data\\texture\\ui\\window.png");
			m_Sprite[i * 3 + j].position = m_Position;
			m_Sprite[i * 3 + j].color = color;

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
	IGameObject::Initialize();
}

void cWindow::Update()
{
	IGameObject::Update();
}

void cWindow::Draw()
{
	for (int i = 0; i < 9; i++)
		m_Sprite[i].Draw();

	IGameObject::Draw();
}

void cWindow::Finalize()
{
	for (int i = 0; i < 9; i++)
		m_Sprite[i].Delete();
	IGameObject::Finalize();
}

void cWindow::SetVisible(bool visible)
{
	for (int i = 0; i < 9; i++)
		m_Sprite[i].visible = visible;
}

void cWindow::SetPosition(const aqua::CVector2& pos)
{
	aqua::CVector2 PrevPos = m_Position;
	aqua::CVector2 Mov = pos - PrevPos;
	m_Position = pos;
	for (int i = 0; i < 9; i++)
		m_Sprite[i].position += Mov;
}

aqua::CVector2 cWindow::GetPosition()
{
	return m_Position;
}
