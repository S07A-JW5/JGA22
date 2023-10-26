#pragma once

#include "aqua.h"

class cSEPlayer :public aqua::IGameObject
{
public:
	cSEPlayer(aqua::IGameObject* parent);

	~cSEPlayer() = default;

	void Initialize() override;

	void Update() override;

	void Finalize() override;

	void Load(const aqua::CSound& sound);

private:
	aqua::CSoundPlayer* m_SoundPlayer;
};