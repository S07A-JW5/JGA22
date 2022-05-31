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
	{
		m_LastSeenTargetPos = PlayerPos;
	}

	if (!Attacked && !m_PlayingEffect)
		m_DidAction = Move();

	m_TargetVision = (UnitMgr->BetweenPlayer(m_OnMapPos) <= m_SightRange &&
		!m_MapObj->HitWall(m_OnMapPos, PlayerPos));
	if (m_TargetVision)
	{
		m_LastSeenTargetPos = PlayerPos;
	}

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
	aqua::CVector2 Diff = aqua::CVector2::ZERO;
	IUnit::DIRECTION Dir = IUnit::DIRECTION::DUMMY;
	bool Moved = false;
	
	if (m_LastSeenTargetPos==aqua::CVector2::ZERO)
	{
		for (int i = 0; i < 4; i++)
		{
			m_MoveTo = (IUnit::DIRECTION)(rand() % (int)IUnit::DIRECTION::COUNT);

			if (CanMove())
			{
				Moved = true;
				break;
			}
		}
	}
	else
	{
		Diff = m_LastSeenTargetPos - m_OnMapPos;
		if (abs(Diff.x) > 0 && abs(Diff.y) > 0)
		{
			if (Diff.x < 0)
			{
				if (Diff.y < 0)
					m_MoveTo = IUnit::DIRECTION::NORTH_WEST;
				else if (Diff.y > 0)
					m_MoveTo = IUnit::DIRECTION::SOUTH_WEST;
			}
			else if (Diff.x > 0)
			{
				if (Diff.y < 0)
					m_MoveTo = IUnit::DIRECTION::NORTH_EAST;
				else if (Diff.y > 0)
					m_MoveTo = IUnit::DIRECTION::SOUTH_EAST;
			}
			if (CanMove())
			{
				Moved = true;
			}
		}
		if (!Moved)
		{
			if (abs(Diff.x) > abs(Diff.y))
			{
				if (Diff.x > 0)
					m_MoveTo = IUnit::DIRECTION::EAST;
				else if (Diff.x < 0)
					m_MoveTo = IUnit::DIRECTION::WEST;
			}
			else
			{
				if (Diff.y > 0)
					m_MoveTo = IUnit::DIRECTION::SOUTH;
				else if (Diff.y < 0)
					m_MoveTo = IUnit::DIRECTION::NORTH;
			}
			if (CanMove())
			{
				Moved = true;
			}
			else
			{
				m_MoveTo = Dir;
				if (CanMove())
					Moved = true;
				else
					for (int i = 0; i < 4; i++)
					{
						m_MoveTo = (IUnit::DIRECTION)(rand() % (int)IUnit::DIRECTION::COUNT);

						if (CanMove())
						{
							Moved = true;
							break;
						}
					}
			}
		}
	}
	if (Moved)
	{
		Pos = GetMovedPos();
		UnitMgr->SetMovedPos(m_OnMapPos, Pos);
		m_OnMapPos = Pos;
		CameraUpdate();
		if (m_LastSeenTargetPos != aqua::CVector2::ZERO && m_LastSeenTargetPos == m_OnMapPos)
			m_LastSeenTargetPos = aqua::CVector2::ZERO;
	}
	return true;
}

bool cBot::Attack(aqua::CVector2 pos)
{
	if (m_PlayingEffect)
		if (!PlayEffect()) return false;
	return IUnit::Attack(pos);
}
