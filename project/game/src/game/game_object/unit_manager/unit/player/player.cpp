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
	m_Sprite.position.x = cCamera::m_draw_width / 2 - cMap::m_tile_size / 2;
	m_Sprite.position.y = cCamera::m_draw_height / 2 - cMap::m_tile_size / 2;
	//m_Sight.Create("data\\texture\\sight.png");
}

void cPlayer::Update()
{
	m_DesiredAction = ACTION::DUMMY;

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::W))
	{
		m_DesiredAction = ACTION::MOVE;
		m_MoveTo = DIRECTION::NORTH;
	}
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::A))
	{
		m_DesiredAction = ACTION::MOVE;
		m_MoveTo = DIRECTION::WEST;
	}
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::S))
	{
		m_DesiredAction = ACTION::MOVE;
		m_MoveTo = DIRECTION::SOUTH;
	}
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::D))
	{
		m_DesiredAction = ACTION::MOVE;
		m_MoveTo = DIRECTION::EAST;
	}

	if (m_DesiredAction != ACTION::DUMMY)
		Action();

	cCamera* Camera = (cCamera*)m_Camera;

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

bool cPlayer::Action()
{
	if (m_DidAction) return true;

	switch (m_DesiredAction)
	{
	case IUnit::ACTION::WAIT:
		return Wait();
		break;
	case IUnit::ACTION::MOVE:
		return Move();
		break;
	case IUnit::ACTION::ATTACK:
		return Attack();
		break;
	}
	return false;
}

bool cPlayer::Wait()
{
	return false;
}

bool cPlayer::Move()
{
	bool Moved = IUnit::Move();
	if (Moved)
	{
		if (m_OnMapPos == m_StairPos)
		{
			m_Life = m_MaxLife;
			CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
			UnitMgr->MapGeneration();
		}
	}
	return Moved;
}

bool cPlayer::Attack()
{
	return false;
}
