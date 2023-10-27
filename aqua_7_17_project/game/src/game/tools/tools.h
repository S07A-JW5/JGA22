#pragma once
#include <stdint.h>
#include <string>

namespace Dice
{
	struct DiceRollData
	{
		uint16_t DiceCount;	//ダイス数
		uint16_t DiceFaces;	//ダイス面数
		int16_t	 ModValue;	//補正値
		int16_t	 MinValue;	//最小値
		int16_t	 MaxValue;	//最大値
	};

	int DiceRoll(uint16_t faces);
	int DiceRoll(uint16_t dice_count, uint16_t faces);
	int DiceRoll(uint16_t dice_count, uint16_t faces, int16_t num);
	int DiceRoll(DiceRollData data);
	int DiceRoll(std::string text);
	DiceRollData GetDiceRollData(std::string text);
	std::string GetDiceRollText(DiceRollData data, bool range = false);
	void SetMinMaxValue(DiceRollData* data);
	int PercentRoll();
	bool PercentRoll(int num);
}