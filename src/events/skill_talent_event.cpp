#include "skill_talent_event.h"
#include "player.h"
#include "sim.h"
#include "particle_event.h"
#include "talent_scaling.h"

SkillTalentEvent::SkillTalentEvent(Player& p) : TalentEvent(p, p.character.get()->get_talent_data(Talent::SKILL)) {
}

float SkillTalentEvent::get_use_time() {
	TalentData& td = dynamic_cast<TalentData&>(data);
	if (td.talent_type == Talent::SKILL) {
		std::vector<float> v = { td.time_to_attack[0], td.time_to_cancel[0], td.time_to_swap[0], td.time_to_burst[0] };
		return *min_element(std::begin(v), std::end(v));
	};
};

float SkillTalentEvent::CalculateChainTime(Sim& sim) {
	return sim.last_talent.get()->get_time_to_skill();
};

void SkillTalentEvent::ProcessEvent(Sim& sim) {
	DamageEvent::ProcessEvent(sim);
	sim.AddEvent(std::make_shared<ParticleEvent>(_player, data.element, dynamic_cast<TalentData&>(data).particles.at(get_tick())));
};

void SkillTalentEvent::InitialiseForSim(Sim& sim) {
	TalentEvent::InitialiseForSim(sim);
	if (_player.current_skill_charges > 0) {
		_player.current_skill_charges--;
	}
	else _player.skill_cd = dynamic_cast<TalentData&>(data).cd;
}


float SkillTalentEvent::get_ratio(DamageScalingStat damageType, int tick) {
	float m = TalentScaling::Get().scaling_map.at(dynamic_cast<TalentData&>(data).scaling).at(_player.get_skill_level());
	return m * DamageEvent::get_ratio(damageType, tick);
}