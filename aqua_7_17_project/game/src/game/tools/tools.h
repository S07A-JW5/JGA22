#pragma once
#include <stdint.h>
#include <string>

namespace Dice
{
	struct DiceRollData
	{
		uint16_t DiceCount;	//�_�C�X��
		uint16_t DiceFaces;	//�_�C�X�ʐ�
		int16_t	 ModValue;	//�␳�l
		int16_t	 MinValue;	//�ŏ��l
		int16_t	 MaxValue;	//�ő�l
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