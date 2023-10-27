#pragma once

#include "aqua.h"
#include "unit/unit.h"
#include "unit/unit_id.h"
#include "unit/player/player.h"
#include "unit/npc/bot.h"
#include <vector>

class cUnitManager : public aqua::IGameObject
{
public:

	//コンストラクタ
	cUnitManager(aqua::IGameObject* parent);

	//デストラクタ
	~cUnitManager(void) = default;

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Finalize();

	//解放
	void Clear();

	//ユニット生成
	void Create(std::uint16_t id, int x_pos, int y_pos);

	//マップ生成
	void MapGeneration();

	//プレイヤーに隣接しているか
	bool IsPlayerNearBy(aqua::CVector2 pos);

	//指定位置にスペースがあるか
	bool HasSpace(aqua::CVector2 pos);

	//指定位置のユニットに攻撃できるか
	bool CanAttack(aqua::CVector2 target_pos);

	//指定位置のユニットに攻撃
	bool Attack(aqua::CVector2 target_pos, int damage, IUnit::DAMAGE_TYPE type);

	//移動
	void SetMovedPos(aqua::CVector2 prev, aqua::CVector2 moved);

	//プレイヤー移動
	void SetPlayerPos(aqua::CVector2 pos);

	//プレイヤー位置取得
	aqua::CVector2 GetPlayerPos();

	//プレイヤーとの距離取得
	float BetweenPlayer(aqua::CVector2 pos);

	//マップサイズ設定
	void SetMapSize(int width, int height);

	//現在の階層取得
	uint8_t GetFloorCount();

private:
	IGameObject* m_TextManager; //テキストマネージャのポインタ

	cPlayer* m_Player; //プレイヤー

	uint8_t m_Floor; //現在の階層

	std::vector<cBot*> m_NPCs; //プレイヤー以外のユニット

	int** m_UnitPos; //ユニット位置

	uint8_t m_Width; //マップ横サイズ

	uint8_t m_Height; //マップ縦サイズ

	IGameObject* m_MapGenerator; //マップ生成器

	IGameObject* m_MapObj; //マップ

	bool m_MapGenerated; //マップ生成が完了したか

	aqua::CVector2 m_PlayerPos; //プレイヤー位置

	IGameObject* m_GameMain; //ゲームメインシーンのポインタ
};
