#pragma once
#include "stat_component.h"
#include <string>

class WeaponSubstatStatComponent : public StatComponent {
public:
	int* weapon_level;
	float* base_stat_value;

	WeaponSubstatStatComponent(int* lvl, float* stat);

	virtual float get_value();

private:
	bool levelChanged = true;
	float ascensionCalc();
};
