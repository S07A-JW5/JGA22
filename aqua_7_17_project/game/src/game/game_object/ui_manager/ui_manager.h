#pragma once

#include "aqua.h"
#include "component/button/button.h"
#include "component/gauge/gauge.h"
#include "component/select/select.h"
#include "component/value/value.h"
#include "component/status/status.h"
#include "component/window/window.h"

class cUIManager : public aqua::IGameObject
{
public:
	cUIManager(aqua::IGameObject* parent);

	~cUIManager(void) = default;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void ClearUI();

	void SetUIBGVisible(bool visible);

	cStatusUI* CreateStatusUI(aqua::IGameObject* chr_obj, std::string name,
		std::uint16_t life, std::uint16_t maxLife,
		std::int16_t heatFlow, std::int16_t heat, std::int16_t baseHeat,
		std::uint16_t weight, std::uint16_t support,
		std::int16_t energyFlow, std::uint16_t batt, std::uint16_t maxBatt,
		std::uint16_t parts, std::uint16_t maxParts,
		std::uint16_t ammo, std::uint16_t maxAmmo,
		std::int16_t resist[3], std::int16_t protection);

	cSelection* CreateSelection(std::vector<int> number, std::vector<std::string> name, std::vector<std::string> desc, aqua::CVector2 pos);

	cButton* CreateButton(cButton::ButtonFunc button_function, const aqua::CVector2& pos,
		cButton::BUTTON_TYPE type = cButton::BUTTON_TYPE::SWITCH,
		const std::string& name = "ƒ{ƒ^ƒ“", const int& width = 64, const int& height = 64,
		const int& font_size = 12, const std::string& description = "", const bool& select = false);

	cWindow* CreateUIWindow(const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color = 0xffffffff);
	cWindow* CreateUIWindow(aqua::IGameObject* parent, const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color = 0xffffffff);

	cValue* CreateValueText(aqua::CVector2 position, int max, int size, bool display_max);
	cValue* CreateValueText(aqua::CVector2 position, int value, int max, int size, bool display_max);

	cGauge* CreateGauge(aqua::CVector2 position, int max, aqua::IGameObject* sync_counter = nullptr);
	cGauge* CreateGauge(aqua::CVector2 position, int value, int max, aqua::IGameObject* sync_counter = nullptr);
	cGauge* CreateGauge(aqua::CVector2 position, int max, bool mirror, aqua::IGameObject* sync_counter = nullptr);
	cGauge* CreateGauge(aqua::CVector2 position, int value, int max, bool mirror, aqua::IGameObject* sync_counter = nullptr);
	cGauge* CreateGaugeWithBG(aqua::CVector2 position, int value, int max, aqua::IGameObject* sync_counter = nullptr);
	cGauge* CreateGaugeWithSpecifySize(aqua::CVector2 position, int value, int max, int width, int height, bool mirror, bool has_bg, aqua::IGameObject* sync_counter = nullptr);

	static const aqua::CVector2 m_ui_window_pos;
	static const int m_ui_window_width;
	static const int m_ui_window_height;
private:
	cWindow* m_UIWindow;
};