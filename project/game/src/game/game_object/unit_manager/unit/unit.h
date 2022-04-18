#pragma once
#include "aqua.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"

class IUnit : public aqua::IGameObject
{
public:
	enum class DAMAGE_TYPE
	{
		DUMMY,	//��а
		KINETIC,	//����
		THERMAL,	//�M
		ELECTRO,	//�d�C
	};
	enum class DIRECTION
	{
		DUMMY,
		NORTH,
		SOUTH,
		EAST,
		WEST,
	};

	IUnit(aqua::IGameObject* parent, std::string name);

	~IUnit() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void Create(int id);

	void CalcStatus();

	aqua::CVector2 GetPosition();

	void SetPosition(aqua::CVector2 pos);

	void GetMap(cMap* map);

	virtual bool Action();

protected:
	enum class ACTION
	{
		DUMMY,
		WAIT,
		MOVE,
		ATTACK,
	};

	struct status
	{
		std::uint16_t Life;		//��b�ϋv��
		std::uint16_t Cooling;		//��b��p�\��
		std::uint16_t Battery;		//��b�ޯ�ذ�e��
		std::uint16_t Parts;		//��b���i�������
		std::uint16_t Ammo;		//��b�e�򏊎����
		std::int16_t  Resist[3];	//��b�ϐ��l(%)
		std::uint8_t  Inventory;	//��b������ؗe��

		std::uint8_t ArmSlotCount;	//�u�r�v�ۯĐ�
		std::uint8_t ArmorCount;	//�u���b�v�ۯĐ�
		std::uint8_t TranspCount;	//�u�ړ��v�ۯĐ�
		std::uint8_t UtilCount;	//�u���̑��v�ۯĐ�
	};

	virtual bool Wait();

	virtual bool Move();

	virtual bool Attack();

	void CalcBasicEquipmentStat(int id);

	aqua::IGameObject* m_SoundManager;	//������Ȱ�ެ����߲��
	aqua::IGameObject* m_UnitManager;	//�Ư��Ȱ�ެ����߲��
	aqua::IGameObject* m_TextManager;	//÷���Ȱ�ެ����߲��
	aqua::IGameObject* m_UIManager;		//UI�Ȱ�ެ����߲��
	aqua::IGameObject* m_EquipmentDB;	//�����iDB���߲��

	status m_Status;

	aqua::CVector2 m_OnMapPos;	//�}�b�v��ł̈ʒu
	aqua::CVector2 m_Position;	//���ײĂ̈ʒu
	aqua::CSprite m_Sprite;	//�L�����X�v���C�g

	std::string	m_Name;		//���O
	std::uint16_t	m_Life;		//���ݑϋv��
	std::uint16_t	m_MaxLife;	//�ő�ϋv��
	std::int16_t	m_HeatFlow;	//���M�|��p�̑��a
	std::int16_t	m_Heat;		//�M
	std::int16_t	m_BaseHeat;	//�M�����l
	std::uint8_t	m_Inventory;	//������ؗe��
	std::uint16_t	m_Weight;		//�����d��
	std::uint16_t	m_Support;	//�����d�ʏ��(�����ł��Ȃ�����)
	std::int16_t	m_EnergyFlow;	//�d�̗͂��o����
	std::uint16_t	m_Batt;		//�ޯ�ذ�c��
	std::uint16_t	m_MaxBatt;	//�ޯ�ذ�e��
	std::uint16_t	m_Parts;		//�������i
	std::uint16_t	m_MaxParts;	//���i�������
	std::uint16_t	m_Ammo;		//�����e��
	std::uint16_t	m_MaxAmmo;	//�e�򏊎����
	std::int16_t	m_Resist[3];	//�ϐ��l(%)
	std::int16_t	m_Protection;	//�h���
	std::uint8_t	m_SightRange;	//���E���a

	std::vector<uint16_t> m_Weapon;	//�������Ă��镐��
	std::vector<uint16_t> m_Armor;	//�������Ă��鑕�b
	std::vector<uint16_t> m_Transp;	//�������Ă���ړ�
	std::vector<uint16_t> m_Util;	//�������Ă��鑕���i

	cMap* m_MapObj;
	IGameObject* m_Camera;

	bool m_DidAction;
	ACTION m_DesiredAction;
	DIRECTION m_MoveTo;
};