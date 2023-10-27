#pragma once
#include "aqua.h"
#include "map/map.h"

class cMapGenerator : public aqua::IGameObject
{
public:
	enum TILE_TYPE
	{
		EMPTY,		//空
		WALL,		//壁
		ROOM,		//部屋
		GATE,		//境界
		CORRIDOR,	//廊下
		START,		//プレイヤー配置位置
		STAIR,		//階段
	};

	//コンストラクタ
	cMapGenerator(aqua::IGameObject* parent);

	//デストラクタ
	~cMapGenerator() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	/*!
	 *	@brief		マップ生成
	 *
	 *	@param[in]	level		敵強さ
	 *	@param[in]	width		マップ横サイズ
	 *	@param[in]	height		マップ縦サイズ
	 *	@param[in]	min_room_siz	最小部屋サイズ
	 *	@param[in]	max_room_siz	最大部屋サイズ
	 *	@param[in]	max_room_cnt	最大部屋生成数
	 *	@param[in]	min_corr_len	最小廊下長さ
	 *	@param[in]	max_corr_len	最大廊下長さ
	 *	@param[in]	max_corr_cnt	最大廊下生成数
	 */
	bool GenerateMap(uint8_t level = 0, uint8_t width = 40, uint8_t height = 30,
		uint8_t min_room_siz = 4, uint8_t max_room_siz = 8, uint16_t max_room_cnt = 10,
		uint8_t min_corr_len = 8, uint8_t max_corr_len = 12, uint16_t max_corr_cnt = 10);

	//マップ生成が完了したか
	bool MapGenerated();

	//マップ取得
	cMap* GetMap();

private:
	enum DIRECTION
	{
		NORTH,	//上
		SOUTH,	//下
		WEST,	//左
		EAST,	//右

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
		aqua::CRect Rect;	 //範囲
		DIRECTION Direction; //位置
		uint16_t RootRoom;	 //根本の部屋
		int  Length;		 //長さ
		bool Used;			 //使用済みか
		bool RootIsCorridor; //根本が廊下か
	};

	/*!
	 *	@brief		生成するマップのパラメータ設定
	 *
	 *	@param[in]	width		マップ横サイズ
	 *	@param[in]	height		マップ縦サイズ
	 *	@param[in]	min_room_siz	最小部屋サイズ
	 *	@param[in]	max_room_siz	最大部屋サイズ
	 *	@param[in]	max_room_cnt	最大部屋生成数
	 *	@param[in]	min_corr_len	最小廊下長さ
	 *	@param[in]	max_corr_len	最大廊下長さ
	 *	@param[in]	max_corr_cnt	最大廊下生成数
	 */
	void SetMapGenParam(uint8_t width, uint8_t height,
		uint8_t min_room_siz, uint8_t max_room_siz, uint16_t max_room_cnt,
		uint8_t min_corr_len, uint8_t max_corr_len, uint16_t max_corr_cnt);

	void Generate();	//マップ生成
	bool CreateRoom(bool first = false);	//部屋を作る

	/*!
	 *	@brief		範囲内が空か調べる 空の場合、trueを返す
	 *
	 *	@param[in]	range			範囲
	 *	@param[in]	wall_is_empty	壁も空白扱い
	 *	@param[in]	room_is_empty	部屋も空白扱い
	 *	@param[in]	corr_is_empty	廊下も空白扱い
	 */
	bool TileEmptyCheck(aqua::CRect range, bool wall_is_empty = false, bool room_is_empty = false, bool corr_is_empty = false);

	/*!
	 *	@brief		敵配置
	 *
	 *	@param[in]	start_room	プレイヤーを配置した部屋
	 */
	void PutEnemy(int start_room);

	//部屋内のランダムな位置を取得(Point型)
	aqua::CPoint GetRandomPointInRoom(int room_no, int space = 0);

	static const uint8_t m_max_width;
	static const uint8_t m_max_height;

	static const uint8_t m_default_width;
	static const uint8_t m_default_height;

	static const int m_room_count_limit;		//上限部屋生成数
	static const int m_corridor_count_limit;	//上限廊下生成数

	bool m_Generating;		//マップ生成中か
	int m_CurrentBranchP;	//現在選択中の分岐点
	int m_Timer;			//タイマー
	int m_TimeCounter;		//カウンター

	uint8_t m_Level;	//敵強さ

	std::vector<Room> m_Room;		//部屋
	std::vector<Room> m_Corridor;	//廊下
	std::vector<Corner> m_Corner;	//曲がり角
	std::vector<BranchPoint> m_BranchPoint;	//分岐点
	aqua::CVector2 m_StartPos;	//開始地点
	aqua::CVector2 m_StairPos;	//階段の位置

	uint8_t** m_Map;				//マップ配列
	uint8_t		m_Width;			//マップ横サイズ
	uint8_t		m_Height;			//マップ縦サイズ
	uint8_t		m_MinRoomSize;		//最小部屋サイズ
	uint8_t		m_MaxRoomSize;		//最大部屋サイズ
	uint8_t		m_MinCorridorLength;//最小廊下長さ
	uint8_t		m_MaxCorridorLength;//最大廊下長さ
	uint16_t	m_MaxRoomCount;		//最大部屋生成数
	uint16_t	m_MaxCorridorCount;	//最大廊下生成数

	cMap* m_MapObj;	//マップ
};