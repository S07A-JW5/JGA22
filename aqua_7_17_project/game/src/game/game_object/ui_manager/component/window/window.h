#pragma once

#include "aqua.h"

class cWindow :public aqua::IGameObject
{
public:

	//コンストラクタ
	cWindow(aqua::IGameObject* parent);

	//デストラクタ
	~cWindow() = default;

	//初期化
	void Initialize(const aqua::CVector2& pos, const int& width = 64, const int& height = 64, const unsigned int& color = 0xffffffff);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//可視状態切替
	void SetVisible(bool visible);

	//位置設定
	void SetPosition(const aqua::CVector2& pos);

	//位置取得
	aqua::CVector2 GetPosition();

	static const int m_space; //画像の角のサイズ

private:
	static const int m_size; //画像サイズ

	aqua::CVector2 m_Position; //位置

	int m_Height;	//ウィンドウ高さ
	int m_Width;	//ウィンドウ幅

	aqua::CSprite m_Sprite[9]; //ウィンドウスプライト
};