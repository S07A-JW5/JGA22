#pragma once
#include "aqua.h"

class cMap : public aqua::IGameObject
{
public:
	static const int m_tile_size = 16;

	enum class TILE_ID
	{
		EMPTY,		//��
		WALL,		//��
		ROOM,		//����
		GATE,		//���E
		CORRIDOR,	//�L��
		STAIR,		//�K�i
	};

	struct TILE
	{
		TILE_ID TileID;		//�^�C�����
		bool Mapped;		//�}�b�s���O�t���O
		bool Visible;		//���t���O
	};

	struct DroppedItem
	{
		unsigned int ItemID;	//�A�C�e��ID
		unsigned int Num;		//����
	};

	//�R���X�g���N�^
	cMap(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cMap() = default;

	//������
	void Initialize() override;
	void Initialize(int width, int height, std::uint8_t** mapdata,
		aqua::CVector2 start, aqua::CVector2 stair);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//�A�C�e�����E��
	cMap::DroppedItem GatherItem(int x_pos, int y_pos);

	//�A�C�e���ݒu
	void PutItem(int x_pos, int y_pos, unsigned int item_id, unsigned int num = 1);

	//���j�b�g�z�u
	void PutUnit(int x_pos, int y_pos, uint16_t unit_id);

	//�}�b�v�̉��T�C�Y�擾
	int GetMapWidth();

	//�}�b�v�̏c�T�C�Y�擾
	int GetMapHeight();

	//�J�n�ʒu�擾
	aqua::CVector2 GetStartPoint();

	//�K�i�̈ʒu�擾
	aqua::CVector2 GetStairPos();

	//�}�E�X�J�[�\���̈ʒu�ɂ���}�X���擾
	aqua::CVector2 GetPointedTile(aqua::CPoint mouse_pos);

	//�w��ʒu�ɂ���}�X�̎�ނ��擾
	cMap::TILE_ID GetTile(int x_pos, int y_pos);

	//�w��ʒu�ɂ���}�X�����s�\�����擾
	bool IsWalkableTile(int x_pos, int y_pos);

	//�w��ʒu�ɂ���}�X�ɃA�C�e����ݒu�\�����擾
	bool CanPutItem(int x_pos, int y_pos);

	//�w��ʒu�ɂ���}�X�����F�\�����擾
	bool IsTileVisible(int x_pos, int y_pos);

	//�w��͈͓����}�b�s���O
	void SetMapped(aqua::CVector2 pos, int radius);

	//�w��͈͓����}�b�s���O
	void SetMappedFloatRadius(aqua::CVector2 pos, float radius);

	//�w��ʒu�Ԃɕǂ����邩���擾
	bool HitWall(aqua::CVector2 posA, aqua::CVector2 posB);

	//�w��ʒu�̃}�X�̎�ނ�ύX
	void SetTile(int x_pos, int y_pos, TILE_ID tile);

	bool HasData();
private:
	bool m_HasData;
	uint8_t	m_Width;		//�}�b�v�̉��T�C�Y
	uint8_t	m_Height;		//�}�b�v�̏c�T�C�Y
	TILE** m_Tile;			//�}�b�v�^�C���z��
	DroppedItem** m_Item;		//�A�C�e���z��
	aqua::CVector2 m_StartPos;	//�J�n�n�_
	aqua::CVector2 m_StairPos;	//�K�i�̈ʒu
	aqua::CSprite m_ItemSprite;	//�A�C�e���X�v���C�g
	aqua::CSprite m_WallSprite;	//�ǃX�v���C�g
	aqua::CSprite m_TileSprite;	//���X�v���C�g
	aqua::CSprite m_StairSprite;	//�K�i�X�v���C�g
	aqua::CVector2 m_TileDrawPos;	//�^�C���`��ʒu
	aqua::CRect m_DrawArea;		//�`��͈�
	IGameObject* m_Camera;		//�J�����̃|�C���^
	IGameObject* m_UnitManager;	//���j�b�g�}�l�[�W���̃|�C���^
};
