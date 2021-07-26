#include "character_stat_growths.h"

CharacterStatGrowths::CharacterStatGrowths() : baseATK(), baseDEF(), baseHP(), growthATK(), growthDEF(), growthHP() {};
CharacterStatGrowths::CharacterStatGrowths(float bA, float bD, float bH, float gA, float gD, float gH)
		: baseATK(bA), baseDEF(bD), baseHP(bH), growthATK(gA), growthDEF(gD), growthHP(gH) {};
