#pragma once
#include "aqua.h"

class cValue :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cValue(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cValue() = default;

	//������
	void Initialize(aqua::CVector2 position, int value,int max, int size, bool display_max);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//�l�ݒ�
	void SetNum(int value);

	//�l�擾
	int GetNum(bool calcvalue = false);

	//�l�擾
	float GetFloatNum();

	//�l��0���ǂ���
	bool IsZero();

	//�\���l���ݒ�l�ɂȂ�����
	bool Complete();

private:
	int m_Max;		//�ő�l
	int m_Value;	//���݂̐��l
	int m_CalcValue;//�v�Z�ςݐ��l

	int m_PrevValue;//�O�t���[���ł̒l

	aqua::CLabel m_ValueLabel;//�l�\��

	aqua::CLabel m_MaxLabel;//�ő�l�\��
};