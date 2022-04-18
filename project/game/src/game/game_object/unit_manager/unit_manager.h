#pragma once

#include "aqua.h"
#include "unit/unit.h"
#include "unit/unit_id.h"
#include "unit/player/player.h"
#include "unit/npc/bot.h"
#include <vector>

class CUnitManager : public aqua::IGameObject
{
public:
	CUnitManager(aqua::IGameObject* parent);

	~CUnitManager(void) = default;

	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	void Clear();

	void Create();

	void MapGeneration();

	bool IsPlayerNearBy(aqua::CVector2 pos);

	void SetPlayerPos(aqua::CVector2 pos);

private:
	aqua::IGameObject* m_TextManager;
	cPlayer* m_Player;
	std::vector<cBot*> m_NPCs;
	aqua::IGameObject* m_MapGenerator;
	bool m_MapGenerated;
	aqua::CVector2 m_PlayerPos;
};