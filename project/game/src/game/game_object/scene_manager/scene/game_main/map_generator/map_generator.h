#pragma once
#include "aqua.h"

class cMapGenerator : public aqua::IGameObject
{
public:
	cMapGenerator(aqua::IGameObject* parent);

	~cMapGenerator() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void Generate();

private:
	enum TILE_TYPE
	{
		EMPTY,
		WALL,
		ROOM,
		GATE,
		CORRIDOR
	};

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
		aqua::CRect Rect;
		DIRECTION   Direction;
		bool Used;
		bool RootIsCorridor;
	};

	bool CreateRoom(bool first = false);
	bool TileEmptyCheck(aqua::CRect Range);	//”ÍˆÍ“à‚ª‹ó‚©’²‚×‚é

	static const int m_max_width = 160;
	static const int m_max_height = 90;

	static const int m_width;
	static const int m_height;
	static const int m_min_room_size;
	static const int m_max_room_size;
	static const int m_min_corridor_length;
	static const int m_max_corridor_length;

	bool m_Generating;
	int m_CurrentBranchP;
	int m_Timer;

	aqua::CBoxPrimitive m_Tile[m_max_width][m_max_height];
	std::vector<aqua::CRect> m_Room;
	std::vector<BranchPoint> m_BranchPoint;

	std::uint8_t** m_Map;
	std::uint8_t m_Width;
	std::uint8_t m_Height;
};