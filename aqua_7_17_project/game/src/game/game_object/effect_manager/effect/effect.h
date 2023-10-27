#pragma once
#include "aqua.h"
#include "..\effect_id.h"

class IEffect :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	IEffect(aqua::IGameObject* parent, std::string name);

	//�f�X�g���N�^
	~IEffect() = default;

	//������
	virtual void Initialize(aqua::CVector2 posA, aqua::CVector2 posB);

	//�X�V
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

	//���
	virtual void Finalize() override;

	//�G�t�F�N�g�Đ������ǂ���
	bool EffectPlaying();

protected:
	aqua::CVector2 m_PositionA;
	aqua::CVector2 m_PositionB;
	IGameObject* m_Camera;
	aqua::CLinePrimitive m_Line;
	float m_Timer;
};