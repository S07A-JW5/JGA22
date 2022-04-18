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

	void CameraUpdate();

	void Draw() override;

	void Finalize() override;

	void SetStairPosition(aqua::CVector2 pos);

	bool Action() override;

private:
	bool Wait() override;

	bool Move() override;

	bool Attack() override;

	aqua::CSprite m_Sight;
	aqua::CVector2 m_StairPos;
	aqua::CLinePrimitive m_Line;

	aqua::CLabel m_LifeText;
	aqua::CLabel m_BattText;
	aqua::CLabel m_HeatText;
};