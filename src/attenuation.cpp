#include "attenuation.h"
#include "sim.h"
#include "damage_event.h"



Attenuation::Attenuation(AttenuationTag _tag, AttenuationGroup _group) : tag(_tag), group(_group), hit_count(0), timer(0) {};

const std::map<AttenuationGroup, std::pair<int, float>> Attenuation::group_info = {
	{AttenuationGroup::DEFAULT, std::make_pair(3, 2.5f)},
	{AttenuationGroup::POLEARM_CHARGED_ATTACK,  std::make_pair(3, 0.5f)},
	{AttenuationGroup::AMBER,  std::make_pair(3, 1.0f)},
	{AttenuationGroup::VENTI,  std::make_pair(3, 1.0f)},
	{AttenuationGroup::FISCHL,  std::make_pair(4, 5.0f)},
	{AttenuationGroup::DILUC,  std::make_pair(5, 5.0f)},
	{AttenuationGroup::XIAO,  std::make_pair(1, 0.1f)}
};

void Attenuation::ProcessAttenuation(Sim& sim, DamageEvent& event) {
	hit_count++;
	if ((tag == AttenuationTag::NONE) || (hit_count == group_info.at(group).first) || (timer == float(0))) Attenuate(sim, event);
};

void Attenuation::Attenuate(Sim& sim, DamageEvent& event) {
	sim.enemy->gauges.ApplyElement(sim, event);
	sim.enemy->gauges.Update();
};