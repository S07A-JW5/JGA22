#include "bot.h"
#include "../../unit_manager.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/ui_manager/ui_manager.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/sound_manager/sound_manager.h"
#include <vector>

cBot::cBot(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
{
}

void cBot::Initialize()
{
	IUnit::Initialize();
	m_Sprite.visible = false;
}

void cBot::Update()
{
	cCamera* Camera = (cCamera*)m_Camera;

	m_Position.x = m_OnMapPos.x * cMap::m_tile_size;
	m_Position.y = m_OnMapPos.y * cMap::m_tile_size;
	m_Sprite.position = m_Position - Camera->GetDrawBasePos();
	if (m_MapObj)
		m_Sprite.visible = m_MapObj->IsTileVisible(m_OnMapPos.x, m_OnMapPos.y);
}

bool cBot::Action()
{
	CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
	if (UnitMgr->IsPlayerNearBy(m_OnMapPos))
	{
		Attack(UnitMgr->GetPlayerPos());
	}
	return true;
}

bool cBot::Wait()
{
	return false;
}

bool cBot::Attack(aqua::CVector2 pos)
{
	return IUnit::Attack(pos);
}
