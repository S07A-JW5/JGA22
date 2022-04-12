#include "map.h"
#include "../map_generator.h"
#include "game/game_object/camera/camera.h"

cMap::cMap(aqua::IGameObject* parent, std::string name)
	: aqua::IGameObject(parent, name, "Map")
	, m_HasData(false)
	, m_Width(0)
	, m_Height(0)
	, m_Tile(nullptr)
	, m_Item(nullptr)
	, m_Camera(nullptr)
	, m_StartPos(aqua::CVector2::ZERO)
	, m_StairPos(aqua::CVector2::ZERO)
	, m_DrawArea(aqua::CRect::ZERO)
{
}

void cMap::Initialize()
{
	m_WallSprite.Create("data\\texture\\map\\wall.png");
	m_TileSprite.Create("data\\texture\\map\\tile.png");
	m_StairSprite.Create("data\\texture\\map\\stair.png");
	m_Camera = aqua::FindGameObject("Camera");
	aqua::GetWindowWidth();
}

void cMap::Initialize(int width, int height, std::uint8_t** mapdata,
	aqua::CVector2 start, aqua::CVector2 stair)
{
	Initialize();

	AQUA_SAFE_DELETE_ARRAY(m_Tile);
	AQUA_SAFE_DELETE_ARRAY(m_Item);

	m_HasData = true;

	m_Width = width;
	m_Height = height;

	m_Tile = new TILE_ID * [m_Width];
	for (int i = 0; i < width; i++)
		m_Tile[i] = new TILE_ID[m_Height];

	m_Item = new DroppedItem * [m_Width];
	for (int i = 0; i < width; i++)
		m_Item[i] = new DroppedItem[m_Height];

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			switch ((cMapGenerator::TILE_TYPE)mapdata[i][j])
			{
			case cMapGenerator::TILE_TYPE::ROOM:
			case cMapGenerator::TILE_TYPE::START:
				m_Tile[i][j] = TILE_ID::ROOM;
				break;
			case cMapGenerator::TILE_TYPE::GATE:
				m_Tile[i][j] = TILE_ID::GATE;
				break;
			case cMapGenerator::TILE_TYPE::CORRIDOR:
				m_Tile[i][j] = TILE_ID::CORRIDOR;
				break;
			case cMapGenerator::TILE_TYPE::STAIR:
				m_Tile[i][j] = TILE_ID::STAIR;
				break;
			default:
				m_Tile[i][j] = TILE_ID::WALL;
				break;
			}
			m_Item[i][j].ItemID = 0;
			m_Item[i][j].Num = 0;
		}
	m_StartPos = start;
	m_StairPos = stair;
}

void cMap::Update()
{
	if (m_GameObjectState == aqua::GAME_OBJECT_STATE::DEAD) return;

	cCamera* Camera = (cCamera*)m_Camera;
	aqua::CVector2 DrawBasePos = Camera->GetDrawBasePos();
	m_DrawArea.left = DrawBasePos.x / m_tile_size-1;
	m_DrawArea.top = DrawBasePos.y / m_tile_size-1;
	m_DrawArea.right = m_DrawArea.left + aqua::GetWindowWidth() / m_tile_size + 1;
	m_DrawArea.bottom = m_DrawArea.top + aqua::GetWindowHeight() / m_tile_size + 1;
	m_TileDrawPos.x = m_DrawArea.left * m_tile_size - DrawBasePos.x;
	m_TileDrawPos.y = m_DrawArea.top * m_tile_size - DrawBasePos.y;
}

void cMap::Draw()
{
	if (!m_HasData) return;
	if (m_GameObjectState == aqua::GAME_OBJECT_STATE::DEAD) return;	
	
	aqua::CVector2 DrawPos = aqua::CVector2::ZERO;
	for (int i = m_DrawArea.left; i <= m_DrawArea.right; i++)
		for (int j = m_DrawArea.top; j <= m_DrawArea.bottom; j++)
		{
			DrawPos = m_TileDrawPos;
			DrawPos.x += m_tile_size * (i - m_DrawArea.left);
			DrawPos.y += m_tile_size * (j - m_DrawArea.top);

			if (i < 0 || i >= m_Width || j < 0 || j >= m_Height)
			{
				m_WallSprite.position = DrawPos;
				m_WallSprite.Draw();
				continue;
			}

			switch (m_Tile[i][j])
			{
			case cMap::TILE_ID::WALL:
				m_WallSprite.position = DrawPos;
				m_WallSprite.Draw();
				break;
			case cMap::TILE_ID::ROOM:
			case cMap::TILE_ID::GATE:
			case cMap::TILE_ID::CORRIDOR:
				m_TileSprite.position = DrawPos;
				m_TileSprite.Draw();
				break;
			case cMap::TILE_ID::STAIR:
				m_StairSprite.position = DrawPos;
				m_StairSprite.Draw();
				break;
			}
		}
}

void cMap::Finalize()
{
	m_HasData = false;
	m_WallSprite.Delete();
	m_TileSprite.Delete();
	m_StairSprite.Delete();
	AQUA_SAFE_DELETE_ARRAY(m_Tile);
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
	m_Item[x_pos][y_pos].ItemID = item_id;
	m_Item[x_pos][y_pos].Num = num;
}

void cMap::PutUnit(int x_pos, int y_pos, unsigned int unit_id)
{
}

aqua::CVector2 cMap::GetStartPoint()
{
	return m_StartPos;
}

aqua::CVector2 cMap::GetStairPos()
{
	return m_StairPos;
}

cMap::TILE_ID cMap::GetTile(int x_pos, int y_pos)
{
	if (x_pos < 0 || x_pos >= m_Width || y_pos < 0 || y_pos >= m_Height)
		return TILE_ID::WALL;
	return m_Tile[x_pos][y_pos];
}

bool cMap::IsWalkableTile(int x_pos, int y_pos)
{
	if (x_pos < 0 || x_pos >= m_Width || y_pos < 0 || y_pos >= m_Height)
		return false;
	return m_Tile[x_pos][y_pos] != TILE_ID::WALL;
}

bool cMap::IsBreakableTile(int x_pos, int y_pos)
{
	if (x_pos < 0 || x_pos >= m_Width || y_pos < 0 || y_pos >= m_Height)
		return false;
	return m_Tile[x_pos][y_pos] == TILE_ID::WALL;
}

void cMap::FloorChange()
{
}

bool cMap::HasData()
{
	return m_HasData;
}

void cMap::SetTile(int x_pos, int y_pos, TILE_ID tile)
{
	if (x_pos < 0 || x_pos >= m_Width || y_pos < 0 || y_pos >= m_Height)
		return;
	m_Tile[x_pos][y_pos] = tile;
}
