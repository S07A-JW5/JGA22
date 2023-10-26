#include "map_generator.h"

#define SEARCH_NEXT_BRANCH {LoopCount = 0; ++m_CurrentBranchP %= m_BranchPoint.size(); if(m_CurrentBranchP < m_BranchPoint.size()) continue; return true;}

const uint8_t cMapGenerator::m_default_width = 40;
const uint8_t cMapGenerator::m_default_height = 40;

cMapGenerator::cMapGenerator(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "MapGenerator")
	, m_Map(nullptr)
	, m_MapObj(nullptr)
{
}

void cMapGenerator::Initialize()
{
	m_TimeCounter = 0;
	m_Room.clear();
	m_Corridor.clear();
	m_Corner.clear();
	m_BranchPoint.clear();
	m_Generating = false;
}

void cMapGenerator::Update()
{
	IGameObject::Update();
}

void cMapGenerator::Draw()
{
	if (m_MapObj) m_MapObj->Draw();
}

void cMapGenerator::Finalize()
{
	for (int i = 0; i < m_Width; i++)
		AQUA_SAFE_DELETE_ARRAY(m_Map[i]);
	AQUA_SAFE_DELETE_ARRAY(m_Map);

	IGameObject::Finalize();
}

bool cMapGenerator::GenerateMap(uint8_t level, uint32_t width, uint32_t height,
	uint32_t min_room_siz, uint32_t max_room_siz, uint32_t max_room_cnt,
	uint32_t min_corr_len, uint32_t max_corr_len, uint32_t max_corr_cnt)
{
	m_Level = level;
	SetMapGenParam(width, height, min_room_siz, max_room_siz, max_room_cnt,
		min_corr_len, max_corr_len, max_corr_cnt);
	Generate();
	return !m_Generating;
}

cMap* cMapGenerator::GetMap()
{
	return m_MapObj;
}

bool cMapGenerator::MapGenerated()
{
	if (!m_MapObj)
		return false;
	return m_MapObj->HasData() && !m_Generating;
}

void cMapGenerator::SetMapGenParam(uint32_t width, uint32_t height,
	uint32_t min_room_siz, uint32_t max_room_siz, uint32_t max_room_cnt,
	uint32_t min_corr_len, uint32_t max_corr_len, uint32_t max_corr_cnt)
{
	m_TimeCounter = 0;
	m_Room.clear();
	m_Corridor.clear();
	m_Corner.clear();
	m_BranchPoint.clear();
	if (m_Map)
	{
		for (int i = 0; i < m_Width; i++)
			AQUA_SAFE_DELETE_ARRAY(m_Map[i]);
		AQUA_SAFE_DELETE_ARRAY(m_Map);
	}
	m_Generating = false;

	m_Width	= (uint8_t)min(width, UINT8_MAX);
	m_Height	= (uint8_t)min(height, UINT8_MAX);
	m_MinRoomSize		= (uint8_t)min(min_room_siz, UINT8_MAX);
	m_MaxRoomSize		= (uint8_t)min(max_room_siz, UINT8_MAX);
	m_MaxRoomCount	= (uint8_t)min(max_room_cnt, UINT8_MAX);
	m_MinCorridorLen	= (uint8_t)min(min_corr_len, UINT8_MAX);
	m_MaxCorridorLen	= (uint8_t)min(max_corr_len, UINT8_MAX);
	m_MaxCorridorCount	= (uint8_t)min(max_corr_cnt, UINT8_MAX);

	m_Map = AQUA_NEW std::uint8_t * [m_Width];
	for (int i = 0; i < m_Width; i++)
		m_Map[i] = AQUA_NEW std::uint8_t[m_Height];

	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Height; j++)
			m_Map[i][j] = TILE_TYPE::EMPTY;
}

