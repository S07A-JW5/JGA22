#pragma once

#include "aqua.h"

class cText : public aqua::IGameObject
{
public:
	enum class ANCHOR_POS
	{
		LEFT_TOP,	//左上
		TOP,		//上
		RIGHT_TOP,	//右上
		LEFT,		//左
		CENTER,		//中央
		RIGHT,		//右
		LEFT_BOTTOM,//左下
		BOTTOM,		//下
		RIGHT_BOTTOM//右下
	};

	//コンストラクタ
	cText(aqua::IGameObject* parent);

	//デストラクタ
	~cText() = default;

	//初期化
	void Initialize(const aqua::CVector2& pos, const std::string& text,
		const ANCHOR_POS& anchor, const int& font_size, bool with_window);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//可視状態切替
	void SetVisible(bool visible);

	//横サイズ取得
	int GetWidth();

	//縦サイズ取得
	int GetHeight();

	//位置設定
	void SetPosition(const aqua::CVector2& pos);

	//文章設定
	void SetText(std::string text);

private:
	//文字列を改行で分ける
	std::vector<std::string> SeparateText();

	uint8_t m_Rows; //行数

	aqua::CVector2 m_Position; //表示位置

	int m_Width; //横サイズ

	int m_Height; //縦サイズ

	int m_FontSize; //フォントサイズ

	ANCHOR_POS m_Anchor; //基準点

	std::string m_String; //文字列

	aqua::CLabel* m_Text; //描画文字列配列

	IGameObject* m_Window; //文章表示用ウィンドウ
};