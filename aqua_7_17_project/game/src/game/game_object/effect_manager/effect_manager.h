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

	//�G�t�F�N�g�Đ�
	IEffect* CreateEffect(EFFECT_ID id, aqua::CVector2 posA, aqua::CVector2 posB);

private:
	IGameObject* m_SoundManager; //�T�E���h�}�l�[�W���[
};