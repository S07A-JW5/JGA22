#include "sound_manager.h"

cSoundManager::cSoundManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "SoundManager")
	, m_PlayingBGM(nullptr)
{
}

void cSoundManager::Initialize()
{
	//Load();
}

void cSoundManager::Finalize()
{
	if (m_PlayingBGM)
		m_PlayingBGM->Stop();
	m_PlayingBGM = nullptr;

	IGameObject::Finalize();
}

void cSoundManager::Play(SE_LIST sound)
{
	cSEPlayer* SEPlayer = aqua::CreateGameObject<cSEPlayer>(this);

	SEPlayer->Load(m_Sound[int(sound)]);
}

void cSoundManager::PlayBGM(BGM_LIST sound)
{
	if (m_PlayingBGM)
		m_PlayingBGM->Stop();

	m_PlayingBGM = &m_BGM[(int)sound];
	m_PlayingBGM->Play();
}

void cSoundManager::StopBGM()
{
	if (m_PlayingBGM)
		m_PlayingBGM->Stop();

	m_PlayingBGM = nullptr;
}

void cSoundManager::Clear()
{
	IGameObject::Finalize();
}

void cSoundManager::Load()
{
	for (int i = 0; i < (int)BGM_LIST::MAX; i++)
	{
		m_BGM[i].Create(bgm_file_name[i], true);
		//m_BGM[i].SetVolume(96);
	}
	for (int i = 0; i < (int)SE_LIST::MAX; i++)
	{
		m_Sound[i].Load(se_file_name[i], 8);
	}
}
