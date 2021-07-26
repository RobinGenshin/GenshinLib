#pragma once
#include "damage_data.h"
#include <vector>

class TalentData : public DamageData {
public:

	std::string scaling;
	float at;
	std::vector<float> time_to_cancel;
	std::vector<float> time_to_swap;
	std::vector<float> time_to_skill;
	std::vector<float> time_to_burst;
	std::vector<float> time_to_attack;
	std::vector<float> hitlag;
	int charges;
	std::vector<float> particles;
	float cd;
	float energy_cost;
};
