#include "bot.h"
#include "../../unit_manager.h"
#include"game/game_object/ui_manager/ui_manager.h"
#include "game/game_object/text_manager/text_manager.h"
#include "game/game_object/sound_manager/sound_manager.h"
#include <vector>

cBot::cBot(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
{
}