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

	void CalcStatus(bool reset_param = false) override;

	bool Action() override;

private:
	bool Wait() override;

	bool Move() override;

	bool Attack(aqua::CVector2 pos) override;

	bool Item(std::int8_t slot, ITEM_USE_MODE mode = ITEM_USE_MODE::USE) override;

	bool EquipmentChange(std::uint16_t id);

	float m_InputTimer;
	aqua::CVector2 m_TargetTile;
	aqua::CVector2 m_StairPos;
	aqua::CLinePrimitive m_Line;
	aqua::CBoxPrimitive m_Box;
	aqua::IGameObject* m_StatObj;
};