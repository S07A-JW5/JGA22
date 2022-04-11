#pragma once

#include"aqua.h"
#pragma once

#include "aqua.h"
#include "scene\scene_id.h"

class CSceneManager
	: public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	CSceneManager(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~CSceneManager(void) = default;

	//������
	void Initialize(void) override;

	//�X�V
	void Update(void) override;

	//�`��
	void Draw(void) override;

	//���
	void Finalize(void) override;

	//�V�[���ύX
	void Change(SCENE_ID id);

	//�V�[���X�^�b�N
	void Push(SCENE_ID id);

	//�X�^�b�N�V�[�����o��
	void pop(void);

	//�V�[�����Z�b�g
	void Reset(void);

private:

	//���ID
	enum class STATE
	{
		SCENE_IN,		//�J�n
		SCENE_UPDATE,	//�X�V
		SCENE_OUT,		//�I��
		SCENE_CHANGE,	//�ύX
	};

	//�V�[������
	void Create(SCENE_ID id);

	//�V�[���폜
	void Delete(void);

	//�V�[���J�n
	void SceneIn(void);

	//�V�[���X�V
	void SceneUpdate(void);

	//�V�[���I��
	void SceneOut(void);

	//�V�[���ύX
	void SceneChange(void);

	static const float	m_fade_speed;		//�t�F�[�h�X�s�[�h
	SCENE_ID			m_CurrentSceneID;	//���݂̃V�[��ID
	SCENE_ID			m_NextSceneID;		//���̃V�[��ID
	SCENE_ID			m_PushSceneID;		//�v�b�V������V�[��ID
	STATE				m_State;			//���ID
	bool				m_PushFlag;			//�V�[���̃v�b�V�������t���O
	aqua::CSprite		m_FadeSprite;		//�t�F�[�h�p�X�v���C�g
};








