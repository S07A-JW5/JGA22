#pragma once

#include "aqua.h"
#include "../button/button.h"
#include <vector>

class cSelection :public aqua::IGameObject
{
public:
	cSelection(aqua::IGameObject* parent);

	~cSelection() = default;

	void Initialize(std::vector<int> number, std::vector<std::string>name, std::vector<std::string>desc, aqua::CVector2 pos);

	void Update() override;

	void Draw() override;

	void Finalize() override;

	bool Pressed();

	int GetNum();

private:
	static const int m_selection_per_page;
	static const int m_width;
	static const int m_height;

	aqua::CVector2 m_Position;

	int m_PrevFramePage;
	int m_Page;
	int m_MaxPage;

	bool m_ButtonPressed;

	std::vector<int> m_Number;
	std::vector<std::string> m_DescText;

	int m_CurNum;

	aqua::IGameObject* m_UIManager;

	aqua::IGameObject* m_PageTextWindow;
	aqua::IGameObject* m_PageTextObj;
	aqua::IGameObject* m_DescWindow;
	aqua::IGameObject* m_DescObj;
	aqua::IGameObject* m_Window;
	cButton* m_NextPage;
	cButton* m_PrevPage;
	std::vector<cButton*> m_ButtonList;
};