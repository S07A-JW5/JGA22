#pragma once
#include "aqua.h"

class cMap : public aqua::IGameObject
{
public:
	static const int m_tile_size = 16;

	enum class TILE_ID
	{
		EMPTY,	//空
		WALL,	//壁
		ROOM,	//部屋
		GATE,	//境界
		CORRIDOR,	//廊下
		STAIR,	//階段
	};

	struct TILE
	{
		TILE_ID TileID;	//タイル種類
		bool Mapped;		//ﾏｯﾋﾟﾝｸﾞフラグ
		bool Visible;		//可視フラグ
	};

	struct DroppedItem
	{
		unsigned int ItemID;	//アイテムID
		unsigned int Num;		//数量
	};

	cMap(aqua::IGameObject* parent);

	~cMap() = default;

	void Initialize() override;
	void Initialize(int width, int height, std::uint8_t** mapdata,
		aqua::CVector2 start, aqua::CVector2 stair);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	cMap::DroppedItem GatherItem(int x_pos, int y_pos);

	void PutItem(int x_pos, int y_pos, unsigned int item_id, unsigned int num = 1);

	void PutUnit(int x_pos, int y_pos, uint16_t unit_id);

	int GetMapWidth();
	int GetMapHeight();

	aqua::CVector2 GetStartPoint();
	aqua::CVector2 GetStairPos();

	aqua::CVector2 GetPointedTile(aqua::CPoint mouse_pos);

	cMap::TILE_ID GetTile(int x_pos, int y_pos);
	bool IsWalkableTile(int x_pos, int y_pos);
	bool CanPutItem(int x_pos, int y_pos);
	bool IsTileVisible(int x_pos, int y_pos);

	void SetMapped(aqua::CVector2 pos, int radius);
	void SetMappedFloatRadius(aqua::CVector2 pos, float radius);
	bool HitWall(aqua::CVector2 posA, aqua::CVector2 posB);

	bool HasData();

	void SetTile(int x_pos, int y_pos, TILE_ID tile);
private:
	bool m_HasData;
	std::uint8_t	m_Width;		//マップの横サイズ
	std::uint8_t	m_Height;		//マップの縦サイズ
	TILE** m_Tile;			//マップタイル配列
	DroppedItem** m_Item;		//アイテム配列
	aqua::CVector2 m_StartPos;	//開始地点
	aqua::CVector2 m_StairPos;	//階段の位置
	aqua::CSprite m_ItemSprite;	//アイテムスプライト
	aqua::CSprite m_WallSprite;	//壁スプライト
	aqua::CSprite m_TileSprite;	//床スプライト
	aqua::CSprite m_StairSprite;	//階段スプライト
	aqua::CVector2 m_TileDrawPos;	//タイル描画位置
	aqua::CRect m_DrawArea;	//描画範囲
	IGameObject* m_Camera;		//カメラ
	IGameObject* m_UnitManager;	//ﾕﾆｯﾄﾏﾈｰｼﾞｬｰ
};
