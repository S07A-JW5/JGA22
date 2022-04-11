#pragma once

#include "aqua.h"

class cAmountPopUp :public aqua::IGameObject
{
public:
	enum POP_UP_TYPE
	{
		DMG_RIVAL,
		DMG_PLAYER,
		DMG_PP,
		HEAL_HP,
		HEAL_PP
	};

	cAmountPopUp(aqua::IGameObject* parent);

	~cAmountPopUp() = default;

	void Initialize(const aqua::CVector2& pos, const int& amount, POP_UP_TYPE type, bool miss);

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	static const unsigned int m_color[5];

	static const int m_size = 128;

	aqua::CVector2 m_Position;

	int m_Width;

	int m_Digit;

	int m_TimerPhase;

	float m_Timer;

	aqua::CSprite m_BackSprite;
	aqua::CSprite* m_AmountSprite;
};