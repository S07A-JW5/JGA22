#pragma once

#include "aqua.h"
#include "unit/unit.h"
#include "unit/unit_id.h"
#include "unit/player/player.h"
#include "unit/npc/bot.h"
#include <vector>

class cUnitManager : public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cUnitManager(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cUnitManager(void) = default;

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Finalize();

	//���
	void Clear();

	//���j�b�g����
	void Create(std::uint16_t id, int x_pos, int y_pos);

	//�}�b�v����
	void MapGeneration();

	//�v���C���[�ɗאڂ��Ă��邩
	bool IsPlayerNearBy(aqua::CVector2 pos);

	//�w��ʒu�ɃX�y�[�X�����邩
	bool HasSpace(aqua::CVector2 pos);

	//�w��ʒu�̃��j�b�g�ɍU���ł��邩
	bool CanAttack(aqua::CVector2 target_pos);

	//�w��ʒu�̃��j�b�g�ɍU��
	bool Attack(aqua::CVector2 target_pos, int damage, IUnit::DAMAGE_TYPE type);

	//�ړ�
	void SetMovedPos(aqua::CVector2 prev, aqua::CVector2 moved);

	//�v���C���[�ړ�
	void SetPlayerPos(aqua::CVector2 pos);

	//�v���C���[�ʒu�擾
	aqua::CVector2 GetPlayerPos();

	//�v���C���[�Ƃ̋����擾
	float BetweenPlayer(aqua::CVector2 pos);

	//�}�b�v�T�C�Y�ݒ�
	void SetMapSize(int width, int height);

	//���݂̊K�w�擾
	uint8_t GetFloorCount();

private:
	IGameObject* m_TextManager; //�e�L�X�g�}�l�[�W���̃|�C���^

	cPlayer* m_Player; //�v���C���[

	uint8_t m_Floor; //���݂̊K�w

	std::vector<cBot*> m_NPCs; //�v���C���[�ȊO�̃��j�b�g

	int** m_UnitPos; //���j�b�g�ʒu

	uint8_t m_Width; //�}�b�v���T�C�Y

	uint8_t m_Height; //�}�b�v�c�T�C�Y

	IGameObject* m_MapGenerator; //�}�b�v������

	IGameObject* m_MapObj; //�}�b�v

	bool m_MapGenerated; //�}�b�v����������������

	aqua::CVector2 m_PlayerPos; //�v���C���[�ʒu

	IGameObject* m_GameMain; //�Q�[�����C���V�[���̃|�C���^
};
