#pragma once

#include "aqua.h"
#include "..\scene.h"

class CTitleScene
	:public IScene
{
public:

	//�R���X�g���N�^
	CTitleScene(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~CTitleScene(void) = default;

	//������
	void Initialize(void) override;

	//�X�V
	void Update(void) override;

	//�`��
	void Draw(void) override;

	//���
	void Finalize(void) override;

private:
	aqua::CLabel m_Label;
	aqua::CLabel m_Text;

	aqua::IGameObject* m_SoundManager;
};