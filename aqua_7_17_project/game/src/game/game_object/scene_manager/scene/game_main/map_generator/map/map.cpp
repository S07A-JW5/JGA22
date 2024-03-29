#include "map.h"
#include "../map_generator.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/unit_manager/unit_manager.h"

cMap::cMap(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Map")
	, m_HasData(false)
	, m_Width(0)
	, m_Height(0)
	, m_Tile(nullptr)
	, m_Item(nullptr)
	, m_Camera(nullptr)
	, m_UnitManager(nullptr)
	, m_StartPos(aqua::CVector2::ZERO)
	, m_StairPos(aqua::CVector2::ZERO)
	, m_DrawArea(aqua::CRect::ZERO)
{
}

void cMap::Initialize()
{
	m_ItemSprite.Create("data\\texture\\map\\item.png");
	m_WallSprite.Create("data\\texture\\map\\wall.png");
	m_TileSprite.Create("data\\texture\\map\\tile.png");
	m_StairSprite.Create("data\\texture\\map\\stair.png");
	m_Camera = aqua::FindGameObject("Camera");
	m_UnitManager = aqua::FindGameObject("UnitManager");
}

void cMap::Initialize(int width, int height, std::uint8_t** mapdata, aqua::CVector2 start, aqua::CVector2 stair)
{
	Initialize();

	for (int i = 0; i < m_Width; i++)
		AQUA_SAFE_DELETE_ARRAY(m_Tile[i]);
	AQUA_SAFE_DELETE_ARRAY(m_Tile);

	for (int i = 0; i < m_Width; i++)
		AQUA_SAFE_DELETE_ARRAY(m_Item[i]);
	AQUA_SAFE_DELETE_ARRAY(m_Item);

	m_HasData = true;

	m_Width = (uint8_t)width;
	m_Height = (uint8_t)height;

	cUnitManager* UnitMgr = (cUnitManager*)m_UnitManager;
	UnitMgr->SetMapSize(m_Width, m_Height);

	m_Tile = AQUA_NEW TILE * [m_Width];
	for (int i = 0; i < m_Width; i++)
		m_Tile[i] = AQUA_NEW TILE[m_Height];

	m_Item = AQUA_NEW DroppedItem * [m_Width];
	for (int i = 0; i < m_Width; i++)
		m_Item[i] = AQUA_NEW DroppedItem[m_Height];

	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Height; j++)
		{
			m_Tile[i][j].TileID = TILE_ID::EMPTY;
			switch ((cMapGenerator::TILE_TYPE)mapdata[i][j])
			{
			case cMapGenerator::TILE_TYPE::ROOM:
			case cMapGenerator::TILE_TYPE::START:
				m_Tile[i][j].TileID = TILE_ID::ROOM;
				break;
			case cMapGenerator::TILE_TYPE::GATE:
				m_Tile[i][j].TileID = TILE_ID::GATE;
				break;
			case cMapGenerator::TILE_TYPE::CORRIDOR:
				m_Tile[i][j].TileID = TILE_ID::CORRIDOR;
				break;
			case cMapGenerator::TILE_TYPE::STAIR:
				m_Tile[i][j].TileID = TILE_ID::STAIR;
				break;
			case cMapGenerator::TILE_TYPE::WALL:
				m_Tile[i][j].TileID = TILE_ID::WALL;
				break;
			}
			m_Item[i][j].ItemID = 0;
			m_Item[i][j].Num = 0;
			m_Tile[i][j].Mapped = false;
			m_Tile[i][j].Visible = false;
		}
	m_StartPos = start;
	m_StairPos = stair;
}

void cMap::Update()
{
	cCamera* Camera = (cCamera*)m_Camera;
	aqua::CVector2 DrawBasePos = Camera->GetDrawBasePos();
	m_DrawArea.left = (int)DrawBasePos.x / m_tile_size - 1;
	m_DrawArea.top = (int)DrawBasePos.y / m_tile_size - 1;
	m_DrawArea.right = m_DrawArea.left + cCamera::m_draw_width / m_tile_size + 1;
	m_DrawArea.bottom = m_DrawArea.top + cCamera::m_draw_height / m_tile_size + 1;
	m_TileDrawPos.x = m_DrawArea.left * m_tile_size - DrawBasePos.x;
	m_TileDrawPos.y = m_DrawArea.top * m_tile_size - DrawBasePos.y;
}

