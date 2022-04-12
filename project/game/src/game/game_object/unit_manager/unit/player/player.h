#pragma once

#include "aqua.h"
#include "../unit.h"

class cPlayer :public IUnit
{
public:
	cPlayer(aqua::IGameObject* parent);

	~cPlayer() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
};