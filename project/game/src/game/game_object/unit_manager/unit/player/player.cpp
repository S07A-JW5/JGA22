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
	m_LifeText.Create(16);
	m_LifeText.color = 0xffffffff;
	m_BattText.Create(16);
	m_BattText.color = 0xffffffff;
	m_HeatText.Create(16);
	m_HeatText.color = 0xffffffff;
	m_LifeText.position.y = 10;
	m_BattText.position.y = 30;
	m_HeatText.position.y = 50;
	m_LifeText.position.x = m_BattText.position.x = m_HeatText.position.x = 730;
}

void cPlayer::Update()
{
	m_LifeText.text = "Life: " + std::to_string(m_Life) + " / " + std::to_string(m_MaxLife);
	m_HeatText.text = "Heat: " + std::to_string(m_Heat) + " (" + std::to_string(m_HeatFlow)+")";
	m_BattText.text = "Batt: " + std::to_string(m_Batt) + " / " + std::to_string(m_MaxBatt) + " (" + std::to_string(m_EnergyFlow)+")";

	m_Line.visible = aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT);
	m_Line.pointA = aqua::CVector2(cCamera::m_draw_width / 2, cCamera::m_draw_height / 2);
	aqua::CPoint Point = aqua::mouse::GetCursorPos();
	m_Line.pointB.x = Point.x;
	m_Line.pointB.y = Point.y;

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
	m_Sight.Draw();
	m_Line.Draw();

	m_LifeText.Draw();
	m_BattText.Draw();
	m_HeatText.Draw();
}

void cPlayer::Finalize()
{
	m_Sprite.Delete();
	m_Sight.Delete();

	m_LifeText.Delete();
	m_BattText.Delete();
	m_HeatText.Delete();
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
		m_MapObj->SetMapped(m_OnMapPos, 8);
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
