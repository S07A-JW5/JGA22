#pragma once

#include "aqua.h"
#include "../result.h"

class CResultWin : public CResultScene
{
public:

	//�R���X�g���N�^
	CResultWin(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~CResultWin(void) = default;

	//������
	void Initialize(void) override;

	void Finalize(void) override;

private:
};