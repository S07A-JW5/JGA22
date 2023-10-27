#pragma once
#include "aqua.h"
#include "effect_id.h"
#include "effect/effect.h"

class cEffectManager :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cEffectManager(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cEffectManager() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//�G�t�F�N�g�Đ�
	IEffect* CreateEffect(EFFECT_ID id, aqua::CVector2 posA, aqua::CVector2 posB);

private:
	IGameObject* m_SoundManager; //�T�E���h�}�l�[�W���[
};