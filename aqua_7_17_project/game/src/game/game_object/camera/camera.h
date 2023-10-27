#pragma once
#include "aqua.h"

class cCamera : public aqua::IGameObject
{
public:
	static const int m_draw_width;
	static const int m_draw_height;

	//コンストラクタ
	cCamera(aqua::IGameObject* parent);

	//デストラクタ
	~cCamera() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//描画基準点取得
	aqua::CVector2 GetDrawBasePos();

	//描画中心点設定
	void SetDrawCenterPos(aqua::CVector2 pos);

private:
	aqua::CVector2 m_Position;
};