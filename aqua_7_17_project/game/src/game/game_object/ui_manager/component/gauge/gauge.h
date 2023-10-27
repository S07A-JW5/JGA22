#pragma once
#include "aqua.h"

class cGauge :public aqua::IGameObject
{
public:

	//コンストラクタ
	cGauge(aqua::IGameObject* parent);

	//デストラクタ
	~cGauge() = default;

	//初期化
	void Initialize(aqua::CVector2 position, int value, int limit, int width, int height, bool mirror, bool has_bg, aqua::IGameObject* sync_obj);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//現在値設定
	void SetNum(int value);

	//最大値設定
	void SetMax(int value);

private:
	static const int m_space;	//画像の角のサイズ
	static const int m_size;	//画像サイズ

	int m_Max;			//最大値
	float m_Value;		//現在の数値
	float m_CalcValue;	//計算済み数値
	float m_Timer;		//タイマー

	float m_PrevValue; //前の値

	int m_Width; //横サイズ

	int m_Height; //縦サイズ

	bool m_Mirror; //表示方向反転

	aqua::IGameObject* m_SyncObject; //連動オブジェクト(数値UI)

	aqua::CSprite m_Gauge[2]; //ゲージスプライト

	aqua::CSprite m_Background[9]; //ゲージ背景
};