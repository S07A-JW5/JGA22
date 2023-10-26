#include "cannon.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"

cEffectCannon::cEffectCannon(aqua::IGameObject* parent)
	: IEffect(parent, "Cannon")
	, m_Velocity(aqua::CVector2::ZERO)
	, m_BoxPos(aqua::CVector2::ZERO)
	, m_PrevPos(aqua::CVector2::ZERO)
{
}

void cEffectCannon::Initialize(aqua::CVector2 posA, aqua::CVector2 posB)
{
	IEffect::Initialize(posA, posB);

	aqua::CVector2 DrawBasePos = ((cCamera*)m_Camera)->GetDrawBasePos();

	m_PositionA *= cMap::m_tile_size;
	m_PositionB *= cMap::m_tile_size;

	m_PositionA -= DrawBasePos;
	m_PositionB -= DrawBasePos;

	m_PrevPos = m_BoxPos = m_PositionA;

	m_Line.pointA = m_PositionA;
	m_Line.pointB = m_PositionA;

	m_Box.Setup(aqua::CVector2::ZERO, 6.0f, 6.0f, 0xffc0c0c0);
	m_Box.position = m_PositionA;

	m_Line.pointA.x += cMap::m_tile_size / 2;
	m_Line.pointA.y += cMap::m_tile_size / 2;
	m_Line.pointB.x += cMap::m_tile_size / 2;
	m_Line.pointB.y += cMap::m_tile_size / 2;

	m_Box.position.x += cMap::m_tile_size / 2;
	m_Box.position.y += cMap::m_tile_size / 2;
	m_Box.position.x -= m_Box.width / 2;
	m_Box.position.y -= m_Box.height / 2;

	m_Line.color = 0xffff7f00;
	m_Line.thickness = 2.0f;

	m_Velocity = (m_PositionB - m_PositionA).Normalize() * 10;
	m_Timer = 0.25f;
}

void cEffectCannon::Update()
{
	if (m_BoxPos == m_PositionB)
	{
		m_Box.visible = false;
		m_Line.visible = false;
		m_Timer -= aqua::GetDeltaTime();
		return;
	}

	m_PrevPos = m_BoxPos;
	m_BoxPos += m_Velocity;

	if ((m_PositionB - m_PositionA).Length() <= (m_BoxPos - m_PositionA).Length())
	{
		m_BoxPos = m_PositionB;
	}

	m_Box.position = m_BoxPos;

	m_Box.position.x += cMap::m_tile_size / 2;
	m_Box.position.y += cMap::m_tile_size / 2;
	m_Box.position.x -= m_Box.width / 2;
	m_Box.position.y -= m_Box.height / 2;

	m_Line.pointA = m_BoxPos;
	m_Line.pointB = m_PrevPos;

	m_Line.pointA.x += cMap::m_tile_size / 2;
	m_Line.pointA.y += cMap::m_tile_size / 2;
	m_Line.pointB.x += cMap::m_tile_size / 2;
	m_Line.pointB.y += cMap::m_tile_size / 2;
}

void cEffectCannon::Draw()
{
	IEffect::Draw();
	m_Box.Draw();
}

void cEffectCannon::Finalize()
{
	IEffect::Finalize();
}
