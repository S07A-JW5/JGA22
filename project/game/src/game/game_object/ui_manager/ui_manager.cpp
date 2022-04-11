#include "ui_manager.h"

cUIManager::cUIManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent,"UIManager")
{
}

void cUIManager::Initialize()
{
	IGameObject::Initialize();
}

void cUIManager::Update()
{
	IGameObject::Update();
}

void cUIManager::Draw()
{
	IGameObject::Draw();
}

void cUIManager::Finalize()
{
	IGameObject::Finalize();
}

void cUIManager::ClearUI()
{
	if (m_ChildObjectList.empty()) return;

	for (auto it : m_ChildObjectList)
		it->DeleteObject();
}

cSelection* cUIManager::CreateSelection(std::vector<int> number, std::vector<std::string> name, std::vector<std::string> desc, aqua::CVector2 pos)
{
	cSelection* Select = aqua::CreateGameObject<cSelection>(this);
	Select->Initialize(number, name, desc, pos);
	return Select;
}

cButton* cUIManager::CreateButton(cButton::ButtonFunc button_function, const aqua::CVector2& pos, cButton::BUTTON_TYPE type, const std::string& name, const int& width, const int& height, const int& font_size, const std::string& description, const bool& select)
{
	cButton* button = aqua::CreateGameObject<cButton>(this);
	button->Initialize(button_function, pos, type, name, width, height, font_size, description, select);
	return button;
}

cWindow* cUIManager::CreateUIWindow(const aqua::CVector2& pos, const int& width, const int& height)
{
	return CreateUIWindow(pos, width, height, this);
}

cWindow* cUIManager::CreateUIWindow(const aqua::CVector2& pos, const int& width, const int& height, aqua::IGameObject* parent)
{
	cWindow* window = aqua::CreateGameObject<cWindow>(parent);
	window->Initialize(pos, width, height);
	return window;
}

cValue* cUIManager::CreateValueText(aqua::CVector2 position, int max, int size, bool display_max)
{
	return CreateValueText(position, max, max, size, display_max);
}

cValue* cUIManager::CreateValueText(aqua::CVector2 position, int value, int max, int size, bool display_max)
{
	cValue* Value = aqua::CreateGameObject<cValue>(this);
	Value->Initialize(position, value, max, size, display_max);
	return Value;
}

cGauge* cUIManager::CreateGauge(aqua::CVector2 position, int max, aqua::IGameObject* sync_counter)
{
	return CreateGauge(position, max, max, false, sync_counter);
}

cGauge* cUIManager::CreateGauge(aqua::CVector2 position, int value, int max, aqua::IGameObject* sync_counter)
{
	return CreateGauge(position, value, max, false, sync_counter);
}

cGauge* cUIManager::CreateGauge(aqua::CVector2 position, int max, bool mirror, aqua::IGameObject* sync_counter)
{
	return CreateGauge(position, max, max, mirror, sync_counter);
}

cGauge* cUIManager::CreateGauge(aqua::CVector2 position, int value, int max, bool mirror, aqua::IGameObject* sync_counter)
{
	return CreateGaugeWithSpecifySize(position, value, max, 480, 40, mirror, false, sync_counter);
}

cGauge* cUIManager::CreateGaugeWithBG(aqua::CVector2 position, int value, int max, aqua::IGameObject* sync_counter)
{
	return CreateGaugeWithSpecifySize(position, value, max, 480, 40, false, true, sync_counter);
}

cGauge* cUIManager::CreateGaugeWithSpecifySize(aqua::CVector2 position, int value, int max, int width, int height, bool mirror, bool has_bg, aqua::IGameObject* sync_counter)
{
	cGauge* gauge = aqua::CreateGameObject<cGauge>(this);
	gauge->Initialize(position, value, max, width, height, mirror, has_bg, sync_counter);
	return gauge;
}

cAmountPopUp* cUIManager::CreateAmountPopUp(const aqua::CVector2& pos, const int& amount, cAmountPopUp::POP_UP_TYPE type, bool miss)
{
	cAmountPopUp* popup = aqua::CreateGameObject< cAmountPopUp>(this);
	popup->Initialize(pos, amount, type, miss);
	return popup;
}
