#include "status.h"
#include "../../ui_manager.h"
#include "../gauge/gauge.h"
#include "game/game_object/unit_manager/unit/unit.h"


cStatusUI::cStatusUI(aqua::IGameObject* parent)
	: IGameObject(parent,"StatusUI")
	, m_Life(0)
	, m_MaxLife(0)
	, m_HeatFlow(0)
	, m_Heat(0)
	, m_BaseHeat(0)
	, m_Weight(0)
	, m_Support(0)
	, m_EnergyFlow(0)
	, m_Batt(0)
	, m_MaxBatt(0)
	, m_Parts(0)
	, m_MaxParts(0)
	, m_Ammo(0)
	, m_MaxAmmo(0)
	, m_Resist()
	, m_Protection(0)
	, m_LifeGauge(nullptr)
	, m_BattGauge(nullptr)
	, m_AmmoGauge(nullptr)
	, m_PartGauge(nullptr)
	, m_Character(nullptr)
{
}

void cStatusUI::Initialize(aqua::IGameObject* chr_obj, std::string name, std::uint16_t life, std::uint16_t maxLife, std::int16_t heatFlow, std::int16_t heat, std::int16_t baseHeat, std::uint16_t weight, std::uint16_t support, std::int16_t energyFlow, std::uint16_t batt, std::uint16_t maxBatt, std::uint16_t parts, std::uint16_t maxParts, std::uint16_t ammo, std::uint16_t maxAmmo, std::int16_t resist[3], std::int16_t protection)
{
	m_LifeText.Create(16);
	m_PartText.Create(16);
	m_AmmoText.Create(16);
	m_BattText.Create(16);
	m_HeatText.Create(16);
	m_ResistText.Create(16);
	m_ProtectionText.Create(16);
	for (int i = 0; i < 17; i++)
		m_EquipmentText[i].Create(16);
	for (int i = 0; i < 5; i++)
		m_InventoryText[i].Create(16);

	cUIManager* UIMgr = (cUIManager*)m_ParentObject;
	aqua::CVector2 Pos = cUIManager::m_ui_bg_pos;
	int GaugeXPos = cUIManager::m_ui_bg_pos.x + 560 / 2;
	Pos.x += 18;
	Pos.y += 10;

	m_LifeText.position = Pos;	
	Pos.y += 20;

	m_LifeGauge = UIMgr->CreateGaugeWithSpecifySize(aqua::CVector2(GaugeXPos, Pos.y + 4), m_Life, m_MaxLife, 540, 8, false, true);
	Pos.y += 16;

	m_BattText.position = Pos;
	Pos.y += 20;

	m_BattGauge = UIMgr->CreateGaugeWithSpecifySize(aqua::CVector2(GaugeXPos, Pos.y + 4), m_Parts, m_MaxParts, 540, 8, false, true);
	Pos.y += 16;

	m_AmmoText.position = Pos;
	Pos.y += 20;

	m_AmmoGauge = UIMgr->CreateGaugeWithSpecifySize(aqua::CVector2(GaugeXPos, Pos.y + 4), m_Ammo, m_MaxAmmo, 540, 8, false, true);
	Pos.y += 16;

	m_PartText.position = Pos;
	Pos.y += 20;

	m_PartGauge = UIMgr->CreateGaugeWithSpecifySize(aqua::CVector2(GaugeXPos, Pos.y + 4), m_Batt, m_MaxBatt, 540, 8, false, true);
	Pos.y += 16;

	m_HeatText.position = Pos;
	Pos.y += 16;

	m_ResistText.position = Pos;

	m_ProtectionText.position = aqua::CVector2(GaugeXPos, Pos.y);
	Pos.y += 20;

	m_EquipmentText[16].position = aqua::CVector2(Pos.x - 8, Pos.y);
	m_EquipmentText[16].text = "Equipment";

	for (int i = 0; i < 16; i++)
	{
		Pos.y += 16;
		m_EquipmentText[i].position = Pos;
	}
	Pos.y += 20;

	m_InventoryText[4].position = aqua::CVector2(Pos.x - 8, Pos.y);
	m_InventoryText[4].text = "Inventory";

	for (int i = 0; i < 4; i++)
	{
		Pos.y += 16;
		m_InventoryText[i].position = Pos;
	}
	Pos.y += 16;

	Pos.DebugLog();

	m_Character = chr_obj;
	m_Life = life;
	m_Heat = heat;
	m_Batt = batt;
	m_Parts = parts;
	m_Ammo = ammo;
	SetStat(name, maxLife, heatFlow, baseHeat, weight, support, energyFlow, maxBatt, maxParts, maxAmmo, resist, protection);
}

