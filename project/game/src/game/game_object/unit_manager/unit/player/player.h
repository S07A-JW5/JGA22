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

	void CalcStatus() override;

	bool Action() override;

private:
	bool Wait() override;

	bool Move() override;

	bool Attack(aqua::CVector2 pos) override;

	aqua::CVector2 m_TargetTile;
	aqua::CVector2 m_StairPos;
	aqua::CLinePrimitive m_Line;
	aqua::CBoxPrimitive m_Box;
};