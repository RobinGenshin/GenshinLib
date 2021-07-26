#pragma once
#include <vector>
#include <map>
#include "stat.h"
#include "stat_modifier.h"
#include <memory>

class FeatureStatModifierContainer {
public:
	std::vector<Stat> stats;
	std::map<Stat, std::unique_ptr<StatModifier>> stat_modifiers;
	virtual float get_stat(Stat statName);
};