#pragma once
#include <string>

namespace Dice
{
	struct DiceRollData
	{
		unsigned short DiceCount;	//�_�C�X��
		unsigned short DiceFaces;	//�_�C�X�ʐ�
		short         ModValue;	//�␳�l
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