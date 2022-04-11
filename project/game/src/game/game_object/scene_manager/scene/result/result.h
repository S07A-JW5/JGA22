#pragma once
#pragma once

#include "aqua.h"
#include "../scene.h"

class CResultScene
	: public IScene
{
public:

	//�R���X�g���N�^
	CResultScene(aqua::IGameObject* parent, std::string name);

	//�f�X�g���N�^
	~CResultScene(void) = default;

	//������
	void Initialize(void) override;

	//�X�V
	void Update(void) override;

	//�`��
	void Draw(void) override;

	//���
	void Finalize(void) override;

protected:
	aqua::CSprite		m_BackgroundSprite;	//! �w�i�X�v���C�g
	aqua::CSprite		m_ResultSprite;		//! ���U���g�X�v���C�g

	aqua::CLabel		m_Label;				//!�e�L�X�g
};