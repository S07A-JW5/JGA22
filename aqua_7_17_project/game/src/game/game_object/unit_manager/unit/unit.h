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
		NORTH,	//��
		SOUTH,	//��
		EAST,	//�E
		WEST,	//��

		NORTH_EAST,//�E��
		NORTH_WEST,//����
		SOUTH_EAST,//�E��
		SOUTH_WEST,//����

		COUNT,
		DUMMY = 0xff
	};

	enum class STATUS
	{
		LIFE,	//�̗�
		HEAT,	//�M
		BATT,	//�ޯ�ذ
		PARTS,	//���i
		AMMO,	//�e��
	};

	struct EquippedStat
	{
		std::string	Equipment[16];	//�����i��
		std::uint8_t	Count;			//�����X���b�g��
	};

	struct InventoryStat
	{
		std::string	Item[16];	//�A�C�e����
		std::uint8_t	Count;		//�C���x���g���e��
	};

	//�R���X�g���N�^
	IUnit(aqua::IGameObject* parent, std::string name);

	//�f�X�g���N�^
	~IUnit() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�j��
	void Finalize() override;

	/*!
	 *	@brief	�L��������
	 *
	 *	@param[in]	id		�L����DB����ǂݍ���ID
	 *	@param[in]	unit_no	���j�b�g�ԍ�
	 */
	void Create(int id, int unit_no);

	/*!
	 *	@brief	�X�e�[�^�X�v�Z
	 *
	 *	@param[in]	reset_param	���ݒl�����Z�b�g���邩
	 */
	virtual void CalcStatus(bool reset_param = false);

	//���݈ʒu�擾
	aqua::CVector2 GetPosition();

	//�ʒu�ݒ�
	void SetPosition(aqua::CVector2 pos);

	//�}�b�v�I�u�W�F�N�g�ݒ�
	void SetMapObj(cMap* map);

	//�_���[�W���󂯂�
	bool TakeDamage(int damage, IUnit::DAMAGE_TYPE type);

	//�s���ς݂����m�F
	bool DidAction();

	//�s���ς݃t���O��ݒ�
	void SetActFlag(bool flag);

	//�X�e�[�^�X�l�擾
	int GetStatus(IUnit::STATUS stat);

	//�����i���e�擾
	EquippedStat GetEquipped();

	//�C���x���g�����e�擾
	InventoryStat GetInventory();

	//�ϋv�͂�0�ɂȂ������̏���
	virtual void Dead();

	//�s��
	virtual bool Action();

protected:
	enum class ACTION
	{
		DUMMY,
		WAIT,	//�ҋ@
		MOVE,	//�ړ�
		ATTACK,	//�U��
		ITEM,	//���юg�p
	};

	enum class ITEM_USE_MODE
	{
		DUMMY,
		USE,		//����
		DISCARD,	//�j���i���̏�ɗ��Ƃ��j
		SWITCH,	//���ցi��Ԍ��Ɉړ��j
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
		std::uint8_t	EffectID;		//�U���G�t�F�N�gID
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

	//�ҋ@
	virtual bool Wait();

	//�ړ�
	virtual bool Move();

	//�U��
	virtual bool Attack(aqua::CVector2 pos);

	//�A�C�e���g�p
	virtual bool Item(std::int8_t slot);

	//�G�t�F�N�g�Đ��������ׂ�
	virtual bool EffectPlaying();

	//�ړ��\�����ׂ�
	bool CanMove();

	//�ړ���̈ʒu�擾
	aqua::CVector2 GetMovedPos();

	//�����i�̔\�͂��X�e�[�^�X�ɉ��Z
	void CalcEquipmentStat(int id);

	aqua::IGameObject* m_EffectManager;	//�̪���Ȱ�ެ����߲��
	aqua::IGameObject* m_SoundManager;	//������Ȱ�ެ����߲��
	aqua::IGameObject* m_UnitManager;	//�Ư��Ȱ�ެ����߲��
	aqua::IGameObject* m_TextManager;	//÷���Ȱ�ެ����߲��
	aqua::IGameObject* m_UIManager;		//UI�Ȱ�ެ����߲��
	aqua::IGameObject* m_EquipmentDB;	//�����iDB���߲��
	aqua::IGameObject* m_ItemDataBase;	//����DB���߲��
	aqua::IGameObject* m_UnitDataBase;	//�Ư�DB���߲��

	status m_Status;	//�X�e�[�^�X

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

	std::list<ItemStat> m_ItemList;	//�����i

	std::uint8_t	m_WeaponCount;		//�������Ă��镐��̐�
	std::uint8_t	m_AttackingWPN;		//���ݍU�����Ă��镐��
	WeaponStat	m_Weapon[16];			//�������Ă��镐��
	std::uint16_t	m_Equipment[16];		//�������Ă��鑕���i
	std::vector<uint16_t>	 m_Head;		//  ������
	std::vector<uint16_t>	 m_Arm;		//�E�f����
	std::vector<uint16_t>	 m_Chest;	//��������
	std::vector<uint16_t>	 m_Back;		//�w������
	std::vector<uint16_t>	 m_Leg;		//  �r����
	std::vector<uint16_t>	 m_Shlder;	//  ������
	std::vector<uint16_t>	 m_Card;		//���ޑ���

	cMap* m_MapObj;		//�}�b�v
	IGameObject* m_Camera;	//�J����
	int m_UnitNo;			//�ƯĔԍ��i�������A�ԁj

	IGameObject* m_PlayingEffect;	//�Đ����̍U���̪��

	bool m_DidAction;			//�s���ς݃t���O
	ACTION m_DesiredAction;	//�s���\��̍s��
	DIRECTION m_MoveTo;		//�ړ�����
	std::int8_t m_UseItemSlot;	//���ꂩ��g�����ѽۯĔԍ�
	ITEM_USE_MODE m_ItemMode;	//�A�C�e���g�p���[�h
};