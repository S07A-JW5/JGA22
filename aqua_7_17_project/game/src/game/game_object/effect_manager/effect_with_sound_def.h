#pragma once
#include "effect_id.h"

struct EffectWithSoundParam
{
	std::string	SoundFile;
	float		Delay;
};

EffectWithSoundParam SoundPlayDef[(int)EFFECT_ID::COUNT] = {
	{"" , 0.0f},
	{"" , 0.0f}
};