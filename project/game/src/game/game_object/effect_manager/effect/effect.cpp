#include "Effect.h"
#include "game/game_object/camera/camera.h"

IEffect::IEffect(aqua::IGameObject* parent, std::string name)
	: IGameObject(parent, name, "Effect")
	, m_PositionA(aqua::CVector2::ZERO)
	, m_PositionB(aqua::CVector2::ZERO)
	, m_Camera(nullptr)
	, m_Timer(0)
{
}

void IEffect::Initialize(aqua::CVector2 posA, aqua::CVector2 posB)
{
	m_Camera = aqua::FindGameObject("Camera");
	m_PositionA = posA;
	m_PositionB = posB;
	m_Timer = 1.0f;
}

void IEffect::Update()
{
	if (m_Timer <= 0)
	{
		DeleteObject();
		return;
	}
	m_Timer -= aqua::GetDeltaTime();
}

void IEffect::Draw()
{
	m_Line.Draw();
}

void IEffect::Finalize()
{
}

bool IEffect::EffectPlaying()
{
	if (!this) return false;
	return m_Timer > 0;
}
