#include "value.h"
#include <sstream>
#include <iomanip>

cValue::cValue(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Value")
	, m_Max(0)
	, m_Value(0)
	, m_CalcValue(0)
	, m_PrevValue(0)
{
}

void cValue::Initialize(aqua::CVector2 position, int value, int max, int size, bool display_max)
{
	aqua::CVector2 Position = position;
	m_PrevValue = m_CalcValue = m_Value = max(value, 0);
	m_Max = max(max, 0);
	m_ValueLabel.Create(size, 1, true, aqua::FONT_FAMILY_ID::HG_SOUEIKAKUPOP);
	m_MaxLabel.visible = display_max;
	if (display_max)
		m_MaxLabel.Create(size / 2, 1, true, aqua::FONT_FAMILY_ID::HG_SOUEIKAKUPOP);

	m_ValueLabel.position = Position;
	Position.x += 2.0f * size + 8;
	Position.y += .5f * size;
	m_MaxLabel.position = Position;
}

void cValue::Update()
{
	if (m_Value > m_CalcValue)
		m_Value--;
	if (m_Value < m_CalcValue)
		m_Value++;

	aqua::CColor Color = 0xffffffff;

	//if (m_Value <= m_Max / 2)
	//	Color = 0xffffff00;
	//if (m_Value <= m_Max / 4)
	//	Color = 0xffff0000;
	//if (m_Value == 0)
	//	Color = 0xffc00000;

	m_ValueLabel.color = Color;
	m_MaxLabel.color = Color;

	int Value = min(m_Value, 999);
	int Max = min(m_Max, 999);
	{
		std::ostringstream sst;
		sst << std::setw(3) << Value << "/";
		m_ValueLabel.text = sst.str();
	}
	{
		std::ostringstream sst;
		sst << std::setw(3) << Max;
		m_MaxLabel.text = sst.str();
	}
}

void cValue::Draw()
{
	m_ValueLabel.Draw();
	m_MaxLabel.Draw();
}

void cValue::Finalize()
{
	m_ValueLabel.Delete();
	m_MaxLabel.Delete();
}

void cValue::SetNum(int value)
{
	m_PrevValue = m_Value;
	m_CalcValue = max(min(value, m_Max), 0);
}

int cValue::GetNum(bool calcvalue)
{
	if (calcvalue)
		return m_CalcValue;

	return m_Value;
}

float cValue::GetFloatNum()
{
	return (float)m_Value;
}

bool cValue::IsZero()
{
	if (m_CalcValue > 0)
		return false;
	if (m_Value > 0)
		return false;

	return true;
}

bool cValue::Complete()
{
	return m_Value == m_CalcValue;
}
