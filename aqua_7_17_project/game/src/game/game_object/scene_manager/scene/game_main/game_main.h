#pragma once
#include "aqua.h"
#include "..\scene.h"
#include "map_generator/map_generator.h"

class cGameMainScene : public IScene
{
public:

	//�R���X�g���N�^
	cGameMainScene(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cGameMainScene();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Finalize() override;

	//�}�b�v������擾
	cMapGenerator* GetMapGenerator();

private:

	//�Q�[���J�n
	void GameStart();

	//�Q�[����
	void GamePlay();

	//�Q�[���I��
	void GameFinish();

	//���ID
	enum STATE
	{
		STATE_GAME_START,	//�Q�[���J�n
		STATE_GAME_PLAY,	//�Q�[����
		STATE_GAME_FINISH,	//�Q�[���I��
	};

	STATE  m_State; //���ID

	IGameObject*	m_UIManager;	//UI�}�l�[�W���̃|�C���^
	IGameObject*	m_UnitManager;	//���j�b�g�}�l�[�W���̃|�C���^
	IGameObject*	m_TextManager;	//�e�L�X�g�}�l�[�W���̃|�C���^
	cMapGenerator*	m_MapGenerator;	//�}�b�v������̃|�C���^

	aqua::CBoxPrimitive m_Black;	//�g�����W�V�����p
};