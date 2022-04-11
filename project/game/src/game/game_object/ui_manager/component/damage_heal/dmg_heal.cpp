#include "dmg_heal.h"

const unsigned int cAmountPopUp::m_color[5] = {
										0xffffff00 ,
										0xffff2020 ,
										0xff7f00ff ,
										0xff00ff00 ,
										0xff007fff };

cAmountPopUp::cAmountPopUp(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "AmountPopUp")
	, m_Position(aqua::CVector2::ZERO)
	, m_Width(0)
	, m_Digit(0)
	, m_TimerPhase(0)
	, m_Timer(0.0f)
	, m_AmountSprite(nullptr)
{
}

void cAmountPopUp::Initialize(const aqua::CVector2& pos, const int& amount, POP_UP_TYPE type, bool miss)
{
	m_Position = pos;
	m_Digit = 1;

	if (!miss)
		for (int i = amount; i >= 10; i /= 10)
		{
			m_Digit++;
		}

	m_TimerPhase = m_Digit - 1;
	m_AmountSprite = new aqua::CSprite[m_Digit];

	for (int i = 0, Amount = amount; i < m_Digit; i++, Amount /= 10)
	{
		std::string FileName = "data\\";
		if (miss)
			FileName += "miss";
		else
			FileName += "num_" + std::to_string(Amount % 10);

		FileName += ".png";
		m_AmountSprite[i].Create(FileName);
		m_AmountSprite[i].color = m_color[type];
		m_AmountSprite[i].position.y = m_Position.y - m_AmountSprite[i].GetTextureHeight() / 2;

		m_Width += m_AmountSprite[i].GetTextureWidth();
	}
	for (int i = 0, Xpos = m_Position.x + m_Width / 2; i < m_Digit; i++)
	{
		Xpos -= m_AmountSprite[i].GetTextureWidth();
		m_AmountSprite[i].position.x = Xpos;

		m_AmountSprite[i].anchor.x = m_AmountSprite[i].GetTextureWidth() / 2;
		m_AmountSprite[i].anchor.y = m_AmountSprite[i].GetTextureHeight() / 2;

		m_AmountSprite[i].scale.x = m_AmountSprite[i].scale.y = 0;
	}

	switch (type)
	{
	case cAmountPopUp::POP_UP_TYPE::DMG_RIVAL:
		m_BackSprite.Create("data\\dmg.png");
		m_BackSprite.rect.right = m_size;
		break;
	case cAmountPopUp::POP_UP_TYPE::DMG_PLAYER:
		m_BackSprite.Create("data\\dmg.png");
		m_BackSprite.rect.left = m_size;
		m_BackSprite.rect.right = m_size * 2;
		break;
	case cAmountPopUp::POP_UP_TYPE::DMG_PP:
		m_BackSprite.Create("data\\dmg.png");
		m_BackSprite.rect.left = m_size * 2;
		m_BackSprite.rect.right = m_size * 3;
		break;
	case cAmountPopUp::POP_UP_TYPE::HEAL_HP:
		m_BackSprite.Create("data\\heal.png");
		m_BackSprite.rect.right = m_size;
		break;
	case cAmountPopUp::POP_UP_TYPE::HEAL_PP:
		m_BackSprite.Create("data\\heal.png");
		m_BackSprite.rect.left = m_size;
		m_BackSprite.rect.right = m_size * 2;
		break;
	default:
		break;
	}
	m_BackSprite.position.x = m_Position.x - m_size / 2;
	m_BackSprite.position.y = m_Position.y - m_size / 2;
}

void cAmountPopUp::Update()
{
	if (m_TimerPhase == -2) return;

	m_Timer += aqua::GetDeltaTime();

	if (m_TimerPhase == -1)
	{
		if (m_Timer > 2.0f)
		{
			m_Timer = 0;
			m_TimerPhase--;
			DeleteObject();
		}
		return;
	}
	if (m_Timer > 0.125f)
	{
		m_Timer = 0;
		m_AmountSprite[m_TimerPhase].scale.x = m_AmountSprite[m_TimerPhase].scale.y = 1;
		m_TimerPhase--;
		return;
	}
	m_AmountSprite[m_TimerPhase].scale.x = m_AmountSprite[m_TimerPhase].scale.y = aqua::easing::OutBack(m_Timer, 0.125f, 0.125f, 1, 5);
}

void cAmountPopUp::Draw()
{
	m_BackSprite.Draw();
	for (int i = 0; i < m_Digit; i++)
		m_AmountSprite[i].Draw();
}

void cAmountPopUp::Finalize()
{
	m_BackSprite.Delete();
	AQUA_SAFE_DELETE_ARRAY(m_AmountSprite);
}
