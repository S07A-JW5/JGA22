#pragma once

#include "aqua.h"
#include <functional>

class cButton :public aqua::IGameObject
{
public:
	using ButtonFunc = std::function<void(void)>;

	enum class BUTTON_TYPE
	{
		BUTTON,//押している間
		TOGGLE,//トグル式
		SWITCH,//放された瞬間のみ
	};


	//コンストラクタ
	cButton(aqua::IGameObject* parent);

	//デストラクタ
	~cButton() = default;

	//初期化
	void Initialize(ButtonFunc button_function, const aqua::CVector2 & pos,
		BUTTON_TYPE type, const std::string & name, const int& width, const int& height,
		const int& font_size, const std::string & description, const bool& select);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//マウスカーソルを合わせているか
	bool MouseOvered();

	//ボタンが押されているか
	bool Pressed();

private:
	static const int m_space;	//ボタン画像の角のサイズ
	static const int m_size;	//ボタン画像のサイズ

	aqua::CVector2 m_Position; //ボタン表示位置

	int m_Height;	//ボタン縦サイズ
	int m_Width;	//ボタン横サイズ

	aqua::CSprite m_Sprite[9];	//ボタンスプライト
	aqua::CLabel m_Name;	//ボタン名

	std::string m_DescText;	//ボタン説明文
	IGameObject* m_DescObj;	//ボタン説明文テキストボックス

	float m_Timer;	//説明文テキストボックス表示タイマー

	bool m_Switch;	//機能しているか
	bool m_MouseOver;//マウスカーソルを合わせているか

	bool m_IsDiscreteButton;//個別のボタンであるか

	BUTTON_TYPE m_ButtonType;//ボタンタイプ

	ButtonFunc m_ButtonFunction;//ボタンON時の処理
};