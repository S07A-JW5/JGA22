#pragma once
#include "aqua.h"
#include "effect_id.h"
#include "effect/effect.h"

class cEffectManager :public aqua::IGameObject
{
public:
	cEffectManager(aqua::IGameObject* parent);

	~cEffectManager() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	IEffect* CreateEffect(EFFECT_ID id, aqua::CVector2 posA, aqua::CVector2 posB);

private:
	IGameObject* m_SoundMgr;
};