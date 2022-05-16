#pragma once
#include "aqua.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"
#include "game/tools/tools.h"

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
		NORTH,
		SOUTH,
		EAST,
		WEST,

		COUNT,
		DUMMY = 0xff
	};

	enum class STATUS
	{
		LIFE,
		HEAT,
		BATT,
		PARTS,
		AMMO,
	};

	struct EquippedStat
	{
		std::string	Equipment[16];
		std::uint8_t	Count;
	};

	struct InventoryStat
	{
		std::string	Item[16];
		std::uint8_t	Count;
	};

	IUnit(aqua::IGameObject* parent, std::string name);

	~IUnit() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void Create(int id, int unit_no);

	virtual void CalcStatus();

	aqua::CVector2 GetPosition();

	void SetPosition(aqua::CVector2 pos);

	void GetMap(cMap* map);

	bool TakeDamage(int damage, IUnit::DAMAGE_TYPE type);

	bool DidAction();

	void SetActFlag(bool flag);

	int GetStatus(IUnit::STATUS stat);

	EquippedStat GetEquipped();

	InventoryStat GetInventory();

	void Dead();

	virtual bool Action();

protected:
	enum class ACTION
	{
		DUMMY,
		WAIT,
		MOVE,
		ATTACK,
		ITEM,
	};

	enum class ITEM_USE_MODE
	{
		DUMMY,
		USE,
		DISCARD,
		SWITCH,
	};

	struct status
	{
		std::uint16_t	ID;			//�Ư�ID
		std::uint16_t	Life;		//��b�ϋv��
		std::uint16_t	Cooling;		//��b��p�\��
		std::uint16_t	Battery;		//��b�ޯ�ذ�e��
		std::uint16_t	Parts;		//��b���i�������
		std::uint16_t	Ammo;		//��b�e�򏊎����
		std::int16_t	Resist[3];	//��b�ϐ��l(%)
		std::uint8_t	Inventory;	//��b������ؗe��

		std::uint8_t HeadCount;	//�u���v�ۯĐ�
		std::uint8_t ArmCount;		//�u�r�v�ۯĐ�
		std::uint8_t HandCount;	//�u��v�ۯĐ�
		std::uint8_t ChestCount;	//�u�����v�ۯĐ�
		std::uint8_t BackCount;	//�u�w���v�ۯĐ�
		std::uint8_t LegCount;		//�u�r�v�ۯĐ�
		std::uint8_t ShlderCount;	//�u���v�ۯĐ�
		std::uint8_t CardCount;	//�u�g�����ށv�ۯĐ�
		std::uint8_t EquipCount;	//�������X���b�g��
	};

	struct WeaponStat
	{
		std::uint16_t	ID;			//�����iID(0�͋�)
		std::string	Name;		//�����i�̖��O
		DAMAGE_TYPE	DamageType;	//��Ұ�ޑ���
		Dice::DiceRollData DmgRollData;//��Ұ��۰��ް�
		std::uint8_t	Range;		//�˒�
		std::uint8_t	Heat;		//���M��
		std::uint8_t	Ammo;		//�e������
		std::uint8_t	Energy;		//�����ޯ�ذ
	};

	struct ItemStat
	{
		std::uint16_t	ID;			//�A�C�e��ID(0�͋�)
		std::string	Name;		//�A�C�e����
		std::uint8_t	Amount;		//�A�C�e���̐�
		bool			IsEquipment;	//�����i�ł��邩
	};

	virtual bool Wait();

	virtual bool Move();

	virtual bool Attack(aqua::CVector2 pos);

	virtual bool Item(std::int8_t slot, ITEM_USE_MODE mode = ITEM_USE_MODE::USE);

	virtual bool PlayEffect();

	void CalcEquipmentStat(int id);

	aqua::IGameObject* m_EffectManager;	//�̪���Ȱ�ެ����߲��
	aqua::IGameObject* m_SoundManager;	//������Ȱ�ެ����߲��
	aqua::IGameObject* m_UnitManager;	//�Ư��Ȱ�ެ����߲��
	aqua::IGameObject* m_TextManager;	//÷���Ȱ�ެ����߲��
	aqua::IGameObject* m_UIManager;		//UI�Ȱ�ެ����߲��
	aqua::IGameObject* m_EquipmentDB;	//�����iDB���߲��
	aqua::IGameObject* m_ItemDataBase;	//����DB���߲��
	aqua::IGameObject* m_UnitDataBase;	//�Ư�DB���߲��

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

	std::uint8_t	m_Coverage;

	std::list<ItemStat> m_ItemList;

	std::uint8_t	m_WeaponCount;
	std::uint8_t	m_AttackingWPN;
	WeaponStat	m_Weapon[16];			//�������Ă��镐��
	std::uint16_t	m_Equipment[16];		//�������Ă��鑕���i
	std::vector<uint16_t>	 m_Head;		//
	std::vector<uint16_t>	 m_Arm;		//
	std::vector<uint16_t>	 m_Hand;		//
	std::vector<uint16_t>	 m_Chest;	//
	std::vector<uint16_t>	 m_Back;		//
	std::vector<uint16_t>	 m_Leg;		//
	std::vector<uint16_t>	 m_Shlder;	//
	std::vector<uint16_t>	 m_Card;		//

	cMap* m_MapObj;
	IGameObject* m_Camera;
	int m_UnitNo;

	IGameObject* m_PlayingEffect;

	bool m_DidAction;
	ACTION m_DesiredAction;
	DIRECTION m_MoveTo;
	std::int8_t m_UseItemSlot;
	ITEM_USE_MODE m_ItemMode;
};