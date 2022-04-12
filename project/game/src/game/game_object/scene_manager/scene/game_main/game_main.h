#pragma once
#include"aqua.h"
#include"..\scene.h"
#include"../../../unit_manager/unit_manager.h"
#include "map_generator/map_generator.h"

class CGameMainScene
	: public IScene
{
public:

	//�R���X�g���N�^
	CGameMainScene(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~CGameMainScene(void);

	//������
	void Initialize(void);

	//�X�V
	void Update(void);

	// �`��
	void Draw(void);

	cMapGenerator* GetMapGenerator();
private:

	//�Q�[���J�n
	void GameStart(void);

	//�Q�[����
	void GamePlay(void);

	//�Q�[���I��
	void GameFinish(void);

	//���ID
	enum STATE
	{
		STATE_GAME_START,		//!�Q�[���J�n
		STATE_GAME_PLAY,		//!�Q�[����
		STATE_GAME_FINISH,		//!�Q�[���I��
	};

	STATE  m_State;		//! ���ID

	CUnitManager* m_UnitMgr;
	cMapGenerator* m_MapGen;
};