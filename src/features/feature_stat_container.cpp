#include "feature_stat_container.h"

float FeatureStatModifierContainer::get_stat(Stat statName) {
	if (std::find(stats.begin(), stats.end(), statName) == stats.end()) return 0;
	return stat_modifiers.at(statName).get()->Value();
};