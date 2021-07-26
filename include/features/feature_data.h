#pragma once
#include <string>
#include <vector>
#include <map>
#include "stat.h"

struct FeatureData {
	bool operator==(FeatureData& other) const {
		if (this == &other) return true;
		else return false;
	};

	std::string feature_category;
	std::string name;
	bool dynamic;
	bool share;
	std::vector<std::string> condition;
	std::string timing;
	float duration;
	std::string character;
	std::string weapon;
	std::string artifact;
	int constellation;
	bool field;
	int max_stacks;
	bool temporary;
	float cd;

	std::map<Stat, float> stat_modifier_data;
};