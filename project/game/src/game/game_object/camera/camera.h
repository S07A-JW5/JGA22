#pragma once
#include "aqua.h"

class cCamera : public aqua::IGameObject
{
public:
	cCamera(aqua::IGameObject* parent);

	~cCamera() = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	aqua::CVector2 GetDrawBasePos();

	void SetDrawCenterPos(aqua::CVector2 pos);

private:
	aqua::CVector2 m_Position;
};