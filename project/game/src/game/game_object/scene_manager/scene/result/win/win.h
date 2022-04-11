#pragma once

#include "aqua.h"
#include "../result.h"

class CResultWin : public CResultScene
{
public:

	//コンストラクタ
	CResultWin(aqua::IGameObject* parent);

	//デストラクタ
	~CResultWin(void) = default;

	//初期化
	void Initialize(void) override;

	void Finalize(void) override;

private:
};