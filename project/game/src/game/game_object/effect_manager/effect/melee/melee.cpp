#include "melee.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"

cEffectMelee::cEffectMelee(aqua::IGameObject* parent)
	: IEffect(parent, "Melee")
{
}

void cEffectMelee::Initialize(aqua::CVector2 posA, aqua::CVector2 posB)
{
	m_Camera = aqua::FindGameObject("Camera");
	cCamera* Camera = (cCamera*)m_Camera;
	aqua::CVector2 mid = (posB - posA) / 2 + posA;

	m_Line.pointA = posA * cMap::m_tile_size - Camera->GetDrawBasePos();
	m_Line.pointB = posB * cMap::m_tile_size - Camera->GetDrawBasePos();

	m_Line.pointA.x += cMap::m_tile_size / 2;
	m_Line.pointA.y += cMap::m_tile_size / 2;
	m_Line.pointB.x += cMap::m_tile_size / 2;
	m_Line.pointB.y += cMap::m_tile_size / 2;

	m_Line.thickness = 5.0f;

	m_Timer = 1.0f;
}

void cEffectMelee::Update()
{
	if (m_Timer <= 0)
	{
		m_Line.visible = false;
		return;
	}
	if (m_Timer <= 0.4f)
		m_Line.visible = false;
	m_Timer -= aqua::GetDeltaTime();
}

void cEffectMelee::Draw()
{
	IEffect::Draw();
}

void cEffectMelee::Finalize()
{
	IEffect::Finalize();
}
