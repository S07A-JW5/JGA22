#pragma once

#include "aqua.h"
#include "text/text.h"

class CTextManager : public aqua::IGameObject
{
public:
	CTextManager(aqua::IGameObject* parent);

	~CTextManager(void) = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetText(int rows, std::string text);

	void SetText(std::string text);

	void EnterText(std::string text);

	void ClearText();

	void WindowCheck();

	cText* CreateText(const aqua::CVector2& pos, const std::string& text, const int& font_size = 24, bool with_window = true);

	cText* CreateText(const aqua::CVector2& pos, const std::string& text,
		const cText::ANCHOR_POS& anchor, const int& font_size = 24, bool with_window = true);

private:
	static const int m_rows;

	static const int m_font_size;

	static const int m_text_window_width;

	static const int m_text_window_height;

	static const aqua::CVector2 m_text_window_pos;

	std::string m_DisplayText;

	std::list<std::string> m_TextList;

	aqua::CLabel* m_Text;

	bool m_TextDisplay;

	int m_TextIndex;

	std::uint8_t m_Rows;

	float m_Timer;

	aqua::IGameObject* m_Window;

	aqua::IGameObject* m_UIManager;
};