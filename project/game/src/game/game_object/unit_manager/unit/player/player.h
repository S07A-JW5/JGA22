#pragma once

#include "aqua.h"
#include "../unit.h"

class cPlayer :public IUnit
{
public:
	cPlayer(aqua::IGameObject* parent);

	~cPlayer() = default;

	void Initialize() override;

	void Draw() override;

	void Finalize() override;

	//void SetState(STATE state) override;

	//void Command() override;

	//void Action() override;

	//void Attack() override;

	//void Cure() override;

	//void Resign() override;

	//int ReceiveDamage(int damage, int defence, std::uint8_t attribute, bool get_damaged, bool special, bool pp_damage) override;

private:
};