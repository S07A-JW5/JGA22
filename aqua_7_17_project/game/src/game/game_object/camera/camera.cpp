#include "camera.h"

const int cCamera::m_draw_width = 720;
const int cCamera::m_draw_height = 720;

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
	m_Position.x = pos.x - cCamera::m_draw_width / 2;
	m_Position.y = pos.y - cCamera::m_draw_height / 2;
}