void cStatusUI::Update()
{
	IUnit* chr = (IUnit*)m_Character;
	int num = 0;
	num = chr->GetStatus(IUnit::STATUS::LIFE);
	if (m_Life != num)
		((cGauge*)m_LifeGauge)->SetNum(num);
	m_Life = num;

	num = chr->GetStatus(IUnit::STATUS::BATT);
	if (m_Batt != num)
		((cGauge*)m_BattGauge)->SetNum(num);
	m_Batt = num;

	num = chr->GetStatus(IUnit::STATUS::PARTS);
	if (m_Parts != num)
		((cGauge*)m_PartGauge)->SetNum(num);
	m_Parts = num;

	num = chr->GetStatus(IUnit::STATUS::AMMO);
	if (m_Ammo != num)
		((cGauge*)m_AmmoGauge)->SetNum(num);
	m_Ammo = num;

	m_Heat = chr->GetStatus(IUnit::STATUS::HEAT);

	m_LifeText.text =
		"Life: " + std::to_string(m_Life) + " / " + std::to_string(m_MaxLife);
	m_PartText.text =
		"Part: " + std::to_string(m_Parts) + " / " + std::to_string(m_MaxParts);
	m_AmmoText.text =
		"Ammo: " + std::to_string(m_Ammo) + " / " + std::to_string(m_MaxAmmo);
	m_BattText.text =
		"Batt: " + std::to_string(m_Batt) + " / " + std::to_string(m_MaxBatt) + " (" + std::to_string(m_EnergyFlow) + ")";
	m_HeatText.text =
		"Heat: " + std::to_string(m_Heat) + " (" + std::to_string(m_HeatFlow) + ")";

	IUnit::InventoryStat Inventory = chr->GetInventory();
	for (int i = 0; i < 4; i++)
		m_InventoryText[i].text = Inventory.Item[i];

}

void cStatusUI::Draw()
{
	m_LifeText.Draw();
	m_BattText.Draw();
	m_AmmoText.Draw();
	m_PartText.Draw();
	m_HeatText.Draw();
	m_ResistText.Draw();
	m_ProtectionText.Draw();
	for (int i = 0; i < 17; i++)
		m_EquipmentText[i].Draw();
	for (int i = 0; i < 5; i++)
		m_InventoryText[i].Draw();
}

void cStatusUI::Finalize()
{
	m_LifeText.Delete();
	m_BattText.Delete();
	m_AmmoText.Delete();
	m_PartText.Delete();
	m_HeatText.Delete();
	m_ResistText.Delete();
	m_ProtectionText.Delete();
	for (int i = 0; i < 17; i++)
		m_EquipmentText[i].Delete();
	for (int i = 0; i < 5; i++)
		m_InventoryText[i].Delete();
}

void cStatusUI::SetStat(std::string name, std::uint16_t maxLife, std::int16_t heatFlow, std::int16_t baseHeat, std::uint16_t weight, std::uint16_t support, std::int16_t energyFlow, std::uint16_t maxBatt, std::uint16_t maxParts, std::uint16_t maxAmmo, std::int16_t resist[3], std::int16_t protection)
{
	m_Name = name;
	m_MaxLife = maxLife;
	m_HeatFlow = heatFlow;
	m_BaseHeat = baseHeat;
	m_Weight = weight;
	m_Support = support;
	m_EnergyFlow = energyFlow;
	m_MaxBatt = maxBatt;
	m_MaxParts = maxParts;
	m_MaxAmmo = maxAmmo;
	for (int i = 0; i < 3; i++)
		m_Resist[i] = resist[i];
	m_Protection = protection;

	IUnit::EquippedStat Stat = ((IUnit*)m_Character)->GetEquipped();

	m_LifeText.text =
		"Life: " + std::to_string(m_Life) + " / " + std::to_string(m_MaxLife);

	((cGauge*)m_LifeGauge)->SetMax(m_MaxLife);
	((cGauge*)m_LifeGauge)->SetNum(m_Life);

	m_BattText.text =
		"Batt: " + std::to_string(m_Batt) + " / " + std::to_string(m_MaxBatt) + " (" + std::to_string(m_EnergyFlow) + ")";

	((cGauge*)m_BattGauge)->SetMax(m_MaxBatt);
	((cGauge*)m_BattGauge)->SetNum(m_Batt);

	m_AmmoText.text =
		"Ammo: " + std::to_string(m_Ammo) + " / " + std::to_string(m_MaxAmmo);

	((cGauge*)m_AmmoGauge)->SetMax(m_MaxAmmo);
	((cGauge*)m_AmmoGauge)->SetNum(m_Ammo);

	m_PartText.text =
		"Part: " + std::to_string(m_Parts) + " / " + std::to_string(m_MaxParts);

	((cGauge*)m_PartGauge)->SetMax(m_MaxParts);
	((cGauge*)m_PartGauge)->SetNum(m_Parts);

	m_HeatText.text =
		"Heat: " + std::to_string(m_Heat) + " (" + std::to_string(m_HeatFlow) + ")";
	m_ResistText.text =
		"KI: " + std::to_string(m_Resist[0]) + "%" +
		"  TH: " + std::to_string(m_Resist[1]) + "%" +
		"  EL: " + std::to_string(m_Resist[2]) + "%";

	m_ProtectionText.text =
		"Protection: " + std::to_string(m_Protection);

	for (int i = 0; i < 16; i++)
		m_EquipmentText[i].text = Stat.Equipment[i];
}