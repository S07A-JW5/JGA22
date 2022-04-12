#include "player.h"
#include "../../unit_manager.h"
#include "game/game_object/ui_manager/ui_manager.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/sound_manager/sound_manager.h"

cPlayer::cPlayer(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
{
}

void cPlayer::Initialize()
{
	m_Sprite.Create("data\\texture\\chr\\player.png");
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
	m_Position.x = m_OnMapPos.x * cMap::m_tile_size;
	m_Position.y = m_OnMapPos.y * cMap::m_tile_size;
	m_CamObj->SetDrawCenterPos(aqua::CVector2(m_Position.x - cMap::m_tile_size / 2,
		m_Position.y - cMap::m_tile_size / 2));	
	m_Sprite.position = m_Position - m_CamObj->GetDrawBasePos();
}

void cPlayer::Draw()
{
	m_Sprite.Draw();
}

void cPlayer::Finalize()
{
	m_Sprite.Delete();
}
