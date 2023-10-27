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

	//コンストラクタ
	cUIManager(aqua::IGameObject* parent);

	//デストラクタ
	~cUIManager() = default;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//UI表示クリア
	void ClearUI();

	//UI背景可視状態切替
	void SetUIBGVisible(bool visible);

	//ステータスUI生成
	cStatusUI* CreateStatusUI(IGameObject* chr_obj, std::string name,
		uint16_t life, uint16_t maxLife, int16_t heatFlow, int16_t heat,
		int16_t energyFlow, uint16_t batt, uint16_t maxBatt,
		uint16_t parts, uint16_t maxParts, uint16_t ammo, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

	//選択肢UI生成
	cSelection* CreateSelection(std::vector<int> number, std::vector<std::string> name, std::vector<std::string> desc, aqua::CVector2 pos);

	//ボタンUI生成
	cButton* CreateButton(cButton::ButtonFunc button_function, const aqua::CVector2& pos,
		cButton::BUTTON_TYPE type = cButton::BUTTON_TYPE::SWITCH,
		const std::string& name = "ボタン", const int& width = 64, const int& height = 64,
		const int& font_size = 12, const std::string& description = "", const bool& select = false);

	//ウィンドウUI生成
	cWindow* CreateUIWindow(const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color = 0xffffffff);
	cWindow* CreateUIWindow(aqua::IGameObject* parent, const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color = 0xffffffff);

	//数値UI生成
	cValue* CreateValueText(aqua::CVector2 position, int max, int size, bool display_max);
	cValue* CreateValueText(aqua::CVector2 position, int value, int max, int size, bool display_max);

	//ゲージUI生成
	cGauge* CreateGauge(aqua::CVector2 position, int max, IGameObject* sync_counter = nullptr);
	cGauge* CreateGauge(aqua::CVector2 position, int value, int max, IGameObject* sync_counter = nullptr);
	cGauge* CreateGauge(aqua::CVector2 position, int max, bool mirror, IGameObject* sync_counter = nullptr);
	cGauge* CreateGauge(aqua::CVector2 position, int value, int max, bool mirror, IGameObject* sync_counter = nullptr);
	cGauge* CreateGaugeWithBG(aqua::CVector2 position, int value, int max, IGameObject* sync_counter = nullptr);
	cGauge* CreateGaugeWithSpecifySize(aqua::CVector2 position, int value, int max, int width, int height, bool mirror, bool has_bg, IGameObject* sync_counter = nullptr);

	static const aqua::CVector2 m_ui_window_pos;
	static const int m_ui_window_width;
	static const int m_ui_window_height;
private:
	cWindow* m_UIWindow;
};