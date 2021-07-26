#pragma once
#include <vector>
#include <string>
#include <map>
#include "damage_scaling_stat.h"
#include "element.h"
#include "talent.h"
#include "attenuation_tag.h"
#include "attentuation_group.h"

class DamageData {
public:
	int ticks;
	Element element;
	Talent talent_type;
	AttenuationGroup a_group;
	AttenuationTag a_tag;
	std::vector<float> times;
	int units;
	std::map<DamageScalingStat, std::vector<float>> damage;

	virtual ~DamageData();;
};
