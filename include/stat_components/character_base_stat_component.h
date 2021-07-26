#pragma once
#include "stat_component.h"
#include "character_stat_growths.h"
#include <iostream>
#include "stat.h"

class PlayerBaseStatComponent : public StatComponent {
public:
	Stat stat_type;
	int* character_level;
	int* character_rarity;
	CharacterStatGrowths* growths;

	PlayerBaseStatComponent(Stat stat, int* lvl, int* rarity, CharacterStatGrowths* grow);

	virtual float get_value() override;

private:
	bool level_changed = true;
	float growthCalc();
	float ascensionCalc();
};