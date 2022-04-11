#include "result.h"

CResultScene::CResultScene(aqua::IGameObject* parent, std::string name)
	:IScene(parent,name)
{
}

void CResultScene::Initialize(void)
{		
}

void CResultScene::Update(void)
{
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT) || aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
		Change(SCENE_ID::TITLE);
}

void CResultScene::Draw(void)
{
}

void CResultScene::Finalize(void)
{
}
