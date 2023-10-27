#pragma once

#include "aqua.h"
#include "sound_list.h"
#include "soundplayer/soundplayer.h"

class cSoundManager :public aqua::IGameObject
{
public:

	//コンストラクタ
	cSoundManager(aqua::IGameObject* parent);

	//デストラクタ
	~cSoundManager() = default;

	//初期化
	void Initialize() override;

	//解放
	void Finalize() override;

	//効果音再生
	void Play(SE_LIST sound);

	//BGM再生
	void PlayBGM(BGM_LIST sound);

	//BGM停止
	void StopBGM();

	void Clear();

	void Load();
private:
	aqua::CSoundPlayer* m_PlayingBGM;				//再生中のBGM
	aqua::CSoundPlayer	m_BGM[(int)BGM_LIST::MAX];
	aqua::CSound		m_Sound[(int)SE_LIST::MAX];
};