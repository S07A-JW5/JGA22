#include "gauge.h"
#include "../value/value.h"

const int cGauge::m_space = 4;
const int cGauge::m_size = 12;

cGauge::cGauge(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Gauge")
	, m_Max(0)
	, m_Value(0)
	, m_CalcValue(0)
	, m_Timer(0)
	, m_PrevValue(0)
	, m_Mirror(false)
	, m_SyncObject(nullptr)
{
}

void cGauge::Initialize(aqua::CVector2 position, int value, int limit, int width, int height, bool mirror, bool has_bg, aqua::IGameObject* sync_obj)
{
	aqua::CVector2 Position = position;
	m_PrevValue = m_CalcValue = m_Value = max(value, 0);
	m_Max = max(limit, 0);
	m_Mirror = mirror;
	m_SyncObject = sync_obj;
	m_Width = width;
	m_Height = height;

	if (has_bg)
	{
		int Width = m_Width + m_space * 2;
		int Height = m_Height + m_space * 2;

		Position.x -= Width / 2;
		Position.y -= Height / 2;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m_Background[i * 3 + j].Create("data\\texture\\ui\\gauge_back.png");
				m_Background[i * 3 + j].position = Position;

				switch (j)
				{
				case 0:
					m_Background[i * 3 + j].rect.left = 0;
					m_Background[i * 3 + j].rect.right = m_space;
					break;
				case 1:
					m_Background[i * 3 + j].rect.left = m_space;
					m_Background[i * 3 + j].rect.right = m_size - m_space;
					m_Background[i * 3 + j].position.x += m_space;
					m_Background[i * 3 + j].scale.x = (float)(Width - m_space * 2) / (m_size - m_space * 2);
					break;
				case 2:
					m_Background[i * 3 + j].rect.left = m_size - m_space;
					m_Background[i * 3 + j].rect.right = m_size;
					m_Background[i * 3 + j].position.x += Width - m_space;
					break;
				default:
					break;
				}
				switch (i)
				{
				case 0:
					m_Background[i * 3 + j].rect.top = 0;
					m_Background[i * 3 + j].rect.bottom = m_space;
					break;
				case 1:
					m_Background[i * 3 + j].rect.top = m_space;
					m_Background[i * 3 + j].rect.bottom = m_size - m_space;
					m_Background[i * 3 + j].position.y += m_space;
					m_Background[i * 3 + j].scale.y = (float)(Height - m_space * 2) / (m_size - m_space * 2);
					break;
				case 2:
					m_Background[i * 3 + j].rect.top = m_size - m_space;
					m_Background[i * 3 + j].rect.bottom = m_size;
					m_Background[i * 3 + j].position.y += Height - m_space;
					break;
				default:
					break;
				}
			}
		}
		Position.x += m_space;
		Position.y += m_space;
	}
	aqua::CColor Color = 0xff00ff00;

	if (m_Value <= m_Max / 2)
		Color = 0xffffff00;
	if (m_Value <= m_Max / 4)
		Color = 0xffff0000;
	if (m_Value == 0)
		Color = 0xffc00000;

	for (int i = 0; i < 2; i++)
	{
		m_Gauge[i].Create("data\\texture\\dot.png");
		m_Gauge[i].position = Position;
		m_Gauge[i].color = Color;
		m_Gauge[i].scale.x = m_Width * m_Value / m_Max;
		m_Gauge[i].scale.y = m_Height;
		if (m_Mirror)
			m_Gauge[i].scale.x *= -1;
	}
}

void cGauge::Update()
{
	if (m_SyncObject)
	{
		if (m_SyncObject->GetGameObjectName() == "Value")
		{
			cValue* Value = (cValue*)m_SyncObject;
			m_Value = Value->GetNum();
			m_CalcValue = Value->GetNum(true);
		}
	}
	else
	{
		if (m_Value == m_CalcValue)
		{
			m_PrevValue = m_CalcValue;
			m_Timer = 0;
			return;
		}

		m_Timer += aqua::GetDeltaTime();
		if (m_Timer > 1.0f)
			m_Timer = 1.0f;

		m_Value = aqua::easing::OutCubic(m_Timer, 1.0f, m_PrevValue, m_CalcValue);
	}
	aqua::CColor Color = 0xff00ff00;

	if (m_CalcValue <= m_Max / 2)
		Color = 0xffffff00;
	if (m_CalcValue <= m_Max / 4)
		Color = 0xffff0000;
	if (m_CalcValue == 0)
		Color = 0xffc00000;

	int length[2];
	length[0] = m_Width * m_Value / m_Max;
	length[1] = m_Width * m_CalcValue / m_Max;

	if (length[0] < length[1])
	{
		float  temp = 0;

		temp = length[1];
		length[1] = length[0];
		length[0] = temp;
	}

	for (int i = 0; i < 2; i++)
	{
		if (length[i] <= 0 && m_CalcValue > 0)
			length[i] = 1;

		m_Gauge[i].color = Color;
		m_Gauge[i].scale.x = length[i];
		if (m_Mirror)
			m_Gauge[i].scale.x *= -1;
	}
	m_Gauge[0].color.alpha = 0x7f;
}

void cGauge::Draw()
{
	m_Gauge[0].visible = !m_Gauge[0].visible;

	for (int i = 0; i < 9; i++)
		m_Background[i].Draw();
	for (int i = 0; i < 2; i++)
		m_Gauge[i].Draw();
}

void cGauge::Finalize()
{
	for (int i = 0; i < 9; i++)
		m_Background[i].Delete();
	for (int i = 0; i < 2; i++)
		m_Gauge[i].Delete();
}

void cGauge::SetNum(int value)
{
	if (m_SyncObject) return;
	if (m_CalcValue == value) return;

	m_PrevValue = m_Value;
	m_Timer = 0;
	m_CalcValue = max(min(value, m_Max), 0);
}

void cGauge::SetMax(int value)
{
	m_Max = value;
}
