#include "weapon_secondary_stat_component.h"

WeaponSubstatStatComponent::WeaponSubstatStatComponent(int* lvl, float* stat) : StatComponent(), weapon_level(lvl), base_stat_value(stat) {};
float WeaponSubstatStatComponent::get_value() {
	//std::cout << "Calculating scalabale stat component\n";
	if (levelChanged) {
		_value = *weapon_level * *base_stat_value * ascensionCalc();
		levelChanged = false;
	};
	return _value;
};

float WeaponSubstatStatComponent::ascensionCalc() {
	if (*weapon_level >= 90) return 4.594f;
	else if (*weapon_level >= 85) return 4.392f;
	else if (*weapon_level >= 80) return 4.190f;
	else if (*weapon_level >= 75) return 3.988f;
	else if (*weapon_level >= 70) return 3.786f;
	else if (*weapon_level >= 65) return 3.585f;
	else if (*weapon_level >= 60) return 3.383f;
	else if (*weapon_level >= 55) return 3.181f;
	else if (*weapon_level >= 50) return 2.979f;
	else if (*weapon_level >= 45) return 2.777f;
	else if (*weapon_level >= 40) return 2.575f;
	else if (*weapon_level >= 35) return 2.373f;
	else if (*weapon_level >= 30) return 2.171f;
	else if (*weapon_level >= 25) return 1.969f;
	else if (*weapon_level >= 20) return 1.767f;
	else if (*weapon_level >= 15) return 1.565f;
	else if (*weapon_level >= 10) return 1.363f;
	else if (*weapon_level >= 5) return 1.162f;
	else return 1;
}
