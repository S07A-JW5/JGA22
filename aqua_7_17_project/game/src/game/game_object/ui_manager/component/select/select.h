#pragma once

#include "aqua.h"
#include "../button/button.h"
#include <vector>

class cSelection :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cSelection(aqua::IGameObject* parent);
	
	//�f�X�g���N�^
	~cSelection() = default;

	//������
	void Initialize(std::vector<int> number, std::vector<std::string>name, std::vector<std::string>desc, aqua::CVector2 pos);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//�I�����ꂽ��
	bool Pressed();

	//�l�擾
	int GetNum();

private:
	static const int m_selection_per_page; //�P�y�[�W������̑I�����\����
	static const int m_width;	//�E�B���h�E��
	static const int m_height;	//�E�B���h�E����

	aqua::CVector2 m_Position; //�E�B���h�E�ʒu

	int m_PrevFramePage; //�O�t���[���ł̕\���y�[�W
	int m_Page; //�\�����y�[�W
	int m_MaxPage; //���v�y�[�W��

	bool m_ButtonPressed; //�I�����{�^���������ꂽ��

	std::vector<int> m_Number; //�I�����ԍ��z��
	std::vector<std::string> m_DescText; //�������z��

	int m_CurNum; //���݂̑I�����ԍ�

	IGameObject* m_UIManager; //UI�}�l�[�W���̃|�C���^

	IGameObject* m_PageTextWindow; //���݃y�[�W���w�i
	IGameObject* m_PageTextObj; //���݃y�[�W���\��
	IGameObject* m_DescWindow; //�I�����������w�i
	IGameObject* m_DescObj; //�I�����������\��
	IGameObject* m_Window; //�E�B���h�E
	cButton* m_NextPage; //�u�O�̃y�[�W�v�{�^��
	cButton* m_PrevPage; //�u���̃y�[�W�v�{�^��
	std::vector<cButton*> m_ButtonList; //�I�����{�^���z��
};