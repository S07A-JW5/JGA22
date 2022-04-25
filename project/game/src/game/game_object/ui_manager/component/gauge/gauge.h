#pragma once
#include "aqua.h"

class cGauge :public aqua::IGameObject
{
public:
	cGauge(aqua::IGameObject* parent);

	~cGauge() = default;

	void Initialize(aqua::CVector2 position, int value, int limit, int width, int height, bool mirror, bool has_bg, aqua::IGameObject* sync_obj);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetNum(int value);

	void SetMax(int value);

private:
	static const int m_space;
	static const int m_size;

	int m_Max;				//�ő�l
	float m_Value;			//���݂̐��l
	float m_CalcValue;			//�v�Z�ςݐ��l
	float m_Timer;			//�^�C�}�[

	float m_PrevValue;

	int m_Width;

	int m_Height;

	bool m_Mirror;

	aqua::IGameObject* m_SyncObject;

	aqua::CSprite m_Gauge[2];

	aqua::CSprite m_Background[9];
};