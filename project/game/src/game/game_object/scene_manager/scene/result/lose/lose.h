#pragma once
#pragma once

#include "aqua.h"
#include "../result.h"

class CResultLose : public CResultScene
{
public:

	//コンストラクタ
	CResultLose(aqua::IGameObject* parent);

	//デストラクタ
	~CResultLose(void) = default;

	//初期化
	void Initialize(void) override;

	void Finalize(void) override;

private:
};