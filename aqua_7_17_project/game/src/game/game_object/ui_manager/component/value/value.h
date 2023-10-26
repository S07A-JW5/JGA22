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
	int m_Max;		//�ő�l
	int m_Value;	//���݂̐��l
	int m_CalcValue;//�v�Z�ςݐ��l

	int m_PrevValue;

	aqua::CLabel m_ValueLabel;

	aqua::CLabel m_MaxLabel;
};