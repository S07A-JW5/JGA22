#pragma once
#include "aqua.h"
#include "map/map.h"

class cMapGenerator : public aqua::IGameObject
{
public:
	enum TILE_TYPE
	{
		EMPTY,
		WALL,
		ROOM,
		GATE,
		CORRIDOR,
		START,
		STAIR,
	};

	cMapGenerator(aqua::IGameObject* parent);

	~cMapGenerator() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	bool LoadMap(std::string file_name);

	bool GenerateMap(uint8_t level = 0, uint8_t width = 40, uint8_t height = 30,
		uint8_t min_room_siz = 4, uint8_t max_room_siz = 8, uint8_t max_room_cnt = 10,
		uint8_t min_corr_len = 8, uint8_t max_corr_len = 12, uint8_t max_corr_cnt = 10);

	bool MapGenerated();

	cMap* GetMap();

private:
	enum DIRECTION
	{
		NORTH,
		SOUTH,
		WEST,
		EAST,

		COUNT
	};

	struct BranchPoint
	{
		aqua::CRect	Rect;
		DIRECTION		Direction;
		uint16_t		RootRoom;
		bool Used;
		bool RootIsCorridor;
	};

	void SetMapGenParam(uint8_t width, uint8_t height,
		uint8_t min_room_siz, uint8_t max_room_siz, uint8_t max_room_cnt,
		uint8_t min_corr_len, uint8_t max_corr_len, uint8_t max_corr_cnt);

	void Generate();
	bool CreateRoom(bool first = false);	//部屋を作る
	bool TileEmptyCheck(aqua::CRect Range);	//範囲内が空か調べる
	void PutEnemy(int start_room);
	aqua::CPoint GetRandomPointInRoom(int room_no, int space = 0);
	aqua::CVector2 GetRandomPositionInRoom(int room_no, int space = 0);

	static const uint8_t m_max_width = 255;
	static const uint8_t m_max_height = 255;

	static const uint8_t m_default_width;
	static const uint8_t m_default_height;

	bool m_Generating;
	int m_CurrentBranchP;
	int m_Timer;
	int m_TimeCounter;
	int m_FrameCounter;

	uint8_t m_Level;

	aqua::CBoxPrimitive m_Tile[m_max_width][m_max_height];
	std::vector<cMap::Room> m_Room;
	std::vector<cMap::Room> m_Corridor;
	std::vector<cMap::Corner> m_Corner;
	std::vector<BranchPoint> m_BranchPoint;
	aqua::CVector2 m_StartPos;	//開始地点
	aqua::CVector2 m_StairPos;	//階段の位置

	uint8_t** m_Map;			//マップ配列
	uint8_t  m_Width;			//マップの横サイズ
	uint8_t  m_Height;		//マップの縦サイズ
	uint8_t  m_MinRoomSize;	//部屋の一辺の最小長さ
	uint8_t  m_MaxRoomSize;	//部屋の一辺の最大長さ
	uint8_t  m_MinCorridorLen;	//廊下の最小長さ
	uint8_t  m_MaxCorridorLen;	//廊下の最大長さ
	uint16_t m_MaxRoomCount;	//部屋の最大数
	uint16_t m_MaxCorridorCount;//廊下の最大数

	cMap* m_MapObj;
};