#pragma once
#pragma once

#include "aqua.h"
#include "../result.h"

class CResultLose : public CResultScene
{
public:

	//�R���X�g���N�^
	CResultLose(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~CResultLose(void) = default;

	//������
	void Initialize(void) override;

	void Finalize(void) override;

private:
};