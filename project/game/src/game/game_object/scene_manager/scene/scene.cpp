#include "scene.h"
#include"../scene_manager.h"

const std::string   IScene::m_scene_category = "Scene";


// �R���X�g���N�^
IScene::IScene(aqua::IGameObject* parent, const
	std::string& object_name)
	:aqua::IGameObject(parent, object_name,m_scene_category)
{
}

// �V�[���ύX
void IScene::Change(SCENE_ID id)
{
	// �e�̃V�[���}�l�[�W���[�Ăяo��
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Change(id);
}

// �V�[���̃X�^�b�N
void IScene::Push(SCENE_ID id)
{
	//�e�̃V�[���}�l�[�W���[�Ăяo��
	CSceneManager* sm = (CSceneManager*)GetParent();

	//�V�[���X�^�b�N
	sm->Push(id);

	//�X�V��~���ĕ`��̂ݍs��
	m_GameObjectState = aqua::GAME_OBJECT_STATE::WAIT;
}

// �X�^�b�N�V�[�����o��
void IScene::Pop(void)
{
	//�e�̃V�[���}�l�[�W���[�Ăяo��
	CSceneManager* sm = (CSceneManager*)GetParent();

	//�X�^�b�N�V�[�����o��
	sm->pop();
}

// �V�[�����Z�b�g
void IScene::Reset(void)
{
	// �e�̃V�[���}�l�[�W���[�Ăяo��
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Reset();
}
