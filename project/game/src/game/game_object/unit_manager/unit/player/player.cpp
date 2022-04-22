#include "player.h"
#include "../../unit_manager.h"
#include "game/game_object/camera/camera.h"
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
	m_Line.Setup(aqua::CVector2::ZERO, aqua::CVector2::ZERO, 0xc07fff00);
	m_Box.Setup(aqua::CVector2::ZERO, 14, 14, 0xffff0000, false, 1);
}

void cPlayer::Update()
{
	m_Line.visible = aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT);
	m_Line.pointA = aqua::CVector2(cCamera::m_draw_width / 2, cCamera::m_draw_height / 2);

	aqua::CPoint Point = aqua::mouse::GetCursorPos();
	aqua::CVector2 PointedTile = m_MapObj->GetPointedTile(Point);

	m_Line.pointB.x = Point.x;
	m_Line.pointB.y = Point.y;

	m_Box.position = 
		(PointedTile * cMap::m_tile_size) - ((cCamera*)m_Camera)->GetDrawBasePos();
	m_Box.position.x += m_Box.thickness;
	m_Box.position.y += m_Box.thickness;

	m_DesiredAction = ACTION::DUMMY;

	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	{
		m_DesiredAction = ACTION::ATTACK;
		m_TargetTile = PointedTile;
	}
	else
	{
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
		{
			m_DesiredAction = ACTION::WAIT;
		}
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
	}

	if (m_DesiredAction != ACTION::DUMMY)
		if(Action())
		{
			m_Batt = max(min(m_Batt + m_EnergyFlow, m_MaxBatt), 0);
			m_Heat = max(min(m_Heat + m_HeatFlow, 999), m_BaseHeat);
		}

	CameraUpdate();	
}

void cPlayer::CameraUpdate()
{
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
	m_Line.Draw();
	m_Box.Draw();
}

void cPlayer::Finalize()
{
	m_Sprite.Delete();
}

void cPlayer::SetStairPosition(aqua::CVector2 pos)
{
	m_StairPos = pos;
}

void cPlayer::CalcStatus()
{
	IUnit::CalcStatus();
	cUIManager* UIMgr = (cUIManager*)m_UIManager;
	UIMgr->CreateStatusUI(this, m_Name, m_Life, m_MaxLife, m_HeatFlow, m_Heat, m_BaseHeat, m_Weight, m_Support, m_EnergyFlow, m_Batt, m_MaxBatt, m_Parts, m_MaxParts, m_Ammo, m_MaxAmmo, m_Resist, m_Protection);
}

bool cPlayer::Action()
{
	if (m_DidAction) return true;
	bool Act = false;

	switch (m_DesiredAction)
	{
	case IUnit::ACTION::WAIT:
		Act = Wait();
		break;
	case IUnit::ACTION::MOVE:
		Act = Move();
		break;
	case IUnit::ACTION::ATTACK:
		Act = Attack(m_TargetTile);
		break;
	}
	m_DidAction = Act;
	return m_DidAction;
}

bool cPlayer::Wait()
{
	return true;
}

bool cPlayer::Move()
{
	CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
	aqua::CVector2 Pos = m_OnMapPos;
	bool Moved = false;

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
		Pos.x += 1;
		break;
	case IUnit::DIRECTION::WEST:
		Pos.x -= 1;
		break;
	}
	if (m_MapObj->IsWalkableTile(Pos.x, Pos.y))
	{
		if (UnitMgr->HasSpace(Pos))
		{
			Moved = true;
			m_OnMapPos = Pos;
			UnitMgr->SetPlayerPos(m_OnMapPos);
			m_MapObj->SetMapped(m_OnMapPos, 8);
			if (m_OnMapPos == m_StairPos)
			{
				m_Life = m_MaxLife;
				m_Ammo = min(m_Ammo + max(m_MaxAmmo / 10, 1), m_MaxAmmo);
				UnitMgr->MapGeneration();
			}
		}
		else
		{
			return Attack(Pos);
		}
	}
	return Moved;
}

bool cPlayer::Attack(aqua::CVector2 pos)
{
	if (!m_MapObj->IsTileVisible(pos.x, pos.y))return false;
	return IUnit::Attack(pos);
}
