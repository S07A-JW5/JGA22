#pragma once

#include "aqua.h"
#include <functional>

class cButton :public aqua::IGameObject
{
public:
	using ButtonFunc = std::function<void(void)>;

	enum class BUTTON_TYPE
	{
		BUTTON,//�����Ă����
		TOGGLE,//�g�O����
		SWITCH,//�����ꂽ�u�Ԃ̂�
	};


	//�R���X�g���N�^
	cButton(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cButton() = default;

	//������
	void Initialize(ButtonFunc button_function, const aqua::CVector2 & pos,
		BUTTON_TYPE type, const std::string & name, const int& width, const int& height,
		const int& font_size, const std::string & description, const bool& select);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//�}�E�X�J�[�\�������킹�Ă��邩
	bool MouseOvered();

	//�{�^����������Ă��邩
	bool Pressed();

private:
	static const int m_space;	//�{�^���摜�̊p�̃T�C�Y
	static const int m_size;	//�{�^���摜�̃T�C�Y

	aqua::CVector2 m_Position; //�{�^���\���ʒu

	int m_Height;	//�{�^���c�T�C�Y
	int m_Width;	//�{�^�����T�C�Y

	aqua::CSprite m_Sprite[9];	//�{�^���X�v���C�g
	aqua::CLabel m_Name;	//�{�^����

	std::string m_DescText;	//�{�^��������
	IGameObject* m_DescObj;	//�{�^���������e�L�X�g�{�b�N�X

	float m_Timer;	//�������e�L�X�g�{�b�N�X�\���^�C�}�[

	bool m_Switch;	//�@�\���Ă��邩
	bool m_MouseOver;//�}�E�X�J�[�\�������킹�Ă��邩

	bool m_IsDiscreteButton;//�ʂ̃{�^���ł��邩

	BUTTON_TYPE m_ButtonType;//�{�^���^�C�v

	ButtonFunc m_ButtonFunction;//�{�^��ON���̏���
};