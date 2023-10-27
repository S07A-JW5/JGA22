#pragma once

#include "aqua.h"

class cSEPlayer :public aqua::IGameObject
{
public:

	//コンストラクタ
	cSEPlayer(aqua::IGameObject* parent);

	//デストラクタ
	~cSEPlayer() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//解放
	void Finalize() override;

	//サウンド再生
	void Load(const aqua::CSound& sound);

private:
	aqua::CSoundPlayer* m_SoundPlayer;
};