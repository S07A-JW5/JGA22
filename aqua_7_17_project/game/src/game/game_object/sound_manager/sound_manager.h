#pragma once

#include "aqua.h"
#include "sound_list.h"
#include "soundplayer/soundplayer.h"

class cSoundManager :public aqua::IGameObject
{
public:

	//�R���X�g���N�^
	cSoundManager(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cSoundManager() = default;

	//������
	void Initialize() override;

	//���
	void Finalize() override;

	//���ʉ��Đ�
	void Play(SE_LIST sound);

	//BGM�Đ�
	void PlayBGM(BGM_LIST sound);

	//BGM��~
	void StopBGM();

	void Clear();

	void Load();
private:
	aqua::CSoundPlayer* m_PlayingBGM;				//�Đ�����BGM
	aqua::CSoundPlayer	m_BGM[(int)BGM_LIST::MAX];
	aqua::CSound		m_Sound[(int)SE_LIST::MAX];
};