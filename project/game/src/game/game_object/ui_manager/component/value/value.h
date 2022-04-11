#pragma once
#include "aqua.h"

class cValue :public aqua::IGameObject
{
public:
	cValue(aqua::IGameObject* parent);

	~cValue() = default;

	void Initialize(aqua::CVector2 position, int value,int max, int size, bool display_max);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetNum(int value);

	int GetNum(bool calcvalue = false);

	float GetFloatNum();

	bool IsZero();

	bool Complete();

private:
	int m_Max;		//最大値
	int m_Value;	//現在の数値
	int m_CalcValue;//計算済み数値

	int m_PrevValue;

	aqua::CLabel m_ValueLabel;

	aqua::CLabel m_MaxLabel;
};