#include "character_ascension_stat_component.h"


AscensionStatComponent::AscensionStatComponent(Stat* stat, int* lvl, int* rarity) :StatComponent(), stat_type(stat), character_level(lvl), character_rarity(rarity) {};

float AscensionStatComponent::get_value() {
	if (levelChanged) {
		_value = ascensionMap() * levelMap();
		levelChanged = false;
	};
	return _value;
};

float AscensionStatComponent::ascensionMap() {
	float rarityMult = *character_rarity == 5 ? 1.2f : 1.0f;
	static std::map<Stat, float> statMultiplierMap = {
		{Stat::PCT_ATK, 6.0f}, 
		{Stat::ANEMO_DMG,6.0f}, 
		{Stat::CRYO_DMG, 6.0f}, 
		{Stat::ELECTRO_DMG, 6.0f}, 
		{Stat::GEO_DMG, 6.0f}, 
		{Stat::HYDRO_DMG, 6.0f}, 
		{Stat::PYRO_DMG, 6.0f}, 
		{Stat::PCT_HP, 6.0f},
		{Stat::CRIT_RATE, 4.0f}, 
		{Stat::CRIT_DMG, 8.0f},
		{Stat::ELEMENTAL_MASTERY, 2400.0f}, 
		{Stat::ENERGY_RECHARGE, 6.0f * (11 / 10)}, 
		{Stat::PCT_DEF, 7.5f}, 
		{Stat::HEALING_BONUS, 5.5f}
	};
	return (statMultiplierMap.at(*stat_type) * rarityMult / 100.0f);
};
float AscensionStatComponent::levelMap() {
	float percentage;
	if (*character_level > 80) percentage = 4;
	else if (*character_level > 70) percentage = 3;
	else if (*character_level > 60) percentage = 2;
	else if (*character_level > 50) percentage = 2;
	else if (*character_level > 40) percentage = 1;
	else if (*character_level > 20) percentage = 0;
	else percentage = 0;
	return percentage;
};

