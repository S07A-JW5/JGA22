#include "soundplayer.h"

cSEPlayer::cSEPlayer(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "SoundEffectPlayer")
	, m_SoundPlayer(nullptr)
{
}

void cSEPlayer::Initialize()
{
}

void cSEPlayer::Update()
{
	if (m_SoundPlayer)
		if (!m_SoundPlayer->IsPlaying())
			DeleteObject();
}

void cSEPlayer::Finalize()
{
	if (m_SoundPlayer)
		AQUA_SAFE_DELETE(m_SoundPlayer);

	IGameObject::Finalize();
}

void cSEPlayer::Load(const aqua::CSound& sound)
{
	m_SoundPlayer = AQUA_NEW aqua::CSoundPlayer;
	if (m_SoundPlayer)
	{
		m_SoundPlayer->Create(sound);
		m_SoundPlayer->Play();

		//m_SoundPlayer->SetVolume(96);
	}
}