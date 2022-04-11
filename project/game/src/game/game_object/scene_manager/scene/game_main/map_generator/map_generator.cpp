#include "map_generator.h"

#define SEARCH_NEXT_BRANCH LoopCount = 0; ++m_CurrentBranchP %= m_BranchPoint.size(); if(m_CurrentBranchP < m_BranchPoint.size()) continue; return true;

const int cMapGenerator::m_width = 40;
const int cMapGenerator::m_height = 30;
const int cMapGenerator::m_min_room_size = 3;
const int cMapGenerator::m_max_room_size = 8;
const int cMapGenerator::m_min_corridor_length = 4;
const int cMapGenerator::m_max_corridor_length = 10;

cMapGenerator::cMapGenerator(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "MapGenerator")
{
}

void cMapGenerator::Initialize()
{
	m_Timer = 0;
	m_Room.clear();
	m_BranchPoint.clear();
	m_Generating = false;

	m_Width = min(m_width, m_max_width);
	m_Height = min(m_height, m_max_height);

	m_Map = new std::uint8_t*[m_Width];
	for (int i = 0; i < m_Width; i++)
		m_Map[i] = new std::uint8_t[m_Height];

	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Height; j++)
			m_Map[i][j] = TILE_TYPE::EMPTY;

}

void cMapGenerator::Update()
{
	//if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	if (m_Generating)
	{
		while (!CreateRoom())
		{
		}
		{
			m_Generating = false;
			AQUA_DEBUG_LOG("Finished!");

			for (int i = 0; i < m_Width; i++)
				for (int j = 0; j < m_Height; j++)
				{
					m_Tile[i][j].Setup(aqua::CVector2(i * 8, j * 8), 8, 8);
					switch (m_Map[i][j])
					{
					case cMapGenerator::WALL:
						m_Tile[i][j].color = 0xff0000ff;
						break;
					case cMapGenerator::ROOM:
						m_Tile[i][j].color = 0xff00ff00;
						break;
					case cMapGenerator::GATE:
						m_Tile[i][j].color = 0xffff4000;
						break;
					case cMapGenerator::CORRIDOR:
						m_Tile[i][j].color = 0xffffff00;
						break;
					default:
						m_Tile[i][j].color = 0xff000000;
						break;
					}
				}
		}
	}
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	{
		if (!m_Generating)
		{
			CreateRoom(true);
			AQUA_DEBUG_LOG("Started!");
		}
	}
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::RIGHT))
	{
		CreateRoom(true);
		AQUA_DEBUG_LOG("Started!");
	}
}

void cMapGenerator::Draw()
{
	//for (int i = 0; i < m_Width; i++)
		//for (int j = 0; j < m_Height; j++)
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 30; j++)
		{
			m_Tile[i][j].Draw();
		}
}

void cMapGenerator::Finalize()
{
}

void cMapGenerator::Generate()
{



}

bool cMapGenerator::CreateRoom(bool first)
{
	aqua::CRect RoomRect;
	BranchPoint BranchP;
	int LoopCount = 0;

	m_Timer = GetNowCount();

	if (first)
	{
		for (int i = 0; i < m_Width; i++)
			for (int j = 0; j < m_Height; j++)
				m_Map[i][j] = TILE_TYPE::EMPTY;
		m_Room.clear();
		m_BranchPoint.clear();
		m_CurrentBranchP = 0;

		RoomRect.left = m_Width / 2 - rand() % 4;
		RoomRect.top = m_Height / 2 - rand() % 4;
		RoomRect.right = RoomRect.left + aqua::Rand(m_min_room_size, m_max_room_size) - 1;
		RoomRect.bottom = RoomRect.top + aqua::Rand(m_min_room_size, m_max_room_size) - 1;

		for (int i = RoomRect.left - 1; i <= RoomRect.right + 1; i++)
			for (int j = RoomRect.top - 1; j <= RoomRect.bottom + 1; j++)
			{
				m_Map[i][j] = TILE_TYPE::ROOM;
				if ((i < RoomRect.left || i > RoomRect.right) || (j < RoomRect.top || j > RoomRect.bottom))
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
			BranchP.Used = false;
			BranchP.RootIsCorridor = false;
			m_BranchPoint.push_back(BranchP);
		}

		m_Room.push_back(RoomRect);

		m_Generating = true;

		return false;
	}

	do
	{
		if ((GetNowCount() - m_Timer) > 500)
			return true;

		BranchP = m_BranchPoint[m_CurrentBranchP];
		if (BranchP.Used)
		{
			SEARCH_NEXT_BRANCH
		}
		++LoopCount;

		aqua::CPoint Point = aqua::CPoint(BranchP.Rect.left, BranchP.Rect.top);
		if (BranchP.Direction == DIRECTION::NORTH || BranchP.Direction == DIRECTION::SOUTH)
		{
			Point.x += LoopCount - 1;
			if (Point.x > BranchP.Rect.right)
			{
				SEARCH_NEXT_BRANCH
			}
		}
		if (BranchP.Direction == DIRECTION::WEST || BranchP.Direction == DIRECTION::EAST)
		{
			Point.y += LoopCount - 1;
			if (Point.y > BranchP.Rect.bottom)
			{
				SEARCH_NEXT_BRANCH
			}
		}

		if ((Point.x < 1) || (Point.x >= m_Width - 1) || (Point.y < 1) || (Point.y >= m_Height - 1))
		{
			SEARCH_NEXT_BRANCH
		}

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

		bool Corridor = rand() % 2;
		//Corridor = true;
		if (Corridor)
		{
			bool Crossed = rand() % 3;
			int Length = aqua::Rand(m_min_corridor_length, m_max_corridor_length);

			if (Crossed)
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
						if ((i < RoomRect.left || i > RoomRect.right) || (j < RoomRect.top || j > RoomRect.bottom))
							m_Map[i][j] = TILE_TYPE::WALL;
					}
				m_Map[GatePoint.x][GatePoint.y] = TILE_TYPE::GATE;
				if(BranchP.RootIsCorridor)
					m_Map[GatePoint.x][GatePoint.y] = TILE_TYPE::CORRIDOR;
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
			std::uint8_t RoomWidth = aqua::Rand(m_min_room_size, m_max_room_size);
			std::uint8_t RoomHeight = aqua::Rand(m_min_room_size, m_max_room_size);
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
						if ((i < RoomRect.left || i > RoomRect.right) || (j < RoomRect.top || j > RoomRect.bottom))
							m_Map[i][j] = TILE_TYPE::WALL;
					}
				m_Map[GatePoint.x][GatePoint.y] = TILE_TYPE::GATE;
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
					BranchP.Used = false;
					BranchP.RootIsCorridor = false;
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
	} while (true);
}

//îÕàÕì‡Ç™ãÛÇ©í≤Ç◊ÇÈ ãÛÇÃèÍçáÅAtrueÇï‘Ç∑
bool cMapGenerator::TileEmptyCheck(aqua::CRect Range)
{
	for (int i = Range.left; i <= Range.right; i++)
		for (int j = Range.top; j <= Range.bottom; j++)
			if (m_Map[i][j] != TILE_TYPE::EMPTY)
				return false;
	return true;
}