void cMap::Draw()
{
	if (!m_HasData) return;
	if (m_GameObjectState == aqua::GAME_OBJECT_STATE::DEAD) return;	
	
	aqua::CVector2 DrawPos = aqua::CVector2::ZERO;
	unsigned char Alpha = 0xff;
	for (int i = m_DrawArea.left; i <= m_DrawArea.right; i++)
		for (int j = m_DrawArea.top; j <= m_DrawArea.bottom; j++)
		{
			Alpha = 0xff;
			if (i < 0 || i >= m_Width || j < 0 || j >= m_Height) continue;

#ifdef _DEBUG
			if (!aqua::mouse::Button(aqua::mouse::BUTTON_ID::RIGHT) &&
				!m_Tile[i][j].Mapped)
				continue;
#else
			if (!m_Tile[i][j].Mapped) continue;
#endif // _DEBUG

			if (!m_Tile[i][j].Visible)
				Alpha = 0x80;

			DrawPos = m_TileDrawPos;
			DrawPos.x += m_tile_size * (i - m_DrawArea.left);
			DrawPos.y += m_tile_size * (j - m_DrawArea.top);

			switch (m_Tile[i][j].TileID)
			{
			case cMap::TILE_ID::WALL:
				m_WallSprite.position = DrawPos;
				m_WallSprite.color.alpha = Alpha;
				m_WallSprite.Draw();
				break;
			case cMap::TILE_ID::ROOM:
			case cMap::TILE_ID::GATE:
			case cMap::TILE_ID::CORRIDOR:
				m_TileSprite.position = DrawPos;
				m_TileSprite.color.alpha = Alpha;
				m_TileSprite.Draw();
				break;
			case cMap::TILE_ID::STAIR:
				m_StairSprite.position = DrawPos;
				m_StairSprite.color.alpha = Alpha;
				m_StairSprite.Draw();
				break;
			}
			if (m_Item[i][j].ItemID > 0 && m_Item[i][j].Num > 0)
			{
				m_ItemSprite.position = DrawPos;
				m_ItemSprite.color.alpha = Alpha;
				m_ItemSprite.Draw();
			}
		}
}

void cMap::Finalize()
{
	m_HasData = false;
	m_ItemSprite.Delete();
	m_WallSprite.Delete();
	m_TileSprite.Delete();
	m_StairSprite.Delete();
	for (int i = 0; i < m_Width; i++)
		AQUA_SAFE_DELETE_ARRAY(m_Tile[i]);
	AQUA_SAFE_DELETE_ARRAY(m_Tile);
	for (int i = 0; i < m_Width; i++)
		AQUA_SAFE_DELETE_ARRAY(m_Item[i]);
	AQUA_SAFE_DELETE_ARRAY(m_Item);
}

cMap::DroppedItem cMap::GatherItem(int x_pos, int y_pos)
{
	DroppedItem Item = m_Item[x_pos][y_pos];

	m_Item[x_pos][y_pos].ItemID = 0;
	m_Item[x_pos][y_pos].Num = 0;

	if (Item.ItemID == 0 || Item.Num == 0)
	{
		Item.ItemID = 0;
		Item.Num = 0;
	}
	return Item;
}

void cMap::PutItem(int x_pos, int y_pos, unsigned int item_id, unsigned int num)
{
	if (item_id <= 0) return;
	if (num <= 0) return;

	if (CanPutItem(x_pos, y_pos))
	{
		m_Item[x_pos][y_pos].ItemID = item_id;
		m_Item[x_pos][y_pos].Num = num;
		return;
	}
	int range = 1;
	int XPos = x_pos;
	int YPos = y_pos;

	while (range <= 16)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < range; j++)
			{
				XPos = x_pos;
				YPos = y_pos;
				switch (i)
				{
				case 0:
					XPos += j;
					YPos -= range - j;
					break;
				case 1:
					YPos += j;
					XPos += range - j;
					break;
				case 2:
					XPos -= j;
					YPos += range - j;
					break;
				case 3:
					YPos -= j;
					XPos -= range - j;
					break;
				}
				if (CanPutItem(XPos, YPos))
				{
					m_Item[XPos][YPos].ItemID = item_id;
					m_Item[XPos][YPos].Num = num;
					return;
				}
			}
		}
		++range;
	}
}

void cMap::PutUnit(int x_pos, int y_pos, uint16_t unit_id)
{
	cUnitManager* UnitMgr = (cUnitManager*)m_UnitManager;
	UnitMgr->Create(unit_id, x_pos, y_pos);
}

int cMap::GetMapWidth()
{
	return m_Width;
}

int cMap::GetMapHeight()
{
	return m_Height;
}

aqua::CVector2 cMap::GetStartPoint()
{
	return m_StartPos;
}

aqua::CVector2 cMap::GetStairPos()
{
	return m_StairPos;
}

aqua::CVector2 cMap::GetPointedTile(aqua::CPoint mouse_pos)
{
	bool Negative = false;
	aqua::CVector2 MousePointedPos = ((cCamera*)m_Camera)->GetDrawBasePos();
	MousePointedPos.x += mouse_pos.x;
	MousePointedPos.y += mouse_pos.y;
	Negative = MousePointedPos.x < 0;
	MousePointedPos.x = (float)((int)(MousePointedPos.x / m_tile_size));
	if (Negative)
		MousePointedPos.x -= 1;
	Negative = MousePointedPos.y < 0;
	MousePointedPos.y = (float)((int)(MousePointedPos.y / m_tile_size));
	if (Negative)
		MousePointedPos.y -= 1;
	return MousePointedPos;
}

