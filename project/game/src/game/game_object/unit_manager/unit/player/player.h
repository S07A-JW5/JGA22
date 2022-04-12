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

	void SetStairPosition(aqua::CVector2 pos);

private:
	aqua::CSprite m_Sight;
	aqua::CVector2 m_StairPos;
};