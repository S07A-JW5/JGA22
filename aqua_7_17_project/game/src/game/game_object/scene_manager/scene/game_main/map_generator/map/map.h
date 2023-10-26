#pragma once
#include "aqua.h"

class cMap : public aqua::IGameObject
{
public:
	static const int m_tile_size = 16;

	enum class TILE_ID
	{
		EMPTY,	//��
		WALL,	//��
		ROOM,	//����
		GATE,	//���E
		CORRIDOR,	//�L��
		STAIR,	//�K�i
	};

	struct TILE
	{
		TILE_ID TileID;	//�^�C�����
		bool Mapped;		//ϯ��ݸރt���O
		bool Visible;		//���t���O
	};

	struct DroppedItem
	{
		unsigned int ItemID;	//�A�C�e��ID
		unsigned int Num;		//����
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
	std::uint8_t	m_Width;		//�}�b�v�̉��T�C�Y
	std::uint8_t	m_Height;		//�}�b�v�̏c�T�C�Y
	TILE** m_Tile;			//�}�b�v�^�C���z��
	DroppedItem** m_Item;		//�A�C�e���z��
	aqua::CVector2 m_StartPos;	//�J�n�n�_
	aqua::CVector2 m_StairPos;	//�K�i�̈ʒu
	aqua::CSprite m_ItemSprite;	//�A�C�e���X�v���C�g
	aqua::CSprite m_WallSprite;	//�ǃX�v���C�g
	aqua::CSprite m_TileSprite;	//���X�v���C�g
	aqua::CSprite m_StairSprite;	//�K�i�X�v���C�g
	aqua::CVector2 m_TileDrawPos;	//�^�C���`��ʒu
	aqua::CRect m_DrawArea;	//�`��͈�
	IGameObject* m_Camera;		//�J����
	IGameObject* m_UnitManager;	//�Ư��Ȱ�ެ�
};
