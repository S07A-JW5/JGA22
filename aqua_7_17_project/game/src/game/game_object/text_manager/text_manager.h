#pragma once

#include "aqua.h"
#include "text/text.h"

class cTextManager : public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cTextManager(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cTextManager(void) = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//����Ԑؑ�
	void SetVisible(bool visible);

	//���͒ǉ�
	void EnterText(std::string text);

	//���̓N���A
	void ClearText();

	//�e�L�X�g�\���쐬
	cText* CreateText(const aqua::CVector2& pos, const std::string& text, const int& font_size = 24, bool with_window = true);

	//�e�L�X�g�\���쐬
	cText* CreateText(const aqua::CVector2& pos, const std::string& text,
		const cText::ANCHOR_POS& anchor, const int& font_size = 24, bool with_window = true);

	std::string m_Temp;

private:

	//���͕\���p�E�B���h�E�����݂��邩�m�F �Ȃ���ΐ���
	void WindowCheck();

	static const int m_rows; //�\���s��

	static const int m_font_size; //�t�H���g�T�C�Y

	static const int m_text_window_width; //���͕\���p�E�B���h�E���T�C�Y

	static const int m_text_window_height; //���͕\���p�E�B���h�E�c�T�C�Y

	static const aqua::CVector2 m_text_window_pos; //���͕\���p�E�B���h�E�\���ʒu

	std::string m_DisplayText; //���ݏ������̕�����

	std::list<std::string> m_TextList; //�����҂������񃊃X�g

	aqua::CLabel* m_Text; //�`�敶����z��

	bool m_TextDisplay; //�������t���O

	int m_TextIndex; //�������̕�����̈ʒu

	uint8_t m_Rows; //���ݏ������̍s

	float m_Timer; //�^�C�}�[

	IGameObject* m_Window; //���͕\���p�E�B���h�E

	IGameObject* m_UIManager; //UI�}�l�[�W���̃|�C���^
};