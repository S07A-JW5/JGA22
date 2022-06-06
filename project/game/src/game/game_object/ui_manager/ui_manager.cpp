#include "ui_manager.h"

const aqua::CVector2 cUIManager::m_ui_window_pos = aqua::CVector2(720, 0);
const int cUIManager::m_ui_window_width = 560;
const int cUIManager::m_ui_window_height = 720;

cUIManager::cUIManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent,"UIManager")
{
}

void cUIManager::Initialize()
{
	IGameObject::Initialize();

	m_UIWindow = CreateUIWindow(m_ui_window_pos, m_ui_window_width, m_ui_window_height, 0xff00c000);

	m_UIWindow->SetVisible(false);
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

void cUIManager::SetUIBGVisible(bool visible)
{
	m_UIWindow->SetVisible(visible);
}

cStatusUI* cUIManager::CreateStatusUI(aqua::IGameObject* chr_obj, std::string name, std::uint16_t life, std::uint16_t maxLife, std::int16_t heatFlow, std::int16_t heat, std::int16_t baseHeat, std::uint16_t weight, std::uint16_t support, std::int16_t energyFlow, std::uint16_t batt, std::uint16_t maxBatt, std::uint16_t parts, std::uint16_t maxParts, std::uint16_t ammo, std::uint16_t maxAmmo, std::int16_t resist[3], std::int16_t protection)
{
	cStatusUI* StatUI = aqua::CreateGameObject<cStatusUI>(this);
	StatUI->Initialize(chr_obj, name, life, maxLife, heatFlow, heat, baseHeat, weight, support, energyFlow, batt, maxBatt, parts, maxParts, ammo, maxAmmo, resist, protection);
	return StatUI;
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

cWindow* cUIManager::CreateUIWindow(const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color)
{
	return CreateUIWindow(this, pos, width, height, color);
}

cWindow* cUIManager::CreateUIWindow(aqua::IGameObject* parent, const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color)
{
	cWindow* window = aqua::CreateGameObject<cWindow>(parent);
	window->Initialize(pos, width, height, color);
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
	cAmountPopUp* popup = aqua::CreateGameObject<cAmountPopUp>(this);
	popup->Initialize(pos, amount, type, miss);
	return popup;
}
