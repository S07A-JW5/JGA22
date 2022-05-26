#include "bot.h"
#include "../../unit_manager.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/ui_manager/ui_manager.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/sound_manager/sound_manager.h"
#include <vector>

cBot::cBot(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
	, m_TargetVision(false)
	, m_LastSeenTargetPos(aqua::CVector2::ZERO)
{
}

void cBot::Initialize()
{
	IUnit::Initialize();
	m_Sprite.visible = false;
}

void cBot::Update()
{
	CameraUpdate();
}

bool cBot::Action()
{
	CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
	aqua::CVector2 PlayerPos = UnitMgr->GetPlayerPos();
	bool Attacked = false;

	if (m_TargetVision &&
		UnitMgr->BetweenPlayer(m_OnMapPos) <= m_SightRange &&
		!m_MapObj->HitWall(m_OnMapPos, PlayerPos))
		m_DidAction = Attacked = Attack(PlayerPos);

	m_TargetVision = (UnitMgr->BetweenPlayer(m_OnMapPos) <= m_SightRange &&
		!m_MapObj->HitWall(m_OnMapPos, PlayerPos));
	if (m_TargetVision)
		m_LastSeenTargetPos = PlayerPos;

	if (!Attacked && !m_PlayingEffect)
		m_DidAction = Move();

	return true;
}

void cBot::CameraUpdate()
{
	cCamera* Camera = (cCamera*)m_Camera;

	m_Position.x = m_OnMapPos.x * cMap::m_tile_size;
	m_Position.y = m_OnMapPos.y * cMap::m_tile_size;
	m_Sprite.position = m_Position - Camera->GetDrawBasePos();
	if (m_MapObj)
		m_Sprite.visible = m_MapObj->IsTileVisible(m_OnMapPos.x, m_OnMapPos.y);
}

bool cBot::Move()
{
	CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
	aqua::CVector2 Pos = aqua::CVector2::ZERO;
	bool Moved = false;
	
	for (int i = 0; i < 4; i++)
	{
		Pos = m_OnMapPos;
		m_MoveTo = (IUnit::DIRECTION)(rand() % (int)IUnit::DIRECTION::COUNT);

		switch (m_MoveTo)
		{
		case IUnit::DIRECTION::DUMMY:
			return false;
			break;
		case IUnit::DIRECTION::NORTH:
			Pos.y -= 1;
			break;
		case IUnit::DIRECTION::SOUTH:
			Pos.y += 1;
			break;
		case IUnit::DIRECTION::EAST:
			Pos.x -= 1;
			break;
		case IUnit::DIRECTION::WEST:
			Pos.x += 1;
			break;
		}
		if (m_MapObj->IsWalkableTile(Pos.x, Pos.y) && UnitMgr->HasSpace(Pos))
		{
			Moved = true;
			break;
		}
	}
	if (Moved)
	{
		UnitMgr->SetMovedPos(m_OnMapPos, Pos);
		m_OnMapPos = Pos;
		CameraUpdate();
	}
	return true;
}

bool cBot::Attack(aqua::CVector2 pos)
{
	if (m_PlayingEffect)
		if (!PlayEffect()) return false;
	return IUnit::Attack(pos);
}
