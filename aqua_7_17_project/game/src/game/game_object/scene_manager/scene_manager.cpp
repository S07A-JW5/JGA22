#include"scene_manager.h"
#include"scene/scene.h"
#include"scene/game_main/game_main.h"
#include"scene/title/title.h"
#include"scene/result/result.h"
#include"scene/splash/splash.h"

const float CSceneManager::m_fade_speed = 255.0f;

// �R���X�g���N�^
CSceneManager::
CSceneManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"SceneManager")
	, m_CurrentSceneID(SCENE_ID::DUMMY)
	, m_NextSceneID(SCENE_ID::DUMMY)
	, m_PushSceneID(SCENE_ID::DUMMY)
	, m_State(STATE::SCENE_IN)
	, m_PushFlag(false)

{
}

// ������
void CSceneManager::Initialize(void)
{
	m_FadeSprite.Create("data\\texture\\white.png");

	m_FadeSprite.color = aqua::CColor::BLACK;


	// �X�v���b�V���V�[�����͂��߂ɐ���
	Create(SCENE_ID::TITLE);

	// �V�[����Ԃ��ێ�
	m_State = STATE::SCENE_IN;

	// �v�b�V���t���OOFF
	m_PushFlag = false;

}

// �X�V
void CSceneManager::Update(void)
{
	switch (m_State)
	{
	case STATE::SCENE_IN:		SceneIn();
		break;
	case STATE::SCENE_UPDATE:	SceneUpdate();
		break;
	case STATE::SCENE_OUT:		SceneOut();
		break;
	case STATE::SCENE_CHANGE:	SceneChange();
		break;
	}
}

 // �`��
void CSceneManager::Draw(void)
{
	IGameObject::Draw();

	m_FadeSprite.Draw();

}

// ���
void CSceneManager::Finalize(void)
{
	IGameObject::Finalize();

	m_FadeSprite.Delete();
}

// �V�[���̕ύX
void CSceneManager::Change(SCENE_ID id)
{
	//���̃V�[��ID
	m_NextSceneID = id;
}

// �V�[���X�^�b�N
void CSceneManager::Push(SCENE_ID id)
{
	//���t���[���̃v�b�V������
	if (m_PushFlag || m_PushSceneID != SCENE_ID::DUMMY) return;

	//�v�b�V���t���OON
	m_PushFlag = true;

	//�X�^�b�N����V�[��ID�ۑ�
	m_PushSceneID = id;
}

// �X�^�b�N�V�[�����o��
void CSceneManager::pop(void)
{
	//�q�̃V�[����1�Ȃ�|�b�v�ł��Ȃ�
	if (m_ChildObjectList.size() <= 1) return;

	//�����̃V�[���̃C�e���[�^�擾
	aqua::GAME_OBJECT_LIST::reverse_iterator it = m_ChildObjectList.rbegin();

	//�V�[���N���X�ɃL���X�g
	IScene* scene = (IScene*)(*it);

	//�����̃V�[�����폜�Ώۂɂ���
	scene->DeleteObject();

	//�ЂƂO�̃V�[���擾
	scene = (IScene*)(*(++it));

	//�ЂƂO�̃V�[�����A�N�e�B�u��Ԃɂ���
	scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
}

// ���Z�b�g
void CSceneManager::Reset(void)
{
	m_NextSceneID = m_CurrentSceneID;

	m_CurrentSceneID = SCENE_ID::DUMMY;
}

// �V�[���̐���
void CSceneManager::Create(SCENE_ID id)
{
	IScene* scene = nullptr;

	//id���ƂɐV���ȃV�[������
	switch (id)
	{
	case SCENE_ID::SPLASH:		scene = aqua::CreateGameObject<CSplashScene>(this);	break;
	case SCENE_ID::TITLE:		scene = aqua::CreateGameObject<CTitleScene>(this);	break;
	case SCENE_ID::GAMEMAIN:	scene = aqua::CreateGameObject<CGameMainScene>(this);	break;
	//case SCENE_ID::MENU:		scene = aqua::CreateGameObject<CMenuScene>(this);		break;
	case SCENE_ID::RESULT:		scene = aqua::CreateGameObject<CResultScene>(this);	break;
	}

	AQUA_ASSERT(scene, "�V�[���������ł��܂���ł����B");

	//�V�[����������
	scene->Initialize();
}

// �V�[���폜
void CSceneManager::Delete(void)
{
	IGameObject::Finalize();
}

// �V�[���J�n
void CSceneManager::SceneIn(void)
{
	float alpha = (float)m_FadeSprite.color.alpha;

	alpha -= m_fade_speed * aqua::GetDeltaTime();

	if (alpha < 0.0f)
	{
		alpha = 0.0f;

		m_State = STATE::SCENE_UPDATE;
	}

	m_FadeSprite.color.alpha = (unsigned char)alpha;
}

// �V�[���X�V
void CSceneManager::SceneUpdate(void)
{
	//�v�b�V���������Ă��邩�̔���
	if (m_PushFlag)
	{
		//�V���ȃV�[���𐶐����ăX�^�b�N
		Create(m_PushSceneID);

		//���g�p���̓_�~�[ID������
		m_PushSceneID = SCENE_ID::DUMMY;

		//�V�[���̃v�b�V�����I��
		m_PushFlag = false;
	}

	IGameObject::Update();

	//�V�[���ύX�̌��m
	if (m_CurrentSceneID != m_NextSceneID)
		m_State = STATE::SCENE_OUT;
}
// �V�[���I��
void CSceneManager::SceneOut(void)
{
	float alpha = (float)m_FadeSprite.color.alpha;

	alpha += m_fade_speed * aqua::GetDeltaTime();

	if (alpha > (float)aqua::CColor::MAX_COLOR)
	{
		alpha = (float)aqua::CColor::MAX_COLOR;

		m_State = STATE::SCENE_CHANGE;
	}

	m_FadeSprite.color.alpha = (unsigned char)alpha;
}

// �V�[���ύX
void CSceneManager::SceneChange(void)
{
	//���݃V�[���폜
	Delete();

	//���̃V�[������
	Create(m_NextSceneID);

	//�V�[��ID��ۑ�
	m_CurrentSceneID = m_NextSceneID;

	//��Ԃ��ڍs
	m_State = STATE::SCENE_IN;
}
