#pragma once
#include "aqua.h"
#include "map/map.h"

class cMapGenerator : public aqua::IGameObject
{
public:
	enum TILE_TYPE
	{
		EMPTY,		//��
		WALL,		//��
		ROOM,		//����
		GATE,		//���E
		CORRIDOR,	//�L��
		START,		//�v���C���[�z�u�ʒu
		STAIR,		//�K�i
	};

	//�R���X�g���N�^
	cMapGenerator(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cMapGenerator() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	/*!
	 *	@brief		�}�b�v����
	 *
	 *	@param[in]	level		�G����
	 *	@param[in]	width		�}�b�v���T�C�Y
	 *	@param[in]	height		�}�b�v�c�T�C�Y
	 *	@param[in]	min_room_siz	�ŏ������T�C�Y
	 *	@param[in]	max_room_siz	�ő啔���T�C�Y
	 *	@param[in]	max_room_cnt	�ő啔��������
	 *	@param[in]	min_corr_len	�ŏ��L������
	 *	@param[in]	max_corr_len	�ő�L������
	 *	@param[in]	max_corr_cnt	�ő�L��������
	 */
	bool GenerateMap(uint8_t level = 0, uint8_t width = 40, uint8_t height = 30,
		uint8_t min_room_siz = 4, uint8_t max_room_siz = 8, uint16_t max_room_cnt = 10,
		uint8_t min_corr_len = 8, uint8_t max_corr_len = 12, uint16_t max_corr_cnt = 10);

	//�}�b�v����������������
	bool MapGenerated();

	//�}�b�v�擾
	cMap* GetMap();

private:
	enum DIRECTION
	{
		NORTH,	//��
		SOUTH,	//��
		WEST,	//��
		EAST,	//�E

		COUNT
	};

	struct Room
	{
		aqua::CRect RoomRect;
		std::list<std::uint16_t> ConnectedCorner;
	};

	struct Corner
	{
		aqua::CVector2	Position;
		unsigned int	RoomNo[2];
		std::list<uint16_t> ConnectedCorner;
	};

	struct BranchPoint
	{
		aqua::CRect Rect;	 //�͈�
		DIRECTION Direction; //�ʒu
		uint16_t RootRoom;	 //���{�̕���
		int  Length;		 //����
		bool Used;			 //�g�p�ς݂�
		bool RootIsCorridor; //���{���L����
	};

	/*!
	 *	@brief		��������}�b�v�̃p�����[�^�ݒ�
	 *
	 *	@param[in]	width		�}�b�v���T�C�Y
	 *	@param[in]	height		�}�b�v�c�T�C�Y
	 *	@param[in]	min_room_siz	�ŏ������T�C�Y
	 *	@param[in]	max_room_siz	�ő啔���T�C�Y
	 *	@param[in]	max_room_cnt	�ő啔��������
	 *	@param[in]	min_corr_len	�ŏ��L������
	 *	@param[in]	max_corr_len	�ő�L������
	 *	@param[in]	max_corr_cnt	�ő�L��������
	 */
	void SetMapGenParam(uint8_t width, uint8_t height,
		uint8_t min_room_siz, uint8_t max_room_siz, uint16_t max_room_cnt,
		uint8_t min_corr_len, uint8_t max_corr_len, uint16_t max_corr_cnt);

	void Generate();	//�}�b�v����
	bool CreateRoom(bool first = false);	//���������

	/*!
	 *	@brief		�͈͓����󂩒��ׂ� ��̏ꍇ�Atrue��Ԃ�
	 *
	 *	@param[in]	range			�͈�
	 *	@param[in]	wall_is_empty	�ǂ��󔒈���
	 *	@param[in]	room_is_empty	�������󔒈���
	 *	@param[in]	corr_is_empty	�L�����󔒈���
	 */
	bool TileEmptyCheck(aqua::CRect range, bool wall_is_empty = false, bool room_is_empty = false, bool corr_is_empty = false);

	/*!
	 *	@brief		�G�z�u
	 *
	 *	@param[in]	start_room	�v���C���[��z�u��������
	 */
	void PutEnemy(int start_room);

	//�������̃����_���Ȉʒu���擾(Point�^)
	aqua::CPoint GetRandomPointInRoom(int room_no, int space = 0);

	static const uint8_t m_max_width;
	static const uint8_t m_max_height;

	static const uint8_t m_default_width;
	static const uint8_t m_default_height;

	static const int m_room_count_limit;		//�������������
	static const int m_corridor_count_limit;	//����L��������

	bool m_Generating;		//�}�b�v��������
	int m_CurrentBranchP;	//���ݑI�𒆂̕���_
	int m_Timer;			//�^�C�}�[
	int m_TimeCounter;		//�J�E���^�[

	uint8_t m_Level;	//�G����

	std::vector<Room> m_Room;		//����
	std::vector<Room> m_Corridor;	//�L��
	std::vector<Corner> m_Corner;	//�Ȃ���p
	std::vector<BranchPoint> m_BranchPoint;	//����_
	aqua::CVector2 m_StartPos;	//�J�n�n�_
	aqua::CVector2 m_StairPos;	//�K�i�̈ʒu

	uint8_t** m_Map;				//�}�b�v�z��
	uint8_t		m_Width;			//�}�b�v���T�C�Y
	uint8_t		m_Height;			//�}�b�v�c�T�C�Y
	uint8_t		m_MinRoomSize;		//�ŏ������T�C�Y
	uint8_t		m_MaxRoomSize;		//�ő啔���T�C�Y
	uint8_t		m_MinCorridorLength;//�ŏ��L������
	uint8_t		m_MaxCorridorLength;//�ő�L������
	uint16_t	m_MaxRoomCount;		//�ő啔��������
	uint16_t	m_MaxCorridorCount;	//�ő�L��������

	cMap* m_MapObj;	//�}�b�v
};