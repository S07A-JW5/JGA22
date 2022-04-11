#include "unit_manager.h"
#include"game/game_object/text_manager/text_manager.h"
#include <filesystem>

// コンストラクタ
CUnitManager::CUnitManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "UnitManager")
{
}

void CUnitManager::Initialize(void)
{
	m_TextManager = aqua::FindGameObject("TextManager");
	IGameObject::Initialize();
}

void CUnitManager::Update(void)
{
	IGameObject::Update();
}

void CUnitManager::Draw(void)
{
	IGameObject::Draw();
}

void CUnitManager::Finalize(void)
{
	IGameObject::Finalize();
}
