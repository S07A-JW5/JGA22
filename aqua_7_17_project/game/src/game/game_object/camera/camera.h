#pragma once
#include "aqua.h"

class cCamera : public aqua::IGameObject
{
public:
	static const int m_draw_width;
	static const int m_draw_height;

	cCamera(aqua::IGameObject* parent);

	~cCamera() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	//�`���_�擾
	aqua::CVector2 GetDrawBasePos();

	//�`�撆�S�_�ݒ�
	void SetDrawCenterPos(aqua::CVector2 pos);

private:
	aqua::CVector2 m_Position;
};