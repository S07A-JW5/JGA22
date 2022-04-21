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

	void Create(std::uint16_t id, int x_pos, int y_pos);

	void MapGeneration();

	bool IsPlayerNearBy(aqua::CVector2 pos);

	bool HasSpace(aqua::CVector2 pos);

	bool Attack(aqua::CVector2 target_pos, int damage, IUnit::DAMAGE_TYPE type);

	void SetPlayerPos(aqua::CVector2 pos);

	aqua::CVector2 GetPlayerPos();

	void SetMapSize(int width, int height);

private:
	aqua::IGameObject* m_TextManager;
	cPlayer* m_Player;
	std::uint8_t m_Floor;
	std::vector<cBot*> m_NPCs;
	int** m_UnitPos;
	std::uint8_t m_Width;
	std::uint8_t m_Height;
	aqua::IGameObject* m_MapGenerator;
	aqua::IGameObject* m_MapObj;
	bool m_MapGenerated;
	aqua::CVector2 m_PlayerPos;
};
