#pragma once

#include "aqua.h"

class cSEPlayer :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cSEPlayer(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cSEPlayer() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//���
	void Finalize() override;

	//�T�E���h�Đ�
	void Load(const aqua::CSound& sound);

private:
	aqua::CSoundPlayer* m_SoundPlayer;
};