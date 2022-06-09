#pragma once
#include "../effect.h"

class cEffectCannon :public IEffect
{
public:
	cEffectCannon(aqua::IGameObject* parent);

	~cEffectCannon() = default;

	void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	aqua::CBoxPrimitive m_Box;
	aqua::CVector2 m_Velocity;
	aqua::CVector2 m_BoxPos;
	aqua::CVector2 m_PrevPos;
};