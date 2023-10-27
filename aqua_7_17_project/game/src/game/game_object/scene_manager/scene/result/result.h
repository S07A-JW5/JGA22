#pragma once
#pragma once

#include "aqua.h"
#include "../scene.h"

class cResultScene : public IScene
{
public:
	//�R���X�g���N�^
	cResultScene(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cResultScene() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

private:
	IGameObject*	m_ResultText;		//���U���g�e�L�X�g
	IGameObject*	m_ReturnTitleButton;//�u�^�C�g���ɖ߂�v�{�^��
	aqua::CSprite	m_ResultSprite;		//���U���g�X�v���C�g
	bool			m_UIVisible;		//UI���t���O
};