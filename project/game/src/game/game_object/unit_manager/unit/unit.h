#pragma once
#include "aqua.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/scene_manager/scene/game_main/map_generator/map_generator.h"

class IUnit : public aqua::IGameObject
{
public:
	enum DAMAGE_TYPE
	{
		KINETIC,
		THERMAL,
		ELECTRO,
	};

	IUnit(aqua::IGameObject* parent, std::string name);

	~IUnit() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	virtual void Create(std::string file_name);

	aqua::CVector2 GetPosition();

	void SetPosition(aqua::CVector2 pos);

	void GetMap(cMap* map);

protected:
	struct status
	{
		char		name[16];	//�L������

		std::uint16_t Life;		//��b�ϋv��
		std::uint16_t Cooling;	//��b��p�\��
		std::uint16_t Battery;	//��b�ޯ�ذ�e��
		std::uint16_t Parts;	//��b���i�������
		std::uint16_t Ammo;		//��b�e�򏊎����
		std::int16_t  Resist[3];//��b�ϐ��l(%)
		std::uint8_t  Inventory;//��b������ؗe��

		std::uint8_t CameraCount; //�u��ׁv�ۯĐ�
		std::uint8_t ArmSlotCount;//�u�r�v�ۯĐ�
		std::uint8_t ArmorCount;  //�u���b�v�ۯĐ�
		std::uint8_t TranspCount; //�u�ړ��v�ۯĐ�
		std::uint8_t UtilCount;   //�u���̑��v�ۯĐ�
	};

	aqua::IGameObject* m_SoundManager;	//������Ȱ�ެ����߲��
	aqua::IGameObject* m_UnitManager;	//�Ư��Ȱ�ެ����߲��
	aqua::IGameObject* m_TextManager;	//÷���Ȱ�ެ����߲��
	aqua::IGameObject* m_UIManager;		//UI�Ȱ�ެ����߲��

	status m_Status;

	aqua::CVector2 m_OnMapPos;	//�}�b�v��ł̈ʒu
	aqua::CVector2 m_Position;	//���ײĂ̈ʒu
	aqua::CSprite m_Sprite;	//�L�����X�v���C�g

	std::uint16_t m_Life;		//���ݑϋv��
	std::uint16_t m_MaxLife;	//�ő�ϋv��
	std::uint16_t m_Cooling;	//��p�\��
	std::int16_t  m_Heat;		//�M
	std::int16_t  m_BaseHeat;	//�M�����l
	std::uint8_t  m_Inventory;	//������ؗe��
	std::uint16_t m_Weight;	//�����d��
	std::uint16_t m_Support;	//�����d�ʏ��(�����ł��Ȃ�����)
	std::uint16_t m_Batt;		//�ޯ�ذ�c��
	std::uint16_t m_MaxBatt;	//�ޯ�ذ�e��
	std::uint16_t m_Parts;		//�������i
	std::uint16_t m_MaxParts;	//���i�������
	std::uint16_t m_Ammo;		//�����e��
	std::uint16_t m_MaxAmmo;	//�e�򏊎����
	std::int16_t  m_Resist[3];	//�ϐ��l(%)
	std::int16_t  m_DmgCut[3];	//��Ұ�޶�ė�

	std::vector<int16_t> m_Camera;	//�������Ă���J����
	std::vector<int16_t> m_Weapon;	//�������Ă��镐��
	std::vector<int16_t> m_Armor;	//�������Ă��鑕�b
	std::vector<int16_t> m_Transp;	//�������Ă���ړ�
	std::vector<int16_t> m_Util;	//�������Ă��鑕���i

	cMap* m_MapObj;
	cCamera* m_CamObj;
};