cMap::TILE_ID cMap::GetTile(int x_pos, int y_pos)
{
	if (x_pos < 0 || x_pos >= m_Width || y_pos < 0 || y_pos >= m_Height)
		return TILE_ID::EMPTY;
	return m_Tile[x_pos][y_pos].TileID;
}

bool cMap::IsWalkableTile(int x_pos, int y_pos)
{
	TILE_ID Tile = GetTile(x_pos, y_pos);

	if (Tile == TILE_ID::EMPTY) return false;
	if (Tile == TILE_ID::WALL) return false;

	return true;
}

bool cMap::CanPutItem(int x_pos, int y_pos)
{
	TILE_ID Tile = GetTile(x_pos, y_pos);

	if (Tile == TILE_ID::EMPTY) return false;
	if (Tile == TILE_ID::WALL) return false;
	if (Tile == TILE_ID::STAIR) return false;

	DroppedItem Item = m_Item[x_pos][y_pos];

	if (Item.ItemID > 0 && Item.Num > 0) return false;

	return true;
}

bool cMap::IsTileVisible(int x_pos, int y_pos)
{
	if (x_pos < 0 || x_pos >= m_Width || y_pos < 0 || y_pos >= m_Height)
		return false;
	return m_Tile[x_pos][y_pos].Visible && m_Tile[x_pos][y_pos].Mapped;
}

void cMap::SetMapped(aqua::CVector2 pos, int radius)
{
	SetMappedFloatRadius(pos, radius + 0.5f);
}

void cMap::SetMappedFloatRadius(aqua::CVector2 pos, float radius)
{
	aqua::CRect Rect = aqua::CRect::ZERO;
	aqua::CVector2 Diff = aqua::CVector2::ZERO;
	std::vector<aqua::CRect> TileRect;
	TileRect.clear();
	Rect.left = (int)(pos.x - radius);
	Rect.right = (int)(pos.x + radius);
	Rect.top = (int)(pos.y - radius);
	Rect.bottom = (int)(pos.y + radius);
	bool Hit = false;
	int Count = 0;
	int LOD = 8;
	aqua::CRect Temp = aqua::CRect::ZERO;
	aqua::CVector2 Pos = aqua::CVector2::ZERO;

	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Height; j++)
			m_Tile[i][j].Visible = false;

	for (int i = Rect.left; i <= Rect.right; i++)
		for (int j = Rect.top; j <= Rect.bottom; j++)
		{
			if (IsWalkableTile(i, j)) continue;

			Temp.left = i * m_tile_size;
			Temp.top = j * m_tile_size;
			Temp.right = Temp.left + m_tile_size - 1;
			Temp.bottom = Temp.top + m_tile_size - 1;

			TileRect.push_back(Temp);
		}
	for (int i = Rect.left; i <= Rect.right; i++)
		for (int j = Rect.top; j <= Rect.bottom; j++)
		{
			if (i < 0 || i >= m_Width || j < 0 || j >= m_Height) continue;

			Diff = aqua::CVector2((float)i, (float)j) - pos;
			if (Diff.Length() > radius) continue;

			if (Diff.Length() < 1.42f)
			{
				m_Tile[i][j].Mapped = true;
				m_Tile[i][j].Visible = true;
				continue;
			}

			if (abs(Diff.x) == abs(Diff.y) && abs(Diff.x) == 0 && abs(Diff.x) == 0)
			{
				Count = (int)max(abs(Diff.x), abs(Diff.y));
				Diff = Diff / (float)Count;
				for (int k = 1; k <= Count; k++)
				{
					Pos = Diff * (float)k + pos;
					if (k == Count)
					{
						m_Tile[i][j].Mapped = true;
						m_Tile[i][j].Visible = true;
						break;
					}
					if (!IsWalkableTile((int)Pos.x, (int)Pos.y)) break;
				}
			}
			else
			{
				for (int k = 0; k < 4; k++)
				{
					aqua::CVector2 PointA = pos * m_tile_size;
					aqua::CVector2 PointB = aqua::CVector2((float)i, (float)j) * m_tile_size;
					PointA.x += (m_tile_size) / 2 - (k / 2);
					PointA.y += (m_tile_size) / 2 - (k % 2);
					PointB.x += (m_tile_size) / 2 - (k / 2);
					PointB.y += (m_tile_size) / 2 - (k % 2);

					Count = 0;
					Hit = false;
					Diff = PointB - PointA;
					Pos = aqua::CVector2::ZERO;

					if (abs(Diff.x) > abs(Diff.y))
					{
						Count = (int)abs(Diff.x);
					}
					else
					{
						Count = (int)abs(Diff.y);
					}
					Diff = Diff / (float)Count;
					for (int m = 1; m <= Count; m += max(m_tile_size / LOD, 1))
					{
						Pos = Diff * (float)m + PointA;
						for (int n = 0; n < TileRect.size(); n++)
						{
							if (Pos.x >= TileRect[n].left &&
								Pos.x <= TileRect[n].right &&
								Pos.y >= TileRect[n].top &&
								Pos.y <= TileRect[n].bottom)
							{
								if (TileRect[n].left / m_tile_size == i &&
									TileRect[n].top / m_tile_size == j)
									continue;
								Hit = true;
							}
							if (Hit) break;
						}
						if (Hit) break;
					}
					if (Hit) continue;
					m_Tile[i][j].Mapped = true;
					m_Tile[i][j].Visible = true;
					break;
				}
			}
		}
}

