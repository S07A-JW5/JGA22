#pragma once
#include "aqua.h"

class cValue :public aqua::IGameObject
{
public:

	//コンストラクタ
	cValue(aqua::IGameObject* parent);

	//デストラクタ
	~cValue() = default;

	//初期化
	void Initialize(aqua::CVector2 position, int value,int max, int size, bool display_max);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//値設定
	void SetNum(int value);

	//値取得
	int GetNum(bool calcvalue = false);

	//値取得
	float GetFloatNum();

	//値が0かどうか
	bool IsZero();

	//表示値が設定値になったか
	bool Complete();

private:
	int m_Max;		//最大値
	int m_Value;	//現在の数値
	int m_CalcValue;//計算済み数値

	int m_PrevValue;//前フレームでの値

	aqua::CLabel m_ValueLabel;//値表示

	aqua::CLabel m_MaxLabel;//最大値表示
};