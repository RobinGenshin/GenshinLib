#include "character_base_stat_component.h"

PlayerBaseStatComponent::PlayerBaseStatComponent(Stat stat, int* lvl, int* rarity, CharacterStatGrowths* grow) : StatComponent(), stat_type(stat), character_level(lvl), character_rarity(rarity), growths(grow) {};
float PlayerBaseStatComponent::get_value() {
	//std::cout << "Calculating scalabale stat component\n";
	if (level_changed) {
		_value = growthCalc() + ascensionCalc();
		level_changed = false;
	};
	//std::cout << _value << std::endl;
	return _value;
};


float PlayerBaseStatComponent::growthCalc() {
	float growth;
	if (*character_rarity == 4) growth = 0.0825688f * *character_level + 0.917443f;
	else if (*character_rarity == 5) growth = (0.0000434248f * *character_level * *character_level) + 0.0830088f * *character_level + 0.916924f;
	else growth = 0;

	float bV = 0;
	if (stat_type == Stat::BASE_ATK) bV = growths->baseATK;
	else if (stat_type == Stat::BASE_DEF) bV = growths->baseDEF;
	else if (stat_type == Stat::BASE_HP) bV = growths->baseHP;
	else throw std::runtime_error("Incorrect base stat assignment.");
	return growth * bV;
};
float PlayerBaseStatComponent::ascensionCalc() {
	float ascensionCap = 0;
	if (stat_type == Stat::BASE_ATK) ascensionCap = growths->growthATK;
	if (stat_type == Stat::BASE_DEF) ascensionCap = growths->growthDEF;
	if (stat_type == Stat::BASE_HP) ascensionCap = growths->growthHP;

	float percentage;
	if (*character_level > 80) percentage = 1;
	else if (*character_level > 70) percentage = (155 / 182);
	else if (*character_level > 60) percentage = (128 / 183);
	else if (*character_level > 50) percentage = (101 / 182);
	else if (*character_level > 40) percentage = (65 / 182);
	else if (*character_level > 20) percentage = (38 / 182);
	else percentage = 0;
	return ascensionCap * percentage;
}