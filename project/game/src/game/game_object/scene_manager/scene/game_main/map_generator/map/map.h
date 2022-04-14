#pragma once
#include "aqua.h"

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

	struct DroppedItem
	{
		unsigned int ItemID;
		unsigned int Num;
	};

	cMap(aqua::IGameObject* parent, std::string name = "Map");

	~cMap() = default;

	void Initialize() override;
	void Initialize(int width, int height, std::uint8_t** mapdata,
		aqua::CVector2 start, aqua::CVector2 stair);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	cMap::DroppedItem GatherItem(int x_pos, int y_pos);

	void PutItem(int x_pos, int y_pos, unsigned int item_id, unsigned int num = 1);

	void PutUnit(int x_pos, int y_pos, unsigned int unit_id);

	aqua::CVector2 GetStartPoint();
	aqua::CVector2 GetStairPos();

	cMap::TILE_ID GetTile(int x_pos, int y_pos);
	bool IsWalkableTile(int x_pos, int y_pos);
	bool IsBreakableTile(int x_pos, int y_pos);

	bool HasData();

	void FloorChange();

	void SetTile(int x_pos, int y_pos, TILE_ID tile);

private:
	bool m_HasData;
	std::uint8_t	m_Width;		//�}�b�v�̉��T�C�Y
	std::uint8_t	m_Height;		//�}�b�v�̏c�T�C�Y
	TILE_ID** m_Tile;		//�}�b�v�^�C���z��
	DroppedItem** m_Item;		//�A�C�e���z��
	aqua::CVector2 m_StartPos;	//�J�n�n�_
	aqua::CVector2 m_StairPos;	//�K�i�̈ʒu
	aqua::CSprite m_WallSprite;
	aqua::CSprite m_TileSprite;
	aqua::CSprite m_StairSprite;
	aqua::CVector2 m_TileDrawPos;
	aqua::CRect m_DrawArea;
	IGameObject* m_Camera;
};
