#include "burst_talent_event.h"
#include "player.h"
#include "sim.h"
#include "talent_scaling.h"


BurstTalentEvent::BurstTalentEvent(Player& p) : TalentEvent(p, p.character.get()->get_talent_data(Talent::BURST)) {
}

float BurstTalentEvent::get_use_time() {
	TalentData& td = dynamic_cast<TalentData&>(data);
	std::vector<float> v = { td.time_to_attack[0], td.time_to_cancel[0], td.time_to_swap[0], td.time_to_skill[0] };
	return *min_element(std::begin(v), std::end(v));
};

float BurstTalentEvent::CalculateChainTime(Sim& sim) {
	return sim.last_talent.get()->get_time_to_burst();
};

void BurstTalentEvent::ProcessEvent(Sim& sim) {
	DamageEvent::ProcessEvent(sim);
};

void BurstTalentEvent::PostProcessEvent(Sim& sim) {
	DamageEvent::PostProcessEvent(sim);
};

void BurstTalentEvent::InitialiseForSim(Sim& sim) {
	TalentEvent::InitialiseForSim(sim);
	_player.burst_cd = dynamic_cast<TalentData&>(data).cd;
	_player.energy = 0;
};

float BurstTalentEvent::get_ratio(DamageScalingStat damageType, int tick) {
	float m = TalentScaling::Get().scaling_map.at(dynamic_cast<TalentData&>(data).scaling).at(_player.get_burst_level());
	return m * DamageEvent::get_ratio(damageType, tick);
}