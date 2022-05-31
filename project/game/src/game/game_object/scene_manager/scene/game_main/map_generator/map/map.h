#pragma once
#include "aqua.h"
//#include 

class cMap : public aqua::IGameObject
{
public:
	static const int m_tile_size = 16;

	enum class TILE_ID
	{
		WALL,
		ROOM,
		GATE,
		CORRIDOR,
		STAIR,
	};

	struct TILE
	{
		TILE_ID TileID;
		bool Mapped;
		bool Visible;
	};

	struct DroppedItem
	{
		unsigned int ItemID;
		unsigned int Num;
	};

	struct Room
	{
		aqua::CRect RoomRect;
		std::list<std::uint16_t> ConnectedCorner;
	};

	struct Corner
	{
		aqua::CVector2 Position;
		std::int16_t RoomNo[2];
		std::list<std::uint16_t> ConnectedCorner;
	};

	cMap(aqua::IGameObject* parent, std::string name = "Map");

	~cMap() = default;

	void Initialize() override;
	void Initialize(int width, int height, std::uint8_t** mapdata,
		aqua::CVector2 start, aqua::CVector2 stair, std::vector<Room> room,
		std::vector<Room> corridor, std::vector<Corner> corner);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	cMap::DroppedItem GatherItem(int x_pos, int y_pos);

	void PutItem(int x_pos, int y_pos, unsigned int item_id, unsigned int num = 1);

	void PutUnit(int x_pos, int y_pos, unsigned int unit_id);

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

	int16_t GetRoom(aqua::CVector2 pos);
	std::list<aqua::CVector2> GetPath(aqua::CVector2 posA, aqua::CVector2 posB);

private:
	std::list<uint16_t> GetCornerList(int16_t room);
	std::list<uint16_t> FindCorner(uint16_t parent, std::list<uint16_t> target);

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
	std::vector<Room> m_Room;		//部屋配列格納変数
	std::vector<Room> m_Corridor;	//廊下配列格納変数
	std::vector<Corner> m_Corner;	//境界配列格納変数
	aqua::CRect m_DrawArea;	//描画範囲
	IGameObject* m_Camera;		//カメラ
	IGameObject* m_UnitManager;	//ﾕﾆｯﾄﾏﾈｰｼﾞｬｰ

	std::list<uint16_t> m_PathTemp;
};
