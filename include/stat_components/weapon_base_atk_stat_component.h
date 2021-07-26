#pragma once
#include "stat_component.h"
#include <string>

class WeaponBaseAtkStatComponent : public StatComponent {
public:
	std::string stat_type;
	int* weapon_rarity;
	int* weapon_level;
	std::string* weapon_class;

	WeaponBaseAtkStatComponent(int* lvl, int* rarity, std::string* wclass);
	virtual float get_value();

private:
	bool levelChanged = true;
	float growthCalc();
	float ascensionCalc();
};
