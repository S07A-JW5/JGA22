#pragma once
#include <string>

namespace Dice
{
	struct DiceRollData
	{
		unsigned short DiceCount;	//ダイス数
		unsigned short DiceFaces;	//ダイス面数
		short         ModValue;	//補正値
	};

	int DiceRoll(unsigned short faces);
	int DiceRoll(unsigned short dice_count, unsigned short faces);
	int DiceRoll(unsigned short dice_count, unsigned short faces, short num);
	int DiceRoll(DiceRollData data);
	int DiceRoll(std::string text);
	DiceRollData GetDiceRollData(std::string text);
	int PercentRoll();
	bool PercentRoll(unsigned char num);
}