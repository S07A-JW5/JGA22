#pragma once
#include "../effect.h"

class cEffectGunshot :public IEffect
{
public:
	cEffectGunshot(aqua::IGameObject* parent);

	~cEffectGunshot() = default;

	void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
};