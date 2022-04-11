#pragma once

#include "aqua.h"
#include "../unit.h"

class cBot :public IUnit
{
public:
	cBot(aqua::IGameObject* parent);

	~cBot() = default;

private:
};