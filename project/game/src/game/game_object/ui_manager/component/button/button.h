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

	cButton(aqua::IGameObject* parent);

	~cButton() = default;

	void Initialize(ButtonFunc button_function, const aqua::CVector2 & pos,
		BUTTON_TYPE type, const std::string & name, const int& width, const int& height,
		const int& font_size, const std::string & description, const bool& select);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	bool MouseOvered();

	bool Pressed();

private:
	static const int m_space;
	static const int m_size;

	aqua::CVector2 m_Position;

	int m_Height;
	int m_Width;

	aqua::CSprite m_Sprite[9];
	aqua::CLabel m_Name;

	std::string m_DescText;
	aqua::IGameObject* m_DescObj;

	float m_Timer;

	bool m_Active;//ボタンの機能を利用できるか
	bool m_Switch;//機能しているか
	bool m_MouseOver;//マウスカーソルを合わせているか

	bool m_IsDiscreteButton;//個別のボタンであるか

	BUTTON_TYPE m_ButtonType;

	ButtonFunc m_ButtonFunction;
};