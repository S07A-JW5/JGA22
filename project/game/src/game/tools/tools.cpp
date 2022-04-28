#include "tools.h"

int Dice::DiceRoll(unsigned short faces)
{
	return DiceRoll(1, faces, 0);
}

int Dice::DiceRoll(unsigned short dice_count, unsigned short faces)
{
	return DiceRoll(dice_count, faces, 0);
}

int Dice::DiceRoll(unsigned short dice_count, unsigned short faces, short num)
{
	return DiceRoll(DiceRollData{ dice_count,faces,num });
	/*
	if (dice_count <= 0) return 0;
	if (faces <= 0) return 0;

	int Result = 0;
	for (int i = 0; i < dice_count; i++)
		Result += rand() % faces + 1;
	Result += num;
	return Result;*/
}

int Dice::DiceRoll(DiceRollData data)
{
	if (data.DiceCount <= 0) return 0;
	if (data.DiceFaces <= 0) return 0;

	int Result = 0;
	for (int i = 0; i < data.DiceCount; i++)
		Result += rand() % data.DiceFaces + 1;
	Result += data.ModValue;
	return Result;
}

int Dice::DiceRoll(std::string text)
{
	return DiceRoll(GetDiceRollData(text));
}

Dice::DiceRollData Dice::GetDiceRollData(std::string text)
{
	DiceRollData Data;
	Data.DiceCount = 0;
	Data.DiceFaces = 0;
	Data.ModValue = 0;
	bool Negative = false;
	unsigned char Phase = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == 0x00)
		{
			break;
		}
		if (Phase == 0)
		{
			if (text[i] == 'd')
			{
				Phase = 1;
			}
			if (text[i] == '+' || text[i] == '-')
			{
				Phase = 2;
				if (text[i] == '-')
					Negative = true;
			}
			if (text[i] >= '0' && text[i] <= '9')
			{
				Data.DiceCount *= 10;
				Data.DiceCount += text[i] - '0';
			}
			continue;
		}
		if (Phase == 1)
		{
			if (text[i] == '+' || text[i] == '-')
			{
				Phase = 2;
				if (text[i] == '-')
					Negative = true;
			}
			if (text[i] >= '0' && text[i] <= '9')
			{
				Data.DiceFaces *= 10;
				Data.DiceFaces += text[i] - '0';
			}
			continue;
		}
		if (Phase == 2)
		{
			if (text[i] >= '0' && text[i] <= '9')
			{
				Data.ModValue *= 10;
				Data.ModValue += text[i] - '0';
			}
			continue;
		}
	}
	if (Negative)
		Data.ModValue = -Data.ModValue;
	return Data;
}

int Dice::PercentRoll()
{
	return DiceRoll(1, 100, 0);
}

bool Dice::PercentRoll(unsigned char num)
{
	return PercentRoll() <= num;
}