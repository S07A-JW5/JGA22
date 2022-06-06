#pragma once
#pragma once

#include "aqua.h"
#include "../scene.h"

class CResultScene : public IScene
{
public:
	//�R���X�g���N�^
	CResultScene(aqua::IGameObject* parent);

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

private:
	aqua::IGameObject*	 m_ResultText;		//
	aqua::IGameObject*	 m_ReturnTitleButton;	//
	aqua::CSprite		 m_ResultSprite;		//���U���g�X�v���C�g
	bool				 m_UIVisible;
};