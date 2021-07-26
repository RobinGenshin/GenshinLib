#pragma once

struct CharacterStatGrowths
{
	CharacterStatGrowths();
	CharacterStatGrowths(float bA, float bD, float bH, float gA, float gD, float gH);

	float baseATK;
	float baseDEF;
	float baseHP;
	float growthATK;
	float growthDEF;
	float growthHP;
};