void cMapGenerator::Generate()
{
	if (!m_Generating)
	{
		CreateRoom(true);
		m_Generating = true;
		m_Timer = GetNowCount();
	}

	while (true)
	{
		m_TimeCounter = 0;
		if (CreateRoom())
		{
			m_Generating = false;
			break;
		}
	}

	if (!m_Generating)
	{
		int PlayerRoom = 0;
		int StairRoom = 0;

		PlayerRoom = rand() % m_Room.size();
		do
		{
			if (m_Room.size() == 1)
			{
				StairRoom = PlayerRoom;
				break;
			}
			StairRoom = rand() % m_Room.size();
		} while (StairRoom == PlayerRoom);

		aqua::CPoint PlayerStartPoint = aqua::CPoint::ZERO;
		aqua::CPoint StairPoint = aqua::CPoint::ZERO;
		PlayerStartPoint = GetRandomPointInRoom(PlayerRoom);
		do
		{
			StairPoint = GetRandomPointInRoom(StairRoom, 1);
		} while (PlayerStartPoint.x == StairPoint.x &&
			PlayerStartPoint.y == StairPoint.y);

		m_Map[PlayerStartPoint.x][PlayerStartPoint.y] = TILE_TYPE::START;
		m_Map[StairPoint.x][StairPoint.y] = TILE_TYPE::STAIR;

		m_StartPos.x = (float)PlayerStartPoint.x;
		m_StartPos.y = (float)PlayerStartPoint.y;
		m_StairPos.x = (float)StairPoint.x;
		m_StairPos.y = (float)StairPoint.y;

		if (m_MapObj)
			m_MapObj->DeleteObject();
		m_MapObj = aqua::CreateGameObject<cMap>(this);
		m_MapObj->Initialize(m_Width, m_Height, m_Map, m_StartPos, m_StairPos);
		PutEnemy(PlayerRoom);
	}

#ifdef _DEBUG
	if (!m_Generating)
	{
		AQUA_DEBUG_LOG("Finished!");
		AQUA_DEBUG_LOG("Time: " + std::to_string(GetNowCount() - m_Timer) + "ms");
		AQUA_DEBUG_LOG(std::to_string(m_Room.size()) + "rooms");
		AQUA_DEBUG_LOG(std::to_string(m_Corridor.size()) + "corridors");
		//AQUA_DEBUG_LOG(std::to_string(m_Corner.size()) + "corners");
	}
#endif // _DEBUG
}

