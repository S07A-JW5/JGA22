#pragma once

#include "aqua.h"
#include "../unit.h"

class cPlayer :public IUnit
{
public:

	//コンストラクタ
	cPlayer(aqua::IGameObject* parent);

	//デストラクタ
	~cPlayer() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//カメラ更新
	void CameraUpdate();

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//階段の位置設定
	void SetStairPosition(aqua::CVector2 pos);

	//ステータス計算
	void CalcStatus(bool reset_param = false) override;

	//死亡時処理
	void Dead() override;

	//行動
	bool Action() override;

private:
	//待機
	bool Wait() override;

	//移動
	bool Move() override;

	//攻撃
	bool Attack(aqua::CVector2 pos) override;

	//アイテムを使用
	bool Item(std::int8_t slot) override;

	//装備変更
	bool EquipmentChange(std::uint16_t id);

	aqua::CVector2 m_TargetTile; //行動対象マス

	aqua::CVector2 m_StairPos; //階段位置

	aqua::CBoxPrimitive m_Box; //対象マス表示

	aqua::IGameObject* m_StatObj; //ステータスUIのポインタ
};