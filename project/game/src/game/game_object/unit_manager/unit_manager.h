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

	void LoadDir();

	void Clear();

	int DealDamage(int damage, int defence, std::uint8_t attribute, bool get_damaged, bool special, int offence_dex = 0, int damage_cap = 9999, bool pp_damage = false, bool from_rival = false);

	bool Command();

	bool Action();

	bool RoundFinished();

	bool BattleFinished();
	
	bool IsBattleFinish();

private:
	aqua::IGameObject* m_TextManager;

};
