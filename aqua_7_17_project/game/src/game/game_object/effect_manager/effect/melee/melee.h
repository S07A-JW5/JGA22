#pragma once
#include "../effect.h"

class cEffectMelee :public IEffect
{
public:

	//�R���X�g���N�^
	cEffectMelee(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cEffectMelee() = default;

	//������
	void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

private:
};