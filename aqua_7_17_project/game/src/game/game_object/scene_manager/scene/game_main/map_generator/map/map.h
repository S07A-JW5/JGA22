#pragma once
#include "aqua.h"

class cMap : public aqua::IGameObject
{
public:
	static const int m_tile_size = 16;

	enum class TILE_ID
	{
		EMPTY,		//空
		WALL,		//壁
		ROOM,		//部屋
		GATE,		//境界
		CORRIDOR,	//廊下
		STAIR,		//階段
	};

	struct TILE
	{
		TILE_ID TileID;		//タイル種類
		bool Mapped;		//マッピングフラグ
		bool Visible;		//可視フラグ
	};

	struct DroppedItem
	{
		unsigned int ItemID;	//アイテムID
		unsigned int Num;		//数量
	};

	//コンストラクタ
	cMap(aqua::IGameObject* parent);

	//デストラクタ
	~cMap() = default;

	//初期化
	void Initialize() override;
	void Initialize(int width, int height, std::uint8_t** mapdata,
		aqua::CVector2 start, aqua::CVector2 stair);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//アイテムを拾う
	cMap::DroppedItem GatherItem(int x_pos, int y_pos);

	//アイテム設置
	void PutItem(int x_pos, int y_pos, unsigned int item_id, unsigned int num = 1);

	//ユニット配置
	void PutUnit(int x_pos, int y_pos, uint16_t unit_id);

	//マップの横サイズ取得
	int GetMapWidth();

	//マップの縦サイズ取得
	int GetMapHeight();

	//開始位置取得
	aqua::CVector2 GetStartPoint();

	//階段の位置取得
	aqua::CVector2 GetStairPos();

	//マウスカーソルの位置にあるマスを取得
	aqua::CVector2 GetPointedTile(aqua::CPoint mouse_pos);

	//指定位置にあるマスの種類を取得
	cMap::TILE_ID GetTile(int x_pos, int y_pos);

	//指定位置にあるマスが歩行可能かを取得
	bool IsWalkableTile(int x_pos, int y_pos);

	//指定位置にあるマスにアイテムを設置可能かを取得
	bool CanPutItem(int x_pos, int y_pos);

	//指定位置にあるマスが視認可能かを取得
	bool IsTileVisible(int x_pos, int y_pos);

	//指定範囲内をマッピング
	void SetMapped(aqua::CVector2 pos, int radius);

	//指定範囲内をマッピング
	void SetMappedFloatRadius(aqua::CVector2 pos, float radius);

	//指定位置間に壁があるかを取得
	bool HitWall(aqua::CVector2 posA, aqua::CVector2 posB);

	//指定位置のマスの種類を変更
	void SetTile(int x_pos, int y_pos, TILE_ID tile);

	bool HasData();
private:
	bool m_HasData;
	uint8_t	m_Width;		//マップの横サイズ
	uint8_t	m_Height;		//マップの縦サイズ
	TILE** m_Tile;			//マップタイル配列
	DroppedItem** m_Item;		//アイテム配列
	aqua::CVector2 m_StartPos;	//開始地点
	aqua::CVector2 m_StairPos;	//階段の位置
	aqua::CSprite m_ItemSprite;	//アイテムスプライト
	aqua::CSprite m_WallSprite;	//壁スプライト
	aqua::CSprite m_TileSprite;	//床スプライト
	aqua::CSprite m_StairSprite;	//階段スプライト
	aqua::CVector2 m_TileDrawPos;	//タイル描画位置
	aqua::CRect m_DrawArea;		//描画範囲
	IGameObject* m_Camera;		//カメラのポインタ
	IGameObject* m_UnitManager;	//ユニットマネージャのポインタ
};
