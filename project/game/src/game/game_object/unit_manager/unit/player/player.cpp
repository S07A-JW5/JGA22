#include "player.h"
#include "game/game_object/camera/camera.h"
#include "../../unit_manager.h"
#include "game/game_object/ui_manager/ui_manager.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/sound_manager/sound_manager.h"

cPlayer::cPlayer(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
	, m_StairPos(aqua::CVector2::ZERO)
{
}

void cPlayer::Initialize()
{
	IUnit::Initialize();
	m_Sprite.Create("data\\texture\\chr\\player.png");
	//m_Sight.Create("data\\texture\\sight.png");
}

void cPlayer::Update()
{
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::W))
	{
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x, m_OnMapPos.y - 1))
			m_OnMapPos.y -= 1;
	}
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::A))
	{
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x - 1, m_OnMapPos.y))
			m_OnMapPos.x -= 1;
	}
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::S))
	{
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x, m_OnMapPos.y + 1))
			m_OnMapPos.y += 1;
	}
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::D))
	{
		if (m_MapObj->IsWalkableTile(m_OnMapPos.x + 1, m_OnMapPos.y))
			m_OnMapPos.x += 1;
	}
	if (m_OnMapPos == m_StairPos)
	{
		CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
		UnitMgr->MapGeneration();
	}

	cCamera* Camera = (cCamera*)m_CamObj;

	m_Position.x = m_OnMapPos.x * cMap::m_tile_size;
	m_Position.y = m_OnMapPos.y * cMap::m_tile_size;
	Camera->SetDrawCenterPos(aqua::CVector2(m_Position.x + cMap::m_tile_size / 2,
		m_Position.y + cMap::m_tile_size / 2));
	m_Sprite.position = m_Position - Camera->GetDrawBasePos();
}

void cPlayer::Draw()
{
	m_Sprite.Draw();
	m_Sight.Draw();
}

void cPlayer::Finalize()
{
	m_Sprite.Delete();
	m_Sight.Delete();
}

void cPlayer::SetStairPosition(aqua::CVector2 pos)
{
	m_StairPos = pos;
}
