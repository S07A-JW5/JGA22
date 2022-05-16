#include "gunshot.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"

cEffectGunshot::cEffectGunshot(aqua::IGameObject* parent)
	: IEffect(parent, "Gunshot")
{
}

void cEffectGunshot::Initialize(aqua::CVector2 posA, aqua::CVector2 posB)
{
	m_Camera = aqua::FindGameObject("Camera");
	cCamera* Camera = (cCamera*)m_Camera;
	aqua::CVector2 mid = (posB - posA) / 2 + posA;

	m_Line.pointA = posA * cMap::m_tile_size - Camera->GetDrawBasePos();
	m_Line.pointB = mid * cMap::m_tile_size - Camera->GetDrawBasePos();

	m_Line2.pointA = mid * cMap::m_tile_size - Camera->GetDrawBasePos();
	m_Line2.pointB = posB * cMap::m_tile_size - Camera->GetDrawBasePos();

	m_Line.pointA.x += cMap::m_tile_size / 2;
	m_Line.pointA.y += cMap::m_tile_size / 2;
	m_Line.pointB.x += cMap::m_tile_size / 2;
	m_Line.pointB.y += cMap::m_tile_size / 2;

	m_Line2.pointA.x += cMap::m_tile_size / 2;
	m_Line2.pointA.y += cMap::m_tile_size / 2;
	m_Line2.pointB.x += cMap::m_tile_size / 2;
	m_Line2.pointB.y += cMap::m_tile_size / 2;

	m_Line.thickness = 2.0f;

	m_Timer = 40;
}

void cEffectGunshot::Update()
{
	if (m_Timer <= 0)
	{
		DeleteObject();
		return;
	}
	m_Line.visible = false;
	m_Line2.visible = false;
	if (m_Timer > 8)
	{
		if ((int)m_Timer % 8 == 0)
			m_Line.visible = true;
		if ((int)m_Timer % 8 == 7)
			m_Line2.visible = true;
	}
	m_Timer -= 1;
}

void cEffectGunshot::Draw()
{
	IEffect::Draw();
	m_Line2.Draw();
}

void cEffectGunshot::Finalize()
{
	IEffect::Finalize();
}
