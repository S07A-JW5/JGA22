#pragma once

#include "aqua.h"
#include "..\scene.h"

class cTitleScene : public IScene
{
public:
	//�R���X�g���N�^
	cTitleScene(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cTitleScene() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

private:
	aqua::CSprite m_Manual;	//�������

	aqua::IGameObject* m_SoundManager;	//�T�E���h�}�l�[�W���̃|�C���^
	aqua::IGameObject* m_UIManager;		//UI�}�l�[�W���̃|�C���^

	aqua::IGameObject* m_GameStartButton;	//�u�Q�[���X�^�[�g�v�{�^��
	aqua::IGameObject* m_ManualOpenButton;	//�u�Q�[�������v�{�^��
	aqua::IGameObject* m_ManualCloseButton;	//�u����v�{�^��
};