bool cMapGenerator::CreateRoom(bool first)
{
	aqua::CRect RoomRect;
	Room room;
	room.ConnectedCorner.clear();
	BranchPoint BranchP;
	int LoopCount = 0;

	int Timer = GetNowCount();

	if (first)
	{
		for (int i = 0; i < m_Width; i++)
			for (int j = 0; j < m_Height; j++)
				m_Map[i][j] = TILE_TYPE::EMPTY;
		m_Room.clear();
		m_Corridor.clear();
		m_Corner.clear();
		m_BranchPoint.clear();
		m_CurrentBranchP = 0;
		m_TimeCounter = 0;

		RoomRect.left = m_Width / 2 - rand() % 4;
		RoomRect.top = m_Height / 2 - rand() % 4;
		RoomRect.right = RoomRect.left + aqua::Rand(m_MinRoomSize, m_MaxRoomSize) - 1;
		RoomRect.bottom = RoomRect.top + aqua::Rand(m_MinRoomSize, m_MaxRoomSize) - 1;

		for (int i = RoomRect.left - 1; i <= RoomRect.right + 1; i++)
			for (int j = RoomRect.top - 1; j <= RoomRect.bottom + 1; j++)
			{
				m_Map[i][j] = TILE_TYPE::ROOM;
				if ((i < RoomRect.left || i > RoomRect.right) ||
					(j < RoomRect.top || j > RoomRect.bottom))
					m_Map[i][j] = TILE_TYPE::WALL;
			}
		for (int i = 0; i < DIRECTION::COUNT; i++)
		{
			aqua::CRect Temp = RoomRect;
			BranchP.Direction = (DIRECTION)i;
			switch (BranchP.Direction)
			{
			case cMapGenerator::NORTH:
				Temp.top = Temp.bottom = RoomRect.top - 1;
				break;
			case cMapGenerator::SOUTH:
				Temp.top = Temp.bottom = RoomRect.bottom + 1;
				break;
			case cMapGenerator::WEST:
				Temp.left = Temp.right = RoomRect.left - 1;
				break;
			case cMapGenerator::EAST:
				Temp.left = Temp.right = RoomRect.right + 1;
				break;
			}
			BranchP.Rect = Temp;
			BranchP.RootRoom = 0;
			BranchP.Used = false;
			BranchP.RootIsCorridor = false;
			m_BranchPoint.push_back(BranchP);
		}
		room.RoomRect = RoomRect;
		m_Room.push_back(room);

		m_Generating = true;

		return false;
	}

	do
	{
		if ((GetNowCount() - Timer) > 10)
		{
			Timer = GetNowCount();
			++m_TimeCounter;
			AQUA_DEBUG_LOG(std::to_string(m_TimeCounter));
			if (m_TimeCounter > 5)
				return true;
		}

		BranchP = m_BranchPoint[m_CurrentBranchP];
		if (BranchP.Used)
			SEARCH_NEXT_BRANCH

			++LoopCount;

		aqua::CPoint Point = aqua::CPoint(BranchP.Rect.left, BranchP.Rect.top);
		if (BranchP.Direction == DIRECTION::NORTH ||
			BranchP.Direction == DIRECTION::SOUTH)
		{
			Point.x += LoopCount - 1;
			if (Point.x > BranchP.Rect.right)
				SEARCH_NEXT_BRANCH
		}
		if (BranchP.Direction == DIRECTION::WEST ||
			BranchP.Direction == DIRECTION::EAST)
		{
			Point.y += LoopCount - 1;
			if (Point.y > BranchP.Rect.bottom)
				SEARCH_NEXT_BRANCH
		}

		if ((Point.x < 1) || (Point.x >= m_Width - 1) ||
			(Point.y < 1) || (Point.y >= m_Height - 1))
			SEARCH_NEXT_BRANCH

			aqua::CPoint GatePoint = Point;

		switch (BranchP.Direction)
		{
		case cMapGenerator::NORTH:
			Point.y--;
			break;
		case cMapGenerator::SOUTH:
			Point.y++;
			break;
		case cMapGenerator::WEST:
			Point.x--;
			break;
		case cMapGenerator::EAST:
			Point.x++;
			break;
		}

		RoomRect.left = RoomRect.right = Point.x;
		RoomRect.top = RoomRect.bottom = Point.y;

		bool Corridor = (rand() % 10) == 0;
		if (!BranchP.RootIsCorridor)
			Corridor = true;
		if (Corridor)
		{
			if (m_Corridor.size() >= m_MaxCorridorCount)
				SEARCH_NEXT_BRANCH

				bool Crossed = rand() % 3;
			int Length = aqua::Rand(m_MinCorridorLen, m_MaxCorridorLen);
			if (Crossed && !BranchP.RootIsCorridor)
			{
				bool LeftTurn = rand() % 2;

				if (LeftTurn)
				{
					switch (BranchP.Direction)
					{
					case cMapGenerator::NORTH:
						RoomRect.left -= Length - 1;
						break;
					case cMapGenerator::SOUTH:
						RoomRect.right += Length - 1;
						break;
					case cMapGenerator::WEST:
						RoomRect.bottom += Length - 1;
						break;
					case cMapGenerator::EAST:
						RoomRect.top -= Length - 1;
						break;
					}
				}
				else
				{
					switch (BranchP.Direction)
					{
					case cMapGenerator::NORTH:
						RoomRect.right += Length - 1;
						break;
					case cMapGenerator::SOUTH:
						RoomRect.left -= Length - 1;
						break;
					case cMapGenerator::WEST:
						RoomRect.top -= Length - 1;
						break;
					case cMapGenerator::EAST:
						RoomRect.bottom += Length - 1;
						break;
					}
				}
			}
			else
			{
				switch (BranchP.Direction)
				{
				case cMapGenerator::NORTH:
					RoomRect.top -= Length - 1;
					break;
				case cMapGenerator::SOUTH:
					RoomRect.bottom += Length - 1;
					break;
				case cMapGenerator::WEST:
					RoomRect.left -= Length - 1;
					break;
				case cMapGenerator::EAST:
					RoomRect.right += Length - 1;
					break;
				}
			}

			if ((RoomRect.left < 1) || (RoomRect.left >= m_Width - 1) ||
				(RoomRect.right < 1) || (RoomRect.right >= m_Width - 1) ||
				(RoomRect.top < 1) || (RoomRect.top >= m_Height - 1) ||
				(RoomRect.bottom < 1) || (RoomRect.bottom >= m_Height - 1))
			{
				SEARCH_NEXT_BRANCH
			}

			if (TileEmptyCheck(RoomRect))
			{
				for (int i = RoomRect.left - 1; i <= RoomRect.right + 1; i++)
					for (int j = RoomRect.top - 1; j <= RoomRect.bottom + 1; j++)
					{
						m_Map[i][j] = TILE_TYPE::CORRIDOR;
						if ((i < RoomRect.left || i > RoomRect.right) ||
							(j < RoomRect.top || j > RoomRect.bottom))
							m_Map[i][j] = TILE_TYPE::WALL;
					}
				room.RoomRect = RoomRect;
				room.ConnectedCorner.push_back((uint16_t)m_Corner.size());

				m_Map[GatePoint.x][GatePoint.y] = TILE_TYPE::GATE;
				Corner corner;
				corner.Position = aqua::CVector2((float)GatePoint.x, (float)GatePoint.y);
				corner.RoomNo[0] = m_BranchPoint[m_CurrentBranchP].RootRoom;
				corner.RoomNo[1] = (int16_t)m_Corridor.size() + 256;
				if (corner.RoomNo[0] < 256)
				{
					if (!m_Room[corner.RoomNo[0]].ConnectedCorner.empty())
						for (auto it : m_Room[corner.RoomNo[0]].ConnectedCorner)
						{
							corner.ConnectedCorner.push_back(it);
							m_Corner[it].ConnectedCorner.push_back((uint16_t)m_Corner.size());
						}
					m_Room[corner.RoomNo[0]].ConnectedCorner.push_back((uint16_t)m_Corner.size());
				}
				else
				{
					if (!m_Corridor[corner.RoomNo[0] - 256].ConnectedCorner.empty())
						for (auto it : m_Corridor[corner.RoomNo[0] - 256].ConnectedCorner)
						{
							corner.ConnectedCorner.push_back(it);
							m_Corner[it].ConnectedCorner.push_back((uint16_t)m_Corner.size());
						}
					m_Corridor[corner.RoomNo[0] - 256].ConnectedCorner.push_back((uint16_t)m_Corner.size());
				}
				m_Corner.push_back(corner);
				m_Corridor.push_back(room);
				m_BranchPoint[m_CurrentBranchP].Used = true;

				DIRECTION BranchRootDir = BranchP.Direction; {
					switch (BranchRootDir)
					{
					case cMapGenerator::NORTH:
						BranchRootDir = SOUTH;
						break;
					case cMapGenerator::SOUTH:
						BranchRootDir = NORTH;
						break;
					case cMapGenerator::WEST:
						BranchRootDir = EAST;
						break;
					case cMapGenerator::EAST:
						BranchRootDir = WEST;
						break;
					}}
				for (int i = 0; i < DIRECTION::COUNT; i++)
				{
					if (i == BranchRootDir)continue;

					aqua::CRect Temp = RoomRect;
					BranchP.Direction = (DIRECTION)i;
					switch (BranchP.Direction)
					{
					case cMapGenerator::NORTH:
						Temp.top = Temp.bottom = RoomRect.top - 1;
						break;
					case cMapGenerator::SOUTH:
						Temp.top = Temp.bottom = RoomRect.bottom + 1;
						break;
					case cMapGenerator::WEST:
						Temp.left = Temp.right = RoomRect.left - 1;
						break;
					case cMapGenerator::EAST:
						Temp.left = Temp.right = RoomRect.right + 1;
						break;
					}
					BranchP.Rect = Temp;
					BranchP.RootRoom = (uint16_t)m_Corridor.size() - 1 + 256;
					BranchP.Used = false;
					BranchP.RootIsCorridor = true;
					m_BranchPoint.push_back(BranchP);
				}
				LoopCount = 0;
				++m_CurrentBranchP %= m_BranchPoint.size();
				if (m_CurrentBranchP >= m_BranchPoint.size())
					return true;
				return false;
			}
			else continue;
		}
		else
		{
			if (m_Room.size() >= m_MaxRoomCount)
				SEARCH_NEXT_BRANCH

				std::uint8_t RoomWidth = (uint8_t)aqua::Rand(m_MinRoomSize, m_MaxRoomSize);
			std::uint8_t RoomHeight = (uint8_t)aqua::Rand(m_MinRoomSize, m_MaxRoomSize);
			std::uint8_t RoomShiftX = 0;
			std::uint8_t RoomShiftY = 0;
			switch (BranchP.Direction)
			{
			case cMapGenerator::NORTH:
				RoomShiftX = rand() % RoomWidth;
				RoomRect.top -= RoomHeight - 1;
				RoomRect.left -= RoomWidth - RoomShiftX - 1;
				RoomRect.right += RoomShiftX;
				break;
			case cMapGenerator::SOUTH:
				RoomShiftX = rand() % RoomWidth;
				RoomRect.bottom += RoomHeight - 1;
				RoomRect.left -= RoomWidth - RoomShiftX - 1;
				RoomRect.right += RoomShiftX;
				break;
			case cMapGenerator::WEST:
				RoomShiftY = rand() % RoomHeight;
				RoomRect.left -= RoomWidth - 1;
				RoomRect.top -= RoomHeight - RoomShiftY - 1;
				RoomRect.bottom += RoomShiftY;
				break;
			case cMapGenerator::EAST:
				RoomShiftY = rand() % RoomHeight;
				RoomRect.right += RoomWidth - 1;
				RoomRect.top -= RoomHeight - RoomShiftY - 1;
				RoomRect.bottom += RoomShiftY;
				break;
			}

			if ((RoomRect.left < 1) || (RoomRect.left >= m_Width - 1) ||
				(RoomRect.right < 1) || (RoomRect.right >= m_Width - 1) ||
				(RoomRect.top < 1) || (RoomRect.top >= m_Height - 1) ||
				(RoomRect.bottom < 1) || (RoomRect.bottom >= m_Height - 1))
			{
				SEARCH_NEXT_BRANCH
			}

			if (TileEmptyCheck(RoomRect))
			{
				for (int i = RoomRect.left - 1; i <= RoomRect.right + 1; i++)
					for (int j = RoomRect.top - 1; j <= RoomRect.bottom + 1; j++)
					{
						m_Map[i][j] = TILE_TYPE::ROOM;
						if ((i < RoomRect.left || i > RoomRect.right) ||
							(j < RoomRect.top || j > RoomRect.bottom))
							m_Map[i][j] = TILE_TYPE::WALL;
					}
				room.RoomRect = RoomRect;
				room.ConnectedCorner.push_back((uint16_t)m_Corner.size());

				m_Map[GatePoint.x][GatePoint.y] = TILE_TYPE::GATE;
				Corner corner;
				corner.Position = aqua::CVector2((float)GatePoint.x, (float)GatePoint.y);
				corner.RoomNo[0] = m_BranchPoint[m_CurrentBranchP].RootRoom;
				corner.RoomNo[1] = (int16_t)m_Room.size();
				if (corner.RoomNo[0] < 256)
				{
					if (!m_Room[corner.RoomNo[0]].ConnectedCorner.empty())
						for (auto it : m_Room[corner.RoomNo[0]].ConnectedCorner)
						{
							corner.ConnectedCorner.push_back(it);
							m_Corner[it].ConnectedCorner.push_back((uint16_t)m_Corner.size());
						}
					m_Room[corner.RoomNo[0]].ConnectedCorner.push_back((uint16_t)m_Corner.size());
				}
				else
				{
					if (!m_Corridor[corner.RoomNo[0] - 256].ConnectedCorner.empty())
						for (auto it : m_Corridor[corner.RoomNo[0] - 256].ConnectedCorner)
						{
							corner.ConnectedCorner.push_back(it);
							m_Corner[it].ConnectedCorner.push_back((uint16_t)m_Corner.size());
						}
					m_Corridor[corner.RoomNo[0] - 256].ConnectedCorner.push_back((uint16_t)m_Corner.size());
				}
				m_Corner.push_back(corner);
				m_Room.push_back(room);

				m_Map[GatePoint.x][GatePoint.y] = TILE_TYPE::GATE;
				m_BranchPoint[m_CurrentBranchP].Used = true;
				DIRECTION BranchRootDir = BranchP.Direction;
				switch (BranchRootDir)
				{
				case cMapGenerator::NORTH:
					BranchRootDir = SOUTH;
					break;
				case cMapGenerator::SOUTH:
					BranchRootDir = NORTH;
					break;
				case cMapGenerator::WEST:
					BranchRootDir = EAST;
					break;
				case cMapGenerator::EAST:
					BranchRootDir = WEST;
					break;
				}
				for (int i = 0; i < DIRECTION::COUNT; i++)
				{
					if (i == BranchRootDir)continue;

					aqua::CRect Temp = RoomRect;
					BranchP.Direction = (DIRECTION)i;
					switch (BranchP.Direction)
					{
					case cMapGenerator::NORTH:
						Temp.top = Temp.bottom = RoomRect.top - 1;
						break;
					case cMapGenerator::SOUTH:
						Temp.top = Temp.bottom = RoomRect.bottom + 1;
						break;
					case cMapGenerator::WEST:
						Temp.left = Temp.right = RoomRect.left - 1;
						break;
					case cMapGenerator::EAST:
						Temp.left = Temp.right = RoomRect.right + 1;
						break;
					}
					BranchP.Rect = Temp;
					BranchP.RootRoom = (uint16_t)m_Room.size() - 1;
					BranchP.Used = false;
					BranchP.RootIsCorridor = false;
					m_BranchPoint.push_back(BranchP);
				}
				LoopCount = 0;
				++m_CurrentBranchP %= m_BranchPoint.size();
				return false;
			}
			else continue;
		}
	} while (true);
}

