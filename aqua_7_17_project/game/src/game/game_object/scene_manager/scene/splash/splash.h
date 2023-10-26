#pragma once

#include "aqua.h"
#include "..\scene.h"

class CSplashScene : public IScene
{
public:
	//�R���X�g���N�^
	CSplashScene(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~CSplashScene(void) = default;

	//������
	void Initialize(void) override;

	//�X�V
	void Update(void) override;

	//�`��
	void Draw(void) override;

	//���
	void Finalize(void) override;

private:
	static const float		m_wait_time;			//�ҋ@����
	aqua::CTimer			m_WaitTimer;			//�^�C�}�[
	aqua::CLabel			m_Label;				//���x��
	aqua::CSprite			m_Background;			//�w�i
};