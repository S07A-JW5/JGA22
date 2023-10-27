#include "tools.h"

int Dice::DiceRoll(uint16_t faces)
{
	return DiceRoll(1, faces, 0);
}

int Dice::DiceRoll(uint16_t dice_count, uint16_t faces)
{
	return DiceRoll(dice_count, faces, 0);
}

int Dice::DiceRoll(uint16_t dice_count, uint16_t faces, int16_t num)
{
	if (dice_count <= 0) return 0;
	if (faces <= 0) return 0;

	int Result = 0;
	for (int i = 0; i < dice_count; i++)
		Result += rand() % faces + 1;
	Result += num;
	return Result;
}

int Dice::DiceRoll(DiceRollData data)
{
	if (data.DiceCount <= 0) return data.ModValue;
	if (data.DiceFaces <= 0) return data.ModValue;

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
	uint8_t Phase = 0;

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == 0x00)
		{
			break;
		}
		switch (Phase)
		{
		case 0:
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
		}
		break;
		case 1:
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
		}
		break;
		case 2:
		{
			if (text[i] >= '0' && text[i] <= '9')
			{
				Data.ModValue *= 10;
				Data.ModValue += text[i] - '0';
			}
		}
		break;
		}
	}
	if (Negative)
		Data.ModValue = -Data.ModValue;

	Data.MinValue = Data.DiceCount + Data.ModValue;
	Data.MaxValue = Data.DiceCount * Data.DiceFaces + Data.ModValue;

	return Data;
}

std::string Dice::GetDiceRollText(DiceRollData data, bool range)
{
	if (range)
	{
		return std::to_string(data.ModValue + data.DiceCount) + "-" +
			std::to_string(data.ModValue + data.DiceCount * data.DiceFaces);
	}
	std::string text =
		std::to_string(data.DiceCount) + "d" + std::to_string(data.DiceFaces);

	if (abs(data.ModValue) == 0)
		return text;

	if (data.ModValue > 0)
		text += "+";
	text += std::to_string(data.ModValue);
	return text;
}

void Dice::SetMinMaxValue(DiceRollData* data)
{
	data->MinValue = data->DiceCount + data->ModValue;
	data->MaxValue = data->DiceCount * data->DiceFaces + data->ModValue;
}

int Dice::PercentRoll()
{
	return DiceRoll(1, 100, 0);
}

bool Dice::PercentRoll(int num)
{
	return PercentRoll() <= num;
}