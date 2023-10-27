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

	//�R���X�g���N�^
	cUIManager(aqua::IGameObject* parent);

	//�f�X�g���N�^
	~cUIManager() = default;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Finalize() override;

	//UI�\���N���A
	void ClearUI();

	//UI�w�i����Ԑؑ�
	void SetUIBGVisible(bool visible);

	//�X�e�[�^�XUI����
	cStatusUI* CreateStatusUI(IGameObject* chr_obj, std::string name,
		uint16_t life, uint16_t maxLife, int16_t heatFlow, int16_t heat,
		int16_t energyFlow, uint16_t batt, uint16_t maxBatt,
		uint16_t parts, uint16_t maxParts, uint16_t ammo, uint16_t maxAmmo,
		int16_t resist[3], int16_t protection);

	//�I����UI����
	cSelection* CreateSelection(std::vector<int> number, std::vector<std::string> name, std::vector<std::string> desc, aqua::CVector2 pos);

	//�{�^��UI����
	cButton* CreateButton(cButton::ButtonFunc button_function, const aqua::CVector2& pos,
		cButton::BUTTON_TYPE type = cButton::BUTTON_TYPE::SWITCH,
		const std::string& name = "�{�^��", const int& width = 64, const int& height = 64,
		const int& font_size = 12, const std::string& description = "", const bool& select = false);

	//�E�B���h�EUI����
	cWindow* CreateUIWindow(const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color = 0xffffffff);
	cWindow* CreateUIWindow(aqua::IGameObject* parent, const aqua::CVector2& pos, const int& width, const int& height, const unsigned int& color = 0xffffffff);

	//���lUI����
	cValue* CreateValueText(aqua::CVector2 position, int max, int size, bool display_max);
	cValue* CreateValueText(aqua::CVector2 position, int value, int max, int size, bool display_max);

	//�Q�[�WUI����
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