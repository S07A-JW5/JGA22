#pragma once

#include "aqua.h"
#include "text/text.h"

class CTextManager : public aqua::IGameObject
{
public:
	enum class DISPLAY_MODE
	{
		STANDARD,	//通常
		NO_WINDOW,	//ウィンドウ無し
		BATTLE,		//戦闘時用
	};

	CTextManager(aqua::IGameObject* parent);

	~CTextManager(void) = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetText(int rows, std::string text);

	void SetText(std::string text);

	void ClearText();

	void SetMode(DISPLAY_MODE mode);

	void WindowCheck();

	cText* CreateText(const aqua::CVector2& pos, const std::string& text, const int& font_size = 24, bool with_window = true);

	cText* CreateText(const aqua::CVector2& pos, const std::string& text,
		const cText::ANCHOR_POS& anchor, const int& font_size = 24, bool with_window = true);

private:
	static const int m_rows;

	static const int m_font_size;

	static const int m_text_window_height;

	static const aqua::CVector2 m_text_window_pos;

	std::string m_String;

	aqua::CLabel* m_Text;

	bool m_TextDisplay;

	int m_TextIndex;

	std::uint8_t m_Rows;

	float m_Timer;

	DISPLAY_MODE m_DisplayMode;

	aqua::IGameObject* m_Window;

	aqua::IGameObject* m_UIManager;
};