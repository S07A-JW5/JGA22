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

	m_Line.pointA = posA * cMap::m_tile_size  - Camera->GetDrawBasePos();
	m_Line.pointB = posB * cMap::m_tile_size - Camera->GetDrawBasePos();

	m_Line.pointA.x += cMap::m_tile_size / 2;
	m_Line.pointA.y += cMap::m_tile_size / 2;
	m_Line.pointB.x += cMap::m_tile_size / 2;
	m_Line.pointB.y += cMap::m_tile_size / 2;

	m_Timer = 15;
}

void cEffectGunshot::Update()
{
	if (m_Timer <= 0)
	{
		DeleteObject();
		return;
	}
	m_Line.visible = false;
	if (m_Timer - (int)m_Timer == 0)
		m_Line.visible = true;
	m_Timer -= 0.25f;
}

void cEffectGunshot::Draw()
{
	IEffect::Draw();
}

void cEffectGunshot::Finalize()
{
	IEffect::Finalize();
}
