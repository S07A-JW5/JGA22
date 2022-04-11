#pragma once

#include "aqua.h"
#include "sound_list.h"
#include "soundplayer/soundplayer.h"

class cSoundManager :public aqua::IGameObject
{
public:
	cSoundManager(aqua::IGameObject* parent);

	~cSoundManager() = default;

	void Initialize() override;

	void Finalize() override;

	void Play(SE_LIST sound);

	void PlayBGM(BGM_LIST sound);

	void StopBGM();

	void Clear();

	void Load();
private:
	aqua::CSoundPlayer* m_PlayingBGM;
	aqua::CSoundPlayer m_BGM[(int)BGM_LIST::MAX];
	aqua::CSound m_Sound[(int)SE_LIST::MAX];
};