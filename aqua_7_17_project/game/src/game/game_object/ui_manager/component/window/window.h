#pragma once

#include "aqua.h"

class cWindow :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cWindow(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cWindow() = default;

	//������
	void Initialize(const aqua::CVector2& pos, const int& width = 64, const int& height = 64, const unsigned int& color = 0xffffffff);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//����Ԑؑ�
	void SetVisible(bool visible);

	//�ʒu�ݒ�
	void SetPosition(const aqua::CVector2& pos);

	//�ʒu�擾
	aqua::CVector2 GetPosition();

	static const int m_space; //�摜�̊p�̃T�C�Y

private:
	static const int m_size; //�摜�T�C�Y

	aqua::CVector2 m_Position; //�ʒu

	int m_Height;	//�E�B���h�E����
	int m_Width;	//�E�B���h�E��

	aqua::CSprite m_Sprite[9]; //�E�B���h�E�X�v���C�g
};