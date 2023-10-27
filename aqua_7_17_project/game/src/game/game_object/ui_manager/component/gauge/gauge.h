#pragma once
#include "aqua.h"

class cGauge :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cGauge(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cGauge() = default;

	//������
	void Initialize(aqua::CVector2 position, int value, int limit, int width, int height, bool mirror, bool has_bg, aqua::IGameObject* sync_obj);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//���ݒl�ݒ�
	void SetNum(int value);

	//�ő�l�ݒ�
	void SetMax(int value);

private:
	static const int m_space;	//�摜�̊p�̃T�C�Y
	static const int m_size;	//�摜�T�C�Y

	int m_Max;			//�ő�l
	float m_Value;		//���݂̐��l
	float m_CalcValue;	//�v�Z�ςݐ��l
	float m_Timer;		//�^�C�}�[

	float m_PrevValue; //�O�̒l

	int m_Width; //���T�C�Y

	int m_Height; //�c�T�C�Y

	bool m_Mirror; //�\���������]

	aqua::IGameObject* m_SyncObject; //�A���I�u�W�F�N�g(���lUI)

	aqua::CSprite m_Gauge[2]; //�Q�[�W�X�v���C�g

	aqua::CSprite m_Background[9]; //�Q�[�W�w�i
};