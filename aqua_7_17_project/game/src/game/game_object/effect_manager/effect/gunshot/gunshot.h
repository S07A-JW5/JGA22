#pragma once
#include "../effect.h"

class cEffectGunshot :public IEffect
{
public:

	//�R���X�g���N�^
	cEffectGunshot(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cEffectGunshot() = default;

	//������
	void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

private:

	aqua::CLinePrimitive m_Line2;
};