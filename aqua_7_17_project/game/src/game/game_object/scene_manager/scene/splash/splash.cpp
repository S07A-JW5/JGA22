#include "splash.h"

const float CSplashScene::m_wait_time = 1.0f;

//�R���X�g���N�^
CSplashScene::CSplashScene(aqua::IGameObject* parent)
	:IScene(parent, "SplashScene")
{
}

//������
void CSplashScene::Initialize(void)
{
	//�^�C�}�[�ݒ�
	m_WaitTimer.Setup(m_wait_time);

	//���x������
	m_Label.Create(50, 1);

	//m_Label.text = "�X�v���b�V��";
	m_Label.color = aqua::CColor::WHITE;
	m_Label.position.x = (aqua::GetWindowWidth() - m_Label.GetTextWidth()) / 2.0f;
	m_Label.position.y = (aqua::GetWindowHeight() - m_Label.GetFontHeight()) / 2.0f;

	//�X�v���C�g����
	//m_Background.Create("data\\.png");
}

//�X�V
void CSplashScene::Update(void)
{
	Change(SCENE_ID::TITLE);
	return;

	//�^�C�}�[�X�V
	m_WaitTimer.Update();

	//�ݒ肵�����ԂɂȂ�����
	if (m_WaitTimer.Finished())
	{
		//�^�C�g���V�[���ɕύX
		Change(SCENE_ID::TITLE);
	}
}

//�`��
void CSplashScene::Draw(void)
{
	//�w�i�`��
	//m_Background.Draw();

	//���x���`��
	m_Label.Draw();
}

//���
void CSplashScene::Finalize(void)
{
	//�X�v���C�g�̉��
	//m_Background.Delete();

	//���x�����
	m_Label.Delete();
}
