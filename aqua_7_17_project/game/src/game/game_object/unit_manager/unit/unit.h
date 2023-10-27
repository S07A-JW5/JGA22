#pragma once
#include "aqua.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map/map.h"
#include "game/tools/tools.h"

class IUnit : public aqua::IGameObject
{
public:
	enum class DAMAGE_TYPE
	{
		DUMMY,		//�_�~�[
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
		BATT,	//�d�́i�o�b�e���[�j
		PARTS,	//���i
		AMMO,	//�e��
	};

	struct EquippedStat
	{
		std::string	Equipment[16];	//�����i��
		uint8_t		Count;			//�����X���b�g��
	};

	struct InventoryStat
	{
		std::string	Item[16];	//�A�C�e����
		uint8_t		Count;		//�C���x���g���e��
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

	//���
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
		SWITCH,		//���ցi��Ԍ��Ɉړ��j
	};

	struct status
	{
		uint16_t ID;		//���j�b�gID
		uint16_t Life;		//��b�ϋv��
		uint16_t Cooling;	//��b��p�\��
		uint16_t Battery;	//��b�d�͗e��
		uint16_t Parts;		//��b���i�������
		uint16_t Ammo;		//��b�e�򏊎����
		int16_t  Resist[3];	//��b�ϐ��l(%)
		uint8_t  Inventory;	//��b�C���x���g���e��

		uint8_t HeadCount;	//�u���v�X���b�g��
		uint8_t ArmCount;	//�u�r�v�X���b�g��
		uint8_t ChestCount;	//�u�����v�X���b�g��
		uint8_t BackCount;	//�u�w���v�X���b�g��
		uint8_t LegCount;	//�u�r�v�X���b�g��
		uint8_t ShlderCount;//�u���v�X���b�g��
		uint8_t CardCount;	//�u�g���v�X���b�g��
		uint8_t EquipCount;	//�������X���b�g��
	};

	struct WeaponStat
	{
		uint16_t	ID;			//�����iID(0�͋�)
		std::string	Name;		//�����i�̖��O
		DAMAGE_TYPE	DamageType;	//�_���[�W����
		Dice::DiceRollData DmgRollData;//�_���[�W���[���f�[�^
		uint8_t		EffectID;	//�U���G�t�F�N�gID
		uint8_t		Range;		//�˒�
		uint8_t		Heat;		//���M��
		uint8_t		Ammo;		//�e������
		uint8_t		Energy;		//����d��
	};

	struct ItemStat
	{
		uint16_t	ID;		//�A�C�e��ID(0�͋�)
		std::string	Name;	//�A�C�e����
		uint8_t		Amount;	//�A�C�e���̐�
		bool		IsEquipment;	//�����i�ł��邩
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

	IGameObject* m_EffectManager;	//�G�t�F�N�g�}�l�[�W���̃|�C���^
	IGameObject* m_SoundManager;	//�T�E���h�}�l�[�W���̃|�C���^
	IGameObject* m_UnitManager;		//���j�b�g�}�l�[�W���̃|�C���^
	IGameObject* m_TextManager;		//�e�L�X�g�}�l�[�W���̃|�C���^
	IGameObject* m_UIManager;		//UI�}�l�[�W���̃|�C���^
	IGameObject* m_EquipmentDB;		//�����iDB�̃|�C���^
	IGameObject* m_ItemDataBase;	//�A�C�e��DB�̃|�C���^
	IGameObject* m_UnitDataBase;	//���j�b�gDB�̃|�C���^

	status m_Status;	//�X�e�[�^�X

	aqua::CVector2 m_OnMapPos;	//�}�b�v��ł̈ʒu
	aqua::CVector2 m_Position;	//�X�v���C�g�ʒu
	aqua::CSprite m_Sprite;		//�L�����X�v���C�g

	std::string	m_Name;			//���O
	uint16_t	m_Life;			//���ݑϋv��
	uint16_t	m_MaxLife;		//�ő�ϋv��
	int16_t		m_HeatFlow;		//���M�|��p�̑��a
	int16_t		m_Heat;			//�M
	int16_t		m_BaseHeat;		//�M�����l
	uint8_t		m_Inventory;	//�C���x���g���e��
	uint16_t	m_Weight;		//�����d��
	uint16_t	m_Support;		//�����d�ʏ��
	int16_t		m_EnergyFlow;	//�d�̗͂��o����
	uint16_t	m_Batt;			//�d�͎c��
	uint16_t	m_MaxBatt;		//�d�͗e��
	uint16_t	m_Parts;		//�������i
	uint16_t	m_MaxParts;		//���i�������
	uint16_t	m_Ammo;			//�����e��
	uint16_t	m_MaxAmmo;		//�e�򏊎����
	int16_t		m_Resist[3];	//�ϐ��l(%)
	int16_t		m_Protection;	//�h���
	uint8_t		m_SightRange;	//���E���a

	std::list<ItemStat> m_ItemList;	//�����i

	uint8_t			m_WeaponCount;		//�������Ă��镐��̐�
	uint8_t			m_AttackingWPN;		//���ݍU�����Ă��镐��
	WeaponStat		m_Weapon[16];		//�������Ă��镐��
	uint16_t		m_Equipment[16];	//�������Ă��鑕���i
	std::vector<uint16_t>	 m_Head;	//������
	std::vector<uint16_t>	 m_Arm;		//�E�f����
	std::vector<uint16_t>	 m_Chest;	//��������
	std::vector<uint16_t>	 m_Back;	//�w������
	std::vector<uint16_t>	 m_Leg;		//�r����
	std::vector<uint16_t>	 m_Shlder;	//������
	std::vector<uint16_t>	 m_Card;	//�g������

	cMap*			m_MapObj;	//�}�b�v
	IGameObject*	m_Camera;	//�J����
	int				m_UnitNo;	//���j�b�g�ԍ��i�������A�ԁj

	IGameObject* m_PlayingEffect;	//�Đ����̍U���G�t�F�N�g

	bool m_DidAction;			//�s���ς݃t���O
	ACTION m_DesiredAction;	//�s���\��̍s��
	DIRECTION m_MoveTo;		//�ړ�����
	std::int8_t m_UseItemSlot;	//���ꂩ��g���A�C�e���X���b�g�ԍ�
	ITEM_USE_MODE m_ItemMode;	//�A�C�e���g�p���[�h
};
