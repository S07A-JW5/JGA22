#pragma once

#include "aqua.h"
#include "scene_id.h"

class IScene
	:public aqua::IGameObject
{
public:
	//コンストラクタ
	IScene(aqua::IGameObject* parent, const std::string& object_name);

	//デストラクタ
	virtual ~IScene(void) = default;

	//シーン変更
	void Change(SCENE_ID id);

	//シーンスタック
	void Push(SCENE_ID id);

	//スタックシーン取り出し
	void Pop(void);

	//シーンリセット
	void Reset(void);

private:
	static const std::string	m_scene_category;	//シーンカテゴリ
};