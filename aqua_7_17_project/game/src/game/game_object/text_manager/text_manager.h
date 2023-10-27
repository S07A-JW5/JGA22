#pragma once

#include "aqua.h"
#include "text/text.h"

class cTextManager : public aqua::IGameObject
{
public:

	//コンストラクタ
	cTextManager(aqua::IGameObject* parent);

	//デストラクタ
	~cTextManager(void) = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//可視状態切替
	void SetVisible(bool visible);

	//文章追加
	void EnterText(std::string text);

	//文章クリア
	void ClearText();

	//テキスト表示作成
	cText* CreateText(const aqua::CVector2& pos, const std::string& text, const int& font_size = 24, bool with_window = true);

	//テキスト表示作成
	cText* CreateText(const aqua::CVector2& pos, const std::string& text,
		const cText::ANCHOR_POS& anchor, const int& font_size = 24, bool with_window = true);

	std::string m_Temp;

private:

	//文章表示用ウィンドウが存在するか確認 なければ生成
	void WindowCheck();

	static const int m_rows; //表示行数

	static const int m_font_size; //フォントサイズ

	static const int m_text_window_width; //文章表示用ウィンドウ横サイズ

	static const int m_text_window_height; //文章表示用ウィンドウ縦サイズ

	static const aqua::CVector2 m_text_window_pos; //文章表示用ウィンドウ表示位置

	std::string m_DisplayText; //現在処理中の文字列

	std::list<std::string> m_TextList; //処理待ち文字列リスト

	aqua::CLabel* m_Text; //描画文字列配列

	bool m_TextDisplay; //処理中フラグ

	int m_TextIndex; //処理中の文字列の位置

	uint8_t m_Rows; //現在処理中の行

	float m_Timer; //タイマー

	IGameObject* m_Window; //文章表示用ウィンドウ

	IGameObject* m_UIManager; //UIマネージャのポインタ
};