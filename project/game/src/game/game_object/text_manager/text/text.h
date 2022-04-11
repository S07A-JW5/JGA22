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

	cText(aqua::IGameObject* parent);

	~cText() = default;

	void Initialize(const aqua::CVector2& pos, const std::string& text,
		const ANCHOR_POS& anchor, const int& font_size, bool with_window);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetVisible(bool visible);

	int GetWidth();

	int GetHeight();

	void SetPosition(const aqua::CVector2& pos);

	void SetText(std::string text);

private:
	std::vector<std::string> SeparateText();

	std::uint8_t m_Rows;

	aqua::CVector2 m_Position;

	int m_Width;

	int m_Height;

	int m_FontSize;

	ANCHOR_POS m_Anchor;

	std::string m_String;

	aqua::CLabel* m_Text;

	aqua::IGameObject* m_Window;
};