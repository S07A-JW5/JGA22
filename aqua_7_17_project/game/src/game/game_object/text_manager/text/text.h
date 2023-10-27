#pragma once

#include "aqua.h"

class cText : public aqua::IGameObject
{
public:
	enum class ANCHOR_POS
	{
		LEFT_TOP,	//����
		TOP,		//��
		RIGHT_TOP,	//�E��
		LEFT,		//��
		CENTER,		//����
		RIGHT,		//�E
		LEFT_BOTTOM,//����
		BOTTOM,		//��
		RIGHT_BOTTOM//�E��
	};

	//�R���X�g���N�^
	cText(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cText() = default;

	//������
	void Initialize(const aqua::CVector2& pos, const std::string& text,
		const ANCHOR_POS& anchor, const int& font_size, bool with_window);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//����Ԑؑ�
	void SetVisible(bool visible);

	//���T�C�Y�擾
	int GetWidth();

	//�c�T�C�Y�擾
	int GetHeight();

	//�ʒu�ݒ�
	void SetPosition(const aqua::CVector2& pos);

	//���͐ݒ�
	void SetText(std::string text);

private:
	//����������s�ŕ�����
	std::vector<std::string> SeparateText();

	uint8_t m_Rows; //�s��

	aqua::CVector2 m_Position; //�\���ʒu

	int m_Width; //���T�C�Y

	int m_Height; //�c�T�C�Y

	int m_FontSize; //�t�H���g�T�C�Y

	ANCHOR_POS m_Anchor; //��_

	std::string m_String; //������

	aqua::CLabel* m_Text; //�`�敶����z��

	IGameObject* m_Window; //���͕\���p�E�B���h�E
};