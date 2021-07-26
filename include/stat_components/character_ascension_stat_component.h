#pragma once
#include "stat_component.h"
#include "stat.h"
#include <map>
#include <string>
#include <vector>

class AscensionStatComponent : public StatComponent {
public:
	Stat* stat_type;
	int* character_level;
	int* character_rarity;
	AscensionStatComponent(Stat* stat, int* lvl, int* rarity);

	float get_value() override;

private:
	bool levelChanged = true;
	float ascensionMap();
	float levelMap();
};

