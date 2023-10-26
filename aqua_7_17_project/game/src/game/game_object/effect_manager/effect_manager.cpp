#include "effect_manager.h"
#include "effect_with_sound_def.h"
#include "effect/melee/melee.h"
#include "effect/gunshot/gunshot.h"
#include "effect/cannon/cannon.h"

cEffectManager::cEffectManager(aqua::IGameObject* parent)
	: IGameObject(parent,"EffectManager")
	, m_SoundManager(nullptr)
{
}

void cEffectManager::Initialize()
{
	m_SoundManager = aqua::FindGameObject("SoundManager");
}

void cEffectManager::Update()
{
	IGameObject::Update();
}

void cEffectManager::Draw()
{
	IGameObject::Draw();
}

void cEffectManager::Finalize()
{
	IGameObject::Finalize();
}

IEffect* cEffectManager::CreateEffect(EFFECT_ID id, aqua::CVector2 posA, aqua::CVector2 posB)
{
	IEffect* Effect = nullptr;

	switch (id)
	{
	case EFFECT_ID::MELEE:		Effect = aqua::CreateGameObject<cEffectMelee>(this); break;
	case EFFECT_ID::GUNSHOT:	Effect = aqua::CreateGameObject<cEffectGunshot>(this); break;
	case EFFECT_ID::CANNON:	Effect = aqua::CreateGameObject<cEffectCannon>(this); break;
	}
	if (Effect) Effect->Initialize(posA, posB);

	return Effect;
}
