#pragma once
#include "../effect.h"

class cEffectMelee :public IEffect
{
public:
	cEffectMelee(aqua::IGameObject* parent);

	~cEffectMelee() = default;

	void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
};