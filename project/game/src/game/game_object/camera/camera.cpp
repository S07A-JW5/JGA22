#include "camera.h"

cCamera::cCamera(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Camera")
	, m_Position(aqua::CVector2::ZERO)
{
}

void cCamera::Initialize()
{
	m_Position = aqua::CVector2::ZERO;
}

void cCamera::Update()
{
}

void cCamera::Draw()
{
}

void cCamera::Finalize()
{
}

aqua::CVector2 cCamera::GetDrawBasePos()
{
	return m_Position;
}

void cCamera::SetDrawCenterPos(aqua::CVector2 pos)
{
	m_Position.x = pos.x - aqua::GetWindowWidth() / 2;
	m_Position.y = pos.y - aqua::GetWindowHeight() / 2;
}