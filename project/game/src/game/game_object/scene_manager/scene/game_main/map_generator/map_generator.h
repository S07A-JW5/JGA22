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

	bool GenerateMap(int width = 40, int height = 30,
		int min_room_siz = 4, int max_room_siz = 8, int max_room_cnt = 10,
		int min_corr_len = 8, int max_corr_len = 12, int max_corr_cnt = 10);

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
		aqua::CRect Rect;
		DIRECTION   Direction;
		bool Used;
		bool RootIsCorridor;
	};

	void SetMapGenParam(int width = 40, int height = 30,
		int min_room_siz = 4, int max_room_siz = 8, int max_room_cnt = 10,
		int min_corr_len = 8, int max_corr_len = 12, int max_corr_cnt = 10);

	void Generate(bool step = false);
	bool CreateRoom(bool first = false);	//���������
	bool TileEmptyCheck(aqua::CRect Range);	//�͈͓����󂩒��ׂ�
	void PutEnemy(int start_room, int id = 1);
	aqua::CPoint GetRandomPointInRoom(int room_no);
	aqua::CVector2 GetRandomPositionInRoom(int room_no);

	static const int m_max_width = 255;
	static const int m_max_height = 255;

	static const int m_default_width;
	static const int m_default_height;

	bool m_Generating;
	int m_CurrentBranchP;
	int m_CorridorCount;
	int m_Timer;
	int m_TimeCounter;
	int m_FrameCounter;

	aqua::CBoxPrimitive m_Tile[m_max_width][m_max_height];
	std::vector<aqua::CRect> m_Room;
	std::vector<BranchPoint> m_BranchPoint;
	aqua::CVector2 m_StartPos;	//�J�n�n�_
	aqua::CVector2 m_StairPos;	//�K�i�̈ʒu

	std::uint8_t** m_Map;			//�}�b�v�z��
	std::uint8_t  m_Width;			//�}�b�v�̉��T�C�Y
	std::uint8_t  m_Height;		//�}�b�v�̏c�T�C�Y
	std::uint8_t  m_MinRoomSize;	//�����̈�ӂ̍ŏ�����
	std::uint8_t  m_MaxRoomSize;	//�����̈�ӂ̍ő咷��
	std::uint8_t  m_MinCorridorLen;	//�L���̍ŏ�����
	std::uint8_t  m_MaxCorridorLen;	//�L���̍ő咷��
	std::uint16_t m_MaxRoomCount;	//�����̍ő吔
	std::uint16_t m_MaxCorridorCount;//�L���̍ő吔

	cMap* m_MapObj;
};