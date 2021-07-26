#pragma once
#include <map>
#include "attentuation_group.h"
#include "attenuation_tag.h"

class Sim;
class DamageEvent;

class Attenuation {
public:
	Attenuation(AttenuationTag _tag, AttenuationGroup _group);

	static const std::map<AttenuationGroup, std::pair<int, float>> group_info;

	AttenuationTag tag;
	AttenuationGroup group;

	int hit_count;
	float timer;

	void ProcessAttenuation(Sim& sim, DamageEvent& event);

	void Attenuate(Sim& sim, DamageEvent& event);
};