bool cMap::HitWall(aqua::CVector2 posA, aqua::CVector2 posB)
{
	bool Hit = false;
	int Count = 0;
	int LOD = 8;
	aqua::CVector2 Diff = aqua::CVector2::ZERO;
	aqua::CVector2 Pos = aqua::CVector2::ZERO;
	aqua::CRect Rect = aqua::CRect::ZERO;
	std::vector<aqua::CRect> TileRect;
	TileRect.clear();
	if (posA.x < posB.x)
	{
		Rect.left = (int)posA.x;
		Rect.right = (int)posB.x;
	}
	else
	{
		Rect.left = (int)posB.x;
		Rect.right = (int)posA.x;
	}
	if (posA.y < posB.y)
	{
		Rect.top = (int)posA.y;
		Rect.bottom = (int)posB.y;
	}
	else
	{
		Rect.top = (int)posB.y;
		Rect.bottom = (int)posA.y;
	}
	aqua::CRect Temp = aqua::CRect::ZERO;
	for (int i = Rect.left; i <= Rect.right; i++)
		for (int j = Rect.top; j <= Rect.bottom; j++)
		{
			if (IsWalkableTile(i, j)) continue;

			Temp.left = i * m_tile_size;
			Temp.top = j * m_tile_size;
			Temp.right = Temp.left + m_tile_size - 1;
			Temp.bottom = Temp.top + m_tile_size - 1;

			TileRect.push_back(Temp);
		}
	Diff = posB - posA;

	if (abs(Diff.x) == abs(Diff.y) || abs(Diff.x) == 0 || abs(Diff.y) == 0)
	{
		Count = (int)max(abs(Diff.x), abs(Diff.y));
		Diff = Diff / (float)Count;
		for (int k = 1; k <= Count; k++)
		{
			Pos = Diff * (float)k + posA;
			if (k == Count)
			{
				return false;
			}
			if (!IsWalkableTile((int)Pos.x, (int)Pos.y)) return true;
		}
	}
	else
	{
		for (int k = 0; k < 4; k++)
		{
			aqua::CVector2 PointA = posA * m_tile_size;
			aqua::CVector2 PointB = posB * m_tile_size;
			PointA.x += (m_tile_size) / 2 - (k / 2);
			PointA.y += (m_tile_size) / 2 - (k % 2);
			PointB.x += (m_tile_size) / 2 - (k / 2);
			PointB.y += (m_tile_size) / 2 - (k % 2);

			Diff = PointB - PointA;
			Pos = aqua::CVector2::ZERO;
			Count = 0;
			Hit = false;
			if (abs(Diff.x) > abs(Diff.y))
			{
				Count = (int)abs(Diff.x);
			}
			else
			{
				Count = (int)abs(Diff.y);
			}
			for (int m = 1; m <= Count; m += max(m_tile_size / LOD, 1))
			{
				Pos = (Diff * (float)m) / (float)Count + PointA;
				for (int n = 0; n < TileRect.size(); n++)
				{
					if (Pos.x >= TileRect[n].left &&
						Pos.x <= TileRect[n].right &&
						Pos.y >= TileRect[n].top &&
						Pos.y <= TileRect[n].bottom)
					{
						if (TileRect[n].left / m_tile_size == posB.x &&
							TileRect[n].top / m_tile_size == posB.y)
							continue;
						Hit = true;
					}
					if (Hit) break;
				}
				if (Hit) break;
			}
			if (Hit) continue;
			break;
		}
		return Hit;
	}
	return false;
}

void cMap::SetTile(int x_pos, int y_pos, TILE_ID tile)
{
	if (x_pos < 0 || x_pos >= m_Width || y_pos < 0 || y_pos >= m_Height)
		return;
	m_Tile[x_pos][y_pos].TileID = tile;
}

bool cMap::HasData()
{
	return m_HasData;
}