//�͈͓����󂩒��ׂ� ��̏ꍇ�Atrue��Ԃ�
bool cMapGenerator::TileEmptyCheck(aqua::CRect Range)
{
	for (int i = Range.left; i <= Range.right; i++)
		for (int j = Range.top; j <= Range.bottom; j++)
			if (m_Map[i][j] != TILE_TYPE::EMPTY)
				return false;
	return true;
}

void cMapGenerator::PutEnemy(int start_room)
{
	int Count = (int)m_Room.size();

	if (Count <= 1) return;

	aqua::CPoint Point = aqua::CPoint::ZERO;

	for (int i = 0; i < Count; i++)
	{
		if (i == start_room) continue;

		Point = GetRandomPointInRoom(i);
		//m_MapObj->PutUnit(Point.x, Point.y, aqua::Rand(max(1, m_Level - 5), m_Level));
		m_MapObj->PutUnit(Point.x, Point.y, rand() % 2 + 1);
	}
}

aqua::CPoint cMapGenerator::GetRandomPointInRoom(int room_no, int space)
{
	aqua::CVector2 Pos = GetRandomPositionInRoom(room_no, space);
	return aqua::CPoint((int)Pos.x, (int)Pos.y);
}

aqua::CVector2 cMapGenerator::GetRandomPositionInRoom(int room_no, int space)
{
	return aqua::CVector2(
		(float)aqua::Rand(m_Room[room_no].RoomRect.left + space,
			m_Room[room_no].RoomRect.right - space), 
		(float)aqua::Rand(m_Room[room_no].RoomRect.top + space,
			m_Room[room_no].RoomRect.bottom - space));
}