#pragma once

#include "aqua.h"

class cWindow :public aqua::IGameObject
{
public:
	cWindow(aqua::IGameObject* parent);

	~cWindow() = default;

	void Initialize(const aqua::CVector2& pos, const int& width = 64, const int& height = 64);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetVisible(bool visible);

	void SetPosition(const aqua::CVector2& pos);

	aqua::CVector2 GetPosition();

	static const int m_space;

private:
	static const int m_size;

	aqua::CVector2 m_Position;

	int m_Height;
	int m_Width;

	aqua::CSprite m_Sprite[9];
};