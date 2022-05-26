#include "player.h"
#include "../../unit_manager.h"
#include "game/game_object/database/item_db/item_db.h"
#include "game/game_object/database/equip_db/equip_db.h"
#include "game/game_object/camera/camera.h"
#include "game/game_object/ui_manager/ui_manager.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/sound_manager/sound_manager.h"

cPlayer::cPlayer(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
	, m_TargetTile(aqua::CVector2::ZERO)
	, m_StairPos(aqua::CVector2::ZERO)
	, m_StatObj(nullptr)
	, m_InputTimer(0.0f)
{
}

void cPlayer::Initialize()
{
	IUnit::Initialize();
	m_Line.Setup(aqua::CVector2::ZERO, aqua::CVector2::ZERO, 0xc07fff00);
	m_Box.Setup(aqua::CVector2::ZERO, 14, 14, 0xffff0000, false, 1);
}

void cPlayer::Update()
{
	m_Line.visible = aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT);
	m_Line.pointA = aqua::CVector2(cCamera::m_draw_width / 2, cCamera::m_draw_height / 2);

	aqua::CVector2 PointedTile = m_MapObj->GetPointedTile(aqua::mouse::GetCursorPos());

	m_Line.pointB = m_Box.position =
		(PointedTile * cMap::m_tile_size) - ((cCamera*)m_Camera)->GetDrawBasePos();
	m_Box.position.x += m_Box.thickness;
	m_Box.position.y += m_Box.thickness;

	m_Line.pointB.x += cMap::m_tile_size / 2.0f;
	m_Line.pointB.y += cMap::m_tile_size / 2.0f;

	if (!m_PlayingEffect)
	{
		m_DesiredAction = ACTION::DUMMY;
		m_UseItemSlot = -1;

		if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		{
			m_DesiredAction = ACTION::ATTACK;
			m_TargetTile = PointedTile;
		}
		else
		{
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
			{
				m_DesiredAction = ACTION::WAIT;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::W))
			{
				m_DesiredAction = ACTION::MOVE;
				m_MoveTo = DIRECTION::NORTH;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::A))
			{
				m_DesiredAction = ACTION::MOVE;
				m_MoveTo = DIRECTION::WEST;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::S))
			{
				m_DesiredAction = ACTION::MOVE;
				m_MoveTo = DIRECTION::SOUTH;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::D))
			{
				m_DesiredAction = ACTION::MOVE;
				m_MoveTo = DIRECTION::EAST;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::ONE))
			{
				m_DesiredAction = ACTION::ITEM;
				m_UseItemSlot = 0;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::TWO))
			{
				m_DesiredAction = ACTION::ITEM;
				m_UseItemSlot = 1;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::THREE))
			{
				m_DesiredAction = ACTION::ITEM;
				m_UseItemSlot = 2;
			}
			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::FOUR))
			{
				m_DesiredAction = ACTION::ITEM;
				m_UseItemSlot = 3;
			}

			if (m_DesiredAction == ACTION::ITEM)
			{
				m_ItemMode = ITEM_USE_MODE::USE;
				if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::LSHIFT))
				{
					m_ItemMode = ITEM_USE_MODE::DISCARD;
				}
				if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::LCONTROL))
				{
					m_ItemMode = ITEM_USE_MODE::SWITCH;
				}
			}
		}
	}
	if (!PlayEffect()) return;
	if (m_DesiredAction != ACTION::DUMMY)
		if (Action())
		{
			m_Batt = max(min(m_Batt + m_EnergyFlow, m_MaxBatt), 0);
			m_Heat = max(min(m_Heat + m_HeatFlow, 999), m_BaseHeat);
		}
	CameraUpdate();
}

void cPlayer::CameraUpdate()
{
	cCamera* Camera = (cCamera*)m_Camera;

	m_Position.x = m_OnMapPos.x * cMap::m_tile_size;
	m_Position.y = m_OnMapPos.y * cMap::m_tile_size;
	Camera->SetDrawCenterPos(aqua::CVector2(m_Position.x + cMap::m_tile_size / 2,
		m_Position.y + cMap::m_tile_size / 2));
	m_Sprite.position = m_Position - Camera->GetDrawBasePos();
}

void cPlayer::Draw()
{
	m_Sprite.Draw();
	m_Line.Draw();
	m_Box.Draw();
}

void cPlayer::Finalize()
{
	m_Sprite.Delete();
}

void cPlayer::SetStairPosition(aqua::CVector2 pos)
{
	m_StairPos = pos;
}

void cPlayer::CalcStatus(bool reset_param)
{
	IUnit::CalcStatus(reset_param);
	if (reset_param)
	{
		cUIManager* UIMgr = (cUIManager*)m_UIManager;
		m_StatObj = UIMgr->CreateStatusUI(this, m_Name, m_Life, m_MaxLife, m_HeatFlow, m_Heat, m_BaseHeat, m_Weight, m_Support, m_EnergyFlow, m_Batt, m_MaxBatt, m_Parts, m_MaxParts, m_Ammo, m_MaxAmmo, m_Resist, m_Protection);
	}
	else if (m_StatObj)
	{
		((cStatusUI*)m_StatObj)->SetStat(m_Name, m_MaxLife, m_HeatFlow, m_BaseHeat, m_Weight, m_Support, m_EnergyFlow, m_MaxBatt, m_MaxParts, m_MaxAmmo, m_Resist, m_Protection);
	}
}

bool cPlayer::Action()
{
	if (m_DidAction) return true;
	bool Act = false;

	switch (m_DesiredAction)
	{
	case IUnit::ACTION::WAIT:
		Act = Wait();
		break;
	case IUnit::ACTION::MOVE:
		Act = Move();
		break;
	case IUnit::ACTION::ATTACK:
		Act = Attack(m_TargetTile);
		break;
	case IUnit::ACTION::ITEM:
		Act = Item(m_UseItemSlot);
		break;
	}
	m_DidAction = Act;
	return m_DidAction;
}

bool cPlayer::Wait()
{
	cMap::DroppedItem Item = m_MapObj->GatherItem(m_OnMapPos.x, m_OnMapPos.y);
	if (Item.ItemID > 0 && Item.Num > 0)
	{
		if (Item.ItemID < (int)cItemDataBase::MATERIALS::COUNT)
		{
			switch ((cItemDataBase::MATERIALS)Item.ItemID)
			{
			case cItemDataBase::MATERIALS::AMMO:
				m_Ammo = min(m_Ammo + Item.Num, m_MaxAmmo);
				break;
			case cItemDataBase::MATERIALS::PARTS:
				m_Parts = min(m_Parts + Item.Num, m_MaxParts);
				break;
			case cItemDataBase::MATERIALS::ENERGY:
				m_Batt = min(m_Batt + Item.Num, m_MaxBatt);
				break;
			}
		}
		else
		{
			cItemDataBase::ItemData ItemData =
				((cItemDataBase*)m_ItemDataBase)->GetData(Item.ItemID);
			ItemStat temp;
			temp.ID = ItemData.ItemID;
			temp.Name = ItemData.Name;
			temp.Amount = Item.Num;
			temp.IsEquipment = ItemData.Type == cItemDataBase::ITEM_TYPE::EQUIPMENT;

			auto it = m_ItemList.begin();
			auto end = m_ItemList.end();

			while (true)
			{
				if (it == end) break;
				if ((*it).ID == temp.ID && (*it).IsEquipment == temp.IsEquipment)
				{
					temp.Amount += (*it).Amount;
					m_ItemList.erase(it);
					break;
				}
				++it;
			}
			m_ItemList.push_back(temp);
			if (m_ItemList.size() > m_Inventory)
			{
				m_ItemList.pop_back();
				m_MapObj->PutItem(m_OnMapPos.x, m_OnMapPos.y, Item.ItemID, Item.Num);
				((CTextManager*)m_TextManager)->EnterText("ƒCƒ“ƒxƒ“ƒgƒŠ‚ª–ž”t‚ÅE‚¦‚È‚¢I");
				return false;
			}
		}
	}

	if (m_OnMapPos == m_StairPos)
	{
		CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
		UnitMgr->MapGeneration();
		((CTextManager*)m_TextManager)->EnterText(std::to_string(UnitMgr->GetFloorCount()) + "ŠK");
	}
	return true;
}

bool cPlayer::Move()
{
	CUnitManager* UnitMgr = (CUnitManager*)m_UnitManager;
	aqua::CVector2 Pos = m_OnMapPos;
	bool Moved = false;

	switch (m_MoveTo)
	{
	case IUnit::DIRECTION::DUMMY:
		return false;
		break;
	case IUnit::DIRECTION::NORTH:
		Pos.y -= 1;
		break;
	case IUnit::DIRECTION::SOUTH:
		Pos.y += 1;
		break;
	case IUnit::DIRECTION::EAST:
		Pos.x += 1;
		break;
	case IUnit::DIRECTION::WEST:
		Pos.x -= 1;
		break;
	}
	if (m_MapObj->IsWalkableTile(Pos.x, Pos.y))
	{
		if (UnitMgr->HasSpace(Pos))
		{
			Moved = true;
			m_OnMapPos = Pos;
			UnitMgr->SetPlayerPos(m_OnMapPos);
			m_MapObj->SetMapped(m_OnMapPos, 8);
		}
		else
		{
			return Attack(Pos);
		}
	}
	return Moved;
}

bool cPlayer::Attack(aqua::CVector2 pos)
{
	if (!m_MapObj->IsTileVisible(pos.x, pos.y))return false;
	return IUnit::Attack(pos);
}

bool cPlayer::Item(std::int8_t slot, ITEM_USE_MODE mode)
{
	if (slot < 0) return false;
	if (slot >= m_Inventory) return false;
	if (slot >= m_ItemList.size()) return false;

	auto it = m_ItemList.begin();
	auto end = m_ItemList.end();
	if (it == end) return false;

	for (int i = 0; i < slot; i++)
	{
		if (it == end) return false;
		++it;
	}
	if ((*it).ID <= 0) return false;
	if ((*it).Amount <= 0) return false;

	switch (m_ItemMode)
	{
	case IUnit::ITEM_USE_MODE::USE:
	{
		if ((*it).IsEquipment)
		{
			bool Changed = EquipmentChange((*it).ID);
			if (--(*it).Amount <= 0) m_ItemList.erase(it);
			return Changed;
		}
		cItemDataBase::ItemData Item = ((cItemDataBase*)m_ItemDataBase)->GetData((*it).ID);

		if (Item.Type != cItemDataBase::ITEM_TYPE::CONSUMABLE) return false;

		if (--(*it).Amount <= 0) m_ItemList.erase(it);

		m_Life = max(min(m_Life + Item.Life, m_MaxLife), 0);
		m_Ammo = max(min(m_Ammo + Item.Ammo, m_MaxAmmo), 0);
		m_Batt = max(min(m_Batt + Item.Energy, m_MaxBatt), 0);
		m_Parts = max(min(m_Parts + Item.Parts, m_MaxParts), 0);
		m_Heat = max(m_Heat - Item.Cooling, m_BaseHeat); 
	}
		break;
	case IUnit::ITEM_USE_MODE::DISCARD:
		m_MapObj->PutItem(m_OnMapPos.x, m_OnMapPos.y, (*it).ID, (*it).Amount);
		m_ItemList.erase(it);
		break;
	case IUnit::ITEM_USE_MODE::SWITCH:
		ItemStat temp = (*it);
		m_ItemList.erase(it);
		m_ItemList.push_back(temp);
		break;
	}
	return true;
}

bool cPlayer::EquipmentChange(std::uint16_t id)
{
	if (id <= 0) return false;

	cEquipDataBase::Equipment Equipment=((cEquipDataBase*)m_EquipmentDB)->GetData(id);

	if (Equipment.AttatchPart > m_Parts) return false;
	m_Parts -= Equipment.AttatchPart;

	uint16_t Drop = 0;
	std::vector<uint16_t> Temp;
	Temp.clear();

	switch (Equipment.Slot)
	{
	case cEquipDataBase::EQUIPMENT_SLOT::HEAD:
		Temp.push_back(id);
		for (int i = 0; i < m_Status.HeadCount; i++)
		{
			Drop = m_Head[i];
			if (Temp.size() >= m_Status.HeadCount) break;

			if (m_Head[i] > 0)
				Temp.push_back(m_Head[i]);
		}
		m_Head = Temp;
		break;
	case cEquipDataBase::EQUIPMENT_SLOT::ARM:
		Temp.push_back(id);
		for (int i = 0; i < m_Status.ArmCount; i++)
		{
			Drop = m_Arm[i];
			if (Temp.size() >= m_Status.ArmCount) break;

			if (m_Arm[i] > 0)
				Temp.push_back(m_Arm[i]);
		}
		m_Arm = Temp;
		break;
	case cEquipDataBase::EQUIPMENT_SLOT::CHEST:
		Temp.push_back(id);
		for (int i = 0; i < m_Status.ChestCount; i++)
		{
			Drop = m_Chest[i];
			if (Temp.size() >= m_Status.ChestCount) break;

			if (m_Chest[i] > 0)
				Temp.push_back(m_Chest[i]);
		}
		m_Chest = Temp;
		break;
	case cEquipDataBase::EQUIPMENT_SLOT::BACK:
		Temp.push_back(id);
		for (int i = 0; i < m_Status.BackCount; i++)
		{
			Drop = m_Back[i];
			if (Temp.size() >= m_Status.BackCount) break;

			if (m_Back[i] > 0)
				Temp.push_back(m_Back[i]);
		}
		m_Back = Temp;
		break;
	case cEquipDataBase::EQUIPMENT_SLOT::LEG:
		Temp.push_back(id);
		for (int i = 0; i < m_Status.LegCount; i++)
		{
			Drop = m_Leg[i];
			if (Temp.size() >= m_Status.LegCount) break;

			if (m_Leg[i] > 0)
				Temp.push_back(m_Leg[i]);
		}
		m_Leg = Temp;
		break;
	case cEquipDataBase::EQUIPMENT_SLOT::SHOULDER:
		Temp.push_back(id);
		for (int i = 0; i < m_Status.ShlderCount; i++)
		{
			Drop = m_Shlder[i];
			if (Temp.size() >= m_Status.ShlderCount) break;

			if (m_Shlder[i] > 0)
				Temp.push_back(m_Shlder[i]);
		}
		m_Shlder = Temp;
		break;
	case cEquipDataBase::EQUIPMENT_SLOT::CARD:
		Temp.push_back(id);
		for (int i = 0; i < m_Status.CardCount; i++)
		{
			Drop = m_Card[i];
			if (Temp.size() >= m_Status.CardCount) break;

			if (m_Card[i] > 0)
				Temp.push_back(m_Card[i]);
		}
		m_Card = Temp;
		break;
	}
	m_MapObj->PutItem(m_OnMapPos.x, m_OnMapPos.y, 
		((cItemDataBase*)m_ItemDataBase)->EquipmentItem(Drop));
	CalcStatus();
	return true;
}
