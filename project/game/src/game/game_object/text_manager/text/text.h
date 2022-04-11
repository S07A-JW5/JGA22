#pragma once

#include "aqua.h"

class cText : public aqua::IGameObject
{
public:
	enum class ANCHOR_POS
	{
		LEFT_TOP,	//ç∂è„
		TOP,		//è„
		RIGHT_TOP,	//âEè„
		LEFT,		//ç∂
		CENTER,		//íÜâõ
		RIGHT,		//âE
		LEFT_BOTTOM,//ç∂â∫
		BOTTOM,		//â∫
		RIGHT_BOTTOM//âEâ